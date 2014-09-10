#include "main.h"
#include "ui_Graphic.h"
#include "bufffunctions.h"

Graphic *pl;
INT32U uid = 0;
void (*msgOut)(INT8U *buff, INT32U l) = NULL;
INT8U outBuff[256];
void (*signalClose)(INT32U) = NULL;

const INT8U xC0Req[6] = "\x01\xC3\x01\x00\x00";

Graphic::Graphic(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Graphic)
{
  ui->setupUi(this);
  d_plot = new QwtPlot(this);



   d_plot->setTitle( "Qwt demonstration" ); // заголовок
   d_plot->setCanvasBackground( Qt::white ); // цвет фона

   // ѕараметры осей координат
   d_plot->setAxisTitle(QwtPlot::yLeft, "Y");
   d_plot->setAxisTitle(QwtPlot::xBottom, "X");
   d_plot->insertLegend( new QwtLegend() );


   // ¬ключить сетку
   // #include <qwt_plot_grid.h>
   QwtPlotGrid *grid = new QwtPlotGrid(); //
   grid->setMajorPen(QPen( Qt::gray, 2 )); // цвет линий и толщина
   grid->attach( d_plot ); // добавить сетку к полю графика
}

Graphic::~Graphic()
{
  delete ui;
}

void Graphic::changeEvent(QEvent *e)
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
  pl = new Graphic();
  msgOut = outFunc;
  signalClose = sClose;
  uid = index;
  return;
}

void Graphic::dataUpdate(INT8U *inBuff, INT32U l)
{
}

void Graphic::closeEvent(QCloseEvent *)
{
  signalClose(uid);
}

void Graphic::changeStyle(QString style)
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

void Graphic::showEvent(QShowEvent *)
{  
  memcpy(outBuff, xC0Req, 5);
  msgOut(outBuff, 5);
}
