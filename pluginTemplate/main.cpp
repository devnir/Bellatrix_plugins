#include "main.h"
#include "ui_PluginName.h"
#include "bufffunctions.h"

PluginName *pl;
INT32U uid = 0;
void (*msgOut)(INT8U *buff, INT32U l) = NULL;
INT8U outBuff[256];
void (*signalClose)(INT32U) = NULL;

const INT8U xC0Req[6] = "\x01\xC3\x01\x00\x00";

PluginName::PluginName(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::PluginName)
{
  ui->setupUi(this);
}

PluginName::~PluginName()
{
  delete ui;
}

void PluginName::changeEvent(QEvent *e)
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
  pl = new PluginName();
  msgOut = outFunc;
  signalClose = sClose;
  uid = index;
  return;
}

void PluginName::dataUpdate(INT8U *inBuff, INT32U l)
{
}

void PluginName::closeEvent(QCloseEvent *)
{
  signalClose(uid);
}

void PluginName::changeStyle(QString style)
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

void PluginName::showEvent(QShowEvent *)
{  
  memcpy(outBuff, xC0Req, 5);
  msgOut(outBuff, 5);
}
