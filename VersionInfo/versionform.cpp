#include "versionform.h"
#include "ui_versionform.h"
#include <QString>
#include "bufffunctions.h"
versionForm *vr;
void (*msgOut)(INT8U *buff, INT32U l) = NULL;
INT8U outBuff[256];
void (*signalClose)(INT32U) = NULL;
INT32U uid = 0;
const INT8U xC0Req[] = "\x01\xC0\x01\x01\x00";
typedef struct
{
  INT8U id;
  INT8U chn;
  INT8U module[6];
  INT8U version[3];
  INT8U subVersion[3];
  INT8U creationDate[12];
  INT8U creationTime[9];
  INT8U coment[30];
}BINR2xC0;




versionForm::versionForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::versionForm)
{
  ui->setupUi(this);
}

versionForm::~versionForm()
{
  delete ui;
}

void versionForm::dataUpdate(INT8U *inBuff, INT32U l)
{
  if(inBuff[0]!= 0xC0)
    return;

  BINR2xC0 xC0;
  xC0.id = load8lu(inBuff);
  xC0.chn = load8lu(inBuff + 1);
  for(int i =0; i<30; i++)
  {
    if(i < 6)
      xC0.module[i] = load8lu(inBuff + 2 + i);
    if(i < 3)
    {
      xC0.version[i] = load8lu(inBuff + 8 + i);
      xC0.subVersion[i] = load8lu(inBuff + 11 + i);
    }
    if(i < 12)
      xC0.creationDate[i] = load8lu(inBuff + 14 + i);
    if(i < 9)
      xC0.creationTime[i] = load8lu(inBuff + 26 + i);
    xC0.coment[i] = load8lu(inBuff + 35 + i);
  }
  QString str;
  str.sprintf("%s v%s.%s", (char *)xC0.module,
              (char *)xC0.version,
              (char *)xC0.subVersion);
  ui->deviceLabel ->setText(str);
  str.sprintf("%s", (char *)xC0.coment);
  ui->descLabel->setText(str);
  ui->chanLcdNumber->display(xC0.chn);
  str.sprintf("%s %s", (char *)xC0.creationDate,
              (char *)xC0.creationTime);
  ui->date_time_label->setText(str);

}

void versionForm::closeEvent(QCloseEvent *event)
{
  signalClose(uid);
  event->accept();
}

void versionForm::changeStyle(QString style)
{
  this->setStyleSheet(style);
}

extern C_CPP void initLib(void (*outFunc)(INT8U *buff,INT32U l),
                          void (*sClose)(INT32U), INT32U index)
{
  vr = new versionForm(/*parent*/);
  msgOut = outFunc;  
  signalClose = sClose;
  uid = index;
  return;
}

extern C_CPP void dataUpdate(INT8U *buff, INT32U l)
{
  vr->dataUpdate(buff, l);
}

extern C_CPP void show()
{
  vr->show();
}

extern C_CPP void close()
{
  vr->close();
}

extern C_CPP void changeStyle(QString style)
{
  vr->changeStyle(style);
}

void versionForm::showEvent(QShowEvent *ev)
{
  memcpy(outBuff, xC0Req, sizeof(xC0Req));
  msgOut(outBuff, sizeof(xC0Req));
}

extern C_CPP void getVersion(TPluginVersion *pl)
{
  pl->major = _VERS_MAJOR_;
  pl->minor = _VERS_MINOR_;
  pl->name = _PL_NAME_;
  pl->desc = _PL_DESC_;
  pl->usedPkg = _PL_PKG_;
}
