#include "main.h"
#include "ui_debugViterbi.h"
#include "bufffunctions.h"

debugViterbi *pl;
INT32U uid = 0;
void (*msgOut)(INT8U *buff, INT32U l) = NULL;
INT8U outBuff[256];
void (*signalClose)(INT32U) = NULL;

const INT8U xFEReq[6] = "\x01\xFE\x02\x01\x00";

debugViterbi::debugViterbi(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::debugViterbi)
{
  ui->setupUi(this);
}

debugViterbi::~debugViterbi()
{
  delete ui;
}

void debugViterbi::changeEvent(QEvent *e)
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
  pl = new debugViterbi();
  msgOut = outFunc;
  signalClose = sClose;
  uid = index;
  return;
}

void debugViterbi::dataUpdate(INT8U *inBuff, INT32U l)
{
  if(inBuff[0] == 0xFE)
  {
    switch(inBuff[1])
    {
      case 0:
        ui->status->setText("Not INIT");
        break;
      case 1:
        ui->status->setText("INIT OK");
        break;
    }
  }
}

void debugViterbi::closeEvent(QCloseEvent *)
{
  signalClose(uid);
}

void debugViterbi::changeStyle(QString style)
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
  pl->dataUpdate(buff, l);
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

void debugViterbi::showEvent(QShowEvent *)
{  
  memcpy(outBuff, xFEReq, 5);
  msgOut(outBuff, 5);  
}

void debugViterbi::on_pushButton_clicked()
{
  INT8U x7EReq[6] = "\x7E\x01\x00\x00\x00";
  memcpy(outBuff, x7EReq, 5);
  msgOut(outBuff, 5);
}
