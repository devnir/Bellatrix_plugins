#include "main.h"
#include "ui_SatView.h"
#include "bufffunctions.h"



SatView *pl;
INT32U uid = 0;
void (*msgOut)(INT8U *buff, INT32U l) = NULL;
INT8U outBuff[256];
void (*signalClose)(INT32U) = NULL;
void updateXA1(INT8U *inBuff, INT32U len);
BINR2xA0 pA0;
BINR2xA1 pA1;

const INT8U xA0Req[6] = "\x01\xA0\x02\x01\x00";
const INT8U xA1Req[6] = "\x01\xA1\x02\x01\x00";

SatView::SatView(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SatView)
{
  ui->setupUi(this);
  scene = new QGraphicsScene;
  ui->graphicsView->setScene(scene);
  scene->setBackgroundBrush(QBrush(Qt::black));
  scene->setSceneRect(0,0,ui->graphicsView->width(), ui->graphicsView->height());

  printLogo();
}

SatView::~SatView()
{
  delete ui;
}

void SatView::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
    break;
    default:
    break;
  }
}


extern C_CPP void initLib(void (*outFunc)(INT8U *buff,INT32U l),
                          void (*sClose)(INT32U), INT32U index)
{
  pl = new SatView();
  msgOut = outFunc;
  signalClose = sClose;
  uid = index;
  return;
}

void SatView::dataUpdate(INT8U *inBuff, INT32U len)
{
  int used = 0;
  if(inBuff[0] == 0xA0)
  {
    INT32U i=0;
    scene->clear();
    printLogo();

    for(int j = 0; j < MAX_XA0_SAT; j++)
    {
      pA0.sat[i].sys = 0;
    }

    pA0.satN = (len - 1)/9;
    pA0.id = load8lu(inBuff + 0);
    for(i =0; i< pA0.satN; i++)
    {
      used = 0;
      pA0.sat[i].sys = load8lu(inBuff + 1 + (i * 9));
      pA0.sat[i].PRN = load8lu(inBuff + 2 + (i * 9));
      pA0.sat[i].fLiter = load8ls(inBuff + 3 + (i * 9));
      pA0.sat[i].elev = load16lu(inBuff + 4 + (i * 9))/10;
      pA0.sat[i].az = load16lu(inBuff + 6 + (i * 9))/10;
      pA0.sat[i].SN = load8lu(inBuff + 8 + (i * 9))/10;
      switch (pA0.sat[i].sys & 0x07)
      {
        case 1:
          if(pA0.sat[i].PRN <33)
          {
            if(pA1.uGln && (0x01 << (pA0.sat[i].PRN - 1)))
              used = 1;
          }
        break;
        case 2:
          if(pA0.sat[i].PRN <33)
          {
            if(pA1.uGln && (0x01 << (pA0.sat[i].PRN - 1)))
              used = 1;
          }
          break;
      }
      printSat(pA0.sat[i].elev, pA0.sat[i].az, pA0.sat[i].sys & 0x07,
               pA0.sat[i].PRN, pA0.sat[i].SN, used);
      qDebug("Elev: %d", pA0.sat[i].elev);
      qDebug("Az:   %d", pA0.sat[i].az);
    }
  }
  if(inBuff[0] == 0xA1)
  {
    updateXA1(inBuff, len);
  }
}

void SatView::closeEvent(QCloseEvent *)
{
  signalClose(uid);
}

void SatView::changeStyle(QString style)
{
  this->setStyleSheet(style);
}

extern C_CPP void getVersion(TPluginVersion *pl)
{
  pl->major = _VERS_MAJOR_;
  pl->minor = _VERS_MINOR_;
  pl->name = _PL_NAME_;
  pl->desc = _PL_DESC_;
  pl->usedPkg = _PL_PKG_;
}

extern C_CPP void dataUpdate(INT8U *buff, INT32U len)
{
  pl->dataUpdate(buff, len);
}

extern C_CPP void show()
{
  pl->show();
}

extern C_CPP void close()
{
  pl->close();
}

extern C_CPP void changeStyle(QString style)
{
  pl->changeStyle(style);
}

void SatView::showEvent(QShowEvent *)
{  
  memcpy(outBuff, xA0Req, 5);
  msgOut(outBuff, 5);
  memcpy(outBuff, xA1Req, 5);
  msgOut(outBuff, 5);
}

