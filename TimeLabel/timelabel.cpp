#include "timelabel.h"
#include "ui_timelabel.h"
#include "bufffunctions.h"

TimeLabel *tl;
INT32U uid = 0;
void (*msgOut)(INT8U *buff, INT32U l) = NULL;
INT8U outBuff[256];
void (*signalClose)(INT32U) = NULL;
char* dateString(int t, int w);
char* clockString(int t);

const INT8U xC3Req[6] = "\x01\xC3\x01\x00\x00";
const INT8U xB6Req[6] = "\x01\xB6\x03\x01\x00";

TimeLabel::TimeLabel(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::TimeLabel)
{
  ui->setupUi(this);
}

TimeLabel::~TimeLabel()
{
  delete ui;
}

void TimeLabel::changeEvent(QEvent *e)
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
  tl = new TimeLabel();
  msgOut = outFunc;
  signalClose = sClose;
  uid = index;
  return;
}

void TimeLabel::dataUpdate(INT8U *inBuff, INT32U l)
{
  if(inBuff[0]== 0xB6)
    updateB6(inBuff, l);

  if(inBuff[0] == 0xC3)
    updateC3(inBuff, l);
}

void TimeLabel::updateB6(INT8U *inBuff, INT32U l)
{
  INT32U len   = 1;

  INT32U t     = 0;
  INT32U t_ms  = 0;
  INT16U week  = 0;
  INT8U scale  = 0;
  INT32S dt    = 0;
  INT16S leap  = 0;
  //чтение данных из буфера
  t = load32lu(inBuff + len);
  len += 4;
  t_ms = load32lu(inBuff + len);
  len += 4;
  week = load16lu(inBuff + len);
  len += 2;
  scale = load8lu(inBuff + len);
  len += 1;
  dt = load32ls(inBuff + len);
  len += 4;
  leap = load16ls(inBuff + len);
  len += 2;
  //визуализация данных
  QString str;
  QString scaleStr;
  str.sprintf("GPS week: %d", week);
  ui->dateLbl->setText(str);
  str.clear();
  str.sprintf("Time: %d.%09d ms", t, t_ms);
  if(scale == 0)
    scaleStr = "Scale: Timer";
  else if(scale == 1)
    scaleStr = "Scale: GLN";
  else if(scale == 2)
    scaleStr = "Scale: GPS";
  else if(scale == 4)
    scaleStr = "Scale: UTC";
  else if(scale == 6)
    scaleStr = "Scale: UTC(SU)";
  ui->timeLabel->setText(str);  
  ui->timeScale->setText(scaleStr);
  str.clear();
  str.sprintf("dt: %0.09f ms",dt/1e9);
  ui->generatorLabel->setText(str);
  str.clear();
  str.sprintf("Label deflection: %0.03f ns",leap/1e3);
  ui->timeLeapLabel->setText(str);
}

void TimeLabel::updateC3(INT8U *inBuff, INT32U l)
{
  if(l < 31)
    return;
  //чтение данных из буфера
  INT8U syncType = load8lu(inBuff + 21);
  INT32S delay = load32ls(inBuff + 22);
  INT8U labelType = load8lu(inBuff + 26);
  INT32U duration = load32lu(inBuff + 27);

  //визуализация данных
  if(labelType & 0x01)
  {
    ui->hardwareRadio->setChecked(true);
  }
  else
  {
    ui->softwareRadio->setChecked(true);
  }

  if(labelType & 0x02)
  {
    ui->ppsSecondRadio->setChecked(true);
  }
  else
  {
    ui->ppsIntervalRadio->setChecked(true);
  }

  if(labelType & 0x04)
  {
    ui->ppsValidityEn->setChecked(true);
  }
  else
  {
    ui->ppsValidityDis->setChecked(true);
  }

  if(labelType & 0x08)
  {
    ui->ppsDirect->setChecked(true);
  }
  else
  {
    ui->ppsRevers->setChecked(true);
  }

  if(labelType & 0x10)
  {
    ui->msCorrEn->setChecked(true);
  }
  else
  {
    ui->msCorrDis->setChecked(true);
  }

  ui->syncType->setCurrentIndex(syncType);

  ui->delay->setValue(delay * 0.1);
  ui->duration->setValue(duration);
}

void TimeLabel::closeEvent(QCloseEvent *)
{
  signalClose(uid);
}

void TimeLabel::changeStyle(QString style)
{
  this->setStyleSheet(style);
}

extern C_CPP void dataUpdate(INT8U *buff, INT32U l)
{
  tl->dataUpdate(buff, l);
}

extern C_CPP void show()
{
  tl->show();
}

extern C_CPP void close()
{
  tl->close();
}

extern C_CPP void changeStyle(QString style)
{
  tl->changeStyle(style);
}

void TimeLabel::showEvent(QShowEvent *)
{  
  memcpy(outBuff, xC3Req, 5);
  msgOut(outBuff, 5);
}

char* clockString(int t)
{
 int hh, mm, ss;
 static char clock[10];

 t %= 86400;
 hh = (int)(t / 3600);
 mm = (int)((t % 3600) / 60);
 ss = t % 60;
 sprintf(clock, "%02d:%02d:%02d", hh, mm, ss);
 return clock;
}

//---------------------------------------------------------------------------
static short MDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

char* dateString(int t, int w)
{
 int dd, mm, yy;
 static char date[10];

 int weekday = (int)(t / 86400);
 int i = 0;
 int j = 0;
 int numyear, quartnum;

 w += 1024;
 weekday += w * 7 + 5;
 quartnum = (int)(weekday / 1461);
 weekday -= quartnum * 1461;
 if(weekday < 366)
 {
  numyear  = 0;
  MDays[1] = 29;
 }
 else
 {
  weekday -= 366;
  numyear = weekday / 365 + 1;
  weekday -= (numyear - 1) * 365;
  MDays[1] = 28;
 }
 yy = 1980 + quartnum * 4 + numyear;
 while (i <= weekday)
 {
  i += MDays[j];
  j++;
 };
 mm = j;
 dd = weekday - i + MDays[j-1] + 1;

 sprintf(date, "%02d.%02d.%02d", dd, mm, yy % 100);
 return date;
}



void TimeLabel::on_changeButton_clicked()
{
  INT8U  buff[1024];
  INT32U params = 0xF0000;
  INT8U  syncType = 0;
  INT32S delay = 0;
  INT8U  mode = 0;
  INT32U duration = 0;

  syncType = ui->syncType->currentIndex();
  delay = ui->delay->value() * 10;

  if(ui->hardwareRadio->isChecked())
    mode |= 0x01;

  if(ui->ppsSecondRadio->isChecked())
    mode |= 0x02;

  if(ui->ppsValidityEn->isChecked())
    mode |= 0x04;

  if(ui->ppsDirect->isChecked())
    mode |= 0x08;

  if(ui->msCorrEn->isChecked())
    mode |= 0x10;


  duration = ui->duration->value();
  store8lu(buff, 0x04);
  store32lu(buff + 1, params);
  store8lu(buff + 25, syncType);
  store32lu(buff + 26, delay);
  store8lu(buff + 30, mode);
  store32lu(buff + 31, duration);

  memcpy(outBuff, buff, 35);
  msgOut(outBuff, 35);

  memcpy(outBuff, xC3Req, 5);
  msgOut(outBuff, 5);
}

void TimeLabel::on_xB6ReqBtn_clicked()
{
  memcpy(outBuff, xB6Req, 5);
  msgOut(outBuff, 5);
}
