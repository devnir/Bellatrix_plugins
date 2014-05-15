#include "main.h"
#include "ui_satView.h"
#include "bufffunctions.h"
#include <QImage>



SatView *pl;
INT32U uid = 0;
void (*msgOut)(INT8U *buff, INT32U l) = NULL;
INT8U outBuff[256];
void (*signalClose)(INT32U) = NULL;

const INT8U xC0Req[6] = "\x01\xC3\x01\x00\x00";

SatView::SatView(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SatView)
{
  ui->setupUi(this);  
  painter = new QPainter;
  paintBackgr();
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

void SatView::dataUpdate(INT8U *inBuff, INT32U l)
{
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

extern C_CPP void dataUpdate(INT8U *buff, INT32U l)
{

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

  memcpy(outBuff, xC0Req, 5);
  msgOut(outBuff, 5);
}

void SatView::paintBackgr()
{  //setStyleSheet("background-color: rgb(0, 0, 0)");
  QBrush brush;
  QPen penB(QColor::fromRgb(65,110,25));
  brush.setColor(Qt::red);
  penB.setWidth(1);

  int h = this->height();
  int w = this->width();

  QRectF target(0., 0., w, h);
  QImage image(":/LogoNVS.png");
  QRectF source(0.0, 0.0, image.width(), image.height());

  //
  QPixmap pix( ":/LogoNVS.png" );


  // центр
  QPoint p2;
  // х
  p2.setX(w/2.);
  // у
  p2.setY(h/2.);

  //url(:/LogoNVS.png);
  // крест
  painter->setPen(penB);
  painter->drawLine(0, h/2., w, h/2.);
  painter->drawLine(w/2., 0, w/2., h);
  // мишень
  painter->setFont(QFont("Curier new", 10));
  painter->drawEllipse(p2, w/2., h/2.);
  painter->drawEllipse(p2, w/3., h/3.);
  painter->drawEllipse(p2, w/6., h/6.);
  // подписи осей
  penB.setColor(Qt::green);
  painter->setPen(penB);
  painter->drawText(w / 2., 10, "N");
  painter->drawText(w / 2., h - 10, "S");
  painter->drawText(10, h / 2, "W");
  painter->drawText(w - 10, h / 2, "E");
  QGraphicsScene *scene = new QGraphicsScene;
  scene->addPixmap( pix );
  //drawImage(target, image, source);
  ui->graphicsView->setScene(scene);
//  ui->graphicsView->drawBackground();

}

void SatView::paintSat()
{
  QPainter p;
  int elev = 17;
  int azim = 125;
  int h = this->height();
  int w = this->width();
  QBrush brush(Qt::red);
  float r = ((90 - elev) * w / 2) / 90.;
  int x = r * sin((180 - azim) * M_PI / 180.) + w / 2;
  int y = r * cos((azim + 180) * M_PI / 180.) + h / 2;
  p.setBrush(brush);
  p.drawEllipse(x-12, y-12, 24, 24);
}

void SatView::paintEvent(QPaintEvent *ev)
{

}