void SatView::printLogo()
{
  QPoint p;
  QPen   pen;
  QBrush brush;
  QPixmap pix(":/LogoNVS.png");
  scene->addPixmap(pix);

  int w = ui->graphicsView->width();
  int h = ui->graphicsView->height();
  p.setX(w/2.);
  p.setY(h/2.);
  // мишень
  pen.setColor(QColor::fromRgb(65, 150, 65));
  scene->addLine(0, h/2., w, h/2., pen);
  scene->addLine(w/2., 0, w/2., h, pen);

  scene->addEllipse(0, 0, w, h, pen);
  scene->addEllipse(w/6., h/6, w - w/3., h - h /3., pen);
  scene->addEllipse(w/3., h/3.,2*w/6., 2*h/6., pen);


  // подпись осей
  QFont font = ui->graphicsView->font();
  pen.setColor(QColor::fromRgb(0x33, 0xFF, 0xFF));
  QPainterPath path;
  path.addText(w/2., 10, font,  tr("N"));
  path.addText(w/2., h-5, font, "S");
  path.addText(0, h / 2., font, "W");
  path.addText(w - 10., h/2., font, "E");
  scene->addPath(path, pen);

}

void SatView::on_pushButton_clicked()
{

}

void SatView::printSat(int elev, int azim, int sys, int num, int sn, int used)
{
  QBrush brush(Qt::SolidPattern);
  QColor color;
  QPen pen;
  float r = ((90 - elev) * ui->graphicsView->width() / 2.) / 90.;
  float x = r * sin((180 - azim) * M_PI / 180.) + ui->graphicsView->width() / 2.;
  float y = r * cos((azim + 180) * M_PI / 180.) + ui->graphicsView->height() / 2.;

  switch(sys)
  {
    case 1:
      if(sn > 0)
        color = QColor::fromRgb(0xFF, 0, 0x00);
      else
        color = QColor::fromRgb(0x7F, 0, 0x00);
      break;
    case 2:
      if(sn > 0)
        color = QColor::fromRgb(0x00, 0, 0xFF);
      else
        color = QColor::fromRgb(0x00, 0, 0x7F);
      break;
    case 3:
      if(sn > 0)
        color = QColor::fromRgb(0x00, 0x7F, 0x00);
      else
        color = QColor::fromRgb(0x00, 0x3F, 0x00);
      break;
  }
  if(used)
  {
    pen.setColor(Qt::white);
  }
  else
  {
    pen.setColor(color);
  }

  brush.setColor(color);
  myItem *itm = new myItem;
  itm->setPen(pen);
  itm->setBrush(brush);
  itm->setRect(x-12., y-12., 24., 24.);



  //QGraphicsEllipseItem * item = scene->addEllipse(x-12., y-12., 24., 24., pen, brush);
  scene->addItem(itm);

   if(sn > 1)
   {
     color = QColor::fromRgb(0xFF, 0xFF, 0xFF);
   }
   else
   {
     color = QColor::fromRgb(0xA0, 0xA0, 0xA0);
   }
   pen.setColor(color);
   pen.setWidth(1);
   pen.setStyle(Qt::SolidLine);
   QPainterPath path;
   QString  str;

   str.sprintf("%d", num);
   if(num < 10)
     path.addText(x-3, y + 3, ui->graphicsView->font(),  str);
   else if(num < 100)
     path.addText(x-7, y + 3, ui->graphicsView->font(),  str);
   else
     path.addText(x-11, y + 3, ui->graphicsView->font(),  str);

   scene->addPath(path, pen);
}


void updateXA1(INT8U *inBuff, INT32U len)
{
  INT32U offset =0;
  if(len < 3)
    return;
  pA1.id = load8lu(inBuff);
  pA1.data = load16lu(inBuff + 1);
  offset = 3;
  if(pA1.data & 0x0001)
  {
    pA1.uGln = load32lu(inBuff + offset);
    offset += 4;
  }
  if(pA1.data & 0x0002)
  {
    pA1.uGps = load32lu(inBuff + offset);
    offset += 4;
  }
  if(pA1.data & 0x0004)
  {
    pA1.uSbas = load32lu(inBuff + offset);
    offset += 4;
  }

  if(pA1.data & 0x0100)
  {
    pA1.eGln = load32lu(inBuff + offset);
    offset += 4;
  }
  if(pA1.data & 0x0200)
  {
    pA1.eGps = load32lu(inBuff + offset);
    offset += 4;
  }
  if(pA1.data & 0x0400)
  {
    pA1.eSbas = load32lu(inBuff + offset);
    offset += 4;
  }
  return;
}



void SatView::paintEvent(QPaintEvent *)
{
  scene->setSceneRect(0,0,ui->graphicsView->width(), ui->graphicsView->height());
}

void SatView::resizeEvent(QResizeEvent *ev)
{
  resize(this->height(), this->height());
}


void myItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  QRectF r = this->rect();
  r.setWidth(r.width() + 10);
  r.setHeight(r.height() + 10);
  //this->setRect(r);
  setVisible(false);
  update(r);
}


void myItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  QRectF r = this->rect();
  setVisible(false);
  update(r);
}

