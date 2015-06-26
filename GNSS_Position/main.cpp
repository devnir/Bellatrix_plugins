#include "main.h"
#include "ui_GNSS_Position.h"
#include "bufffunctions.h"

GNSS_Position *pl;
INT32U uid = 0;
void (*msgOut)(INT8U *buff, INT32U l) = NULL;
INT8U outBuff[256];
void (*signalClose)(INT32U) = NULL;
BINR2_x90  x90;

const INT8U x90Req[6] = "\x01\x90\x02\x01\x00";

GNSS_Position::GNSS_Position(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::GNSS_Position)
{
  ui->setupUi(this);
  ui->tableWidget->setColumnCount(2);
  QStringList hg;
  hg << tr("Description") << tr("Value");
  ui->tableWidget->verticalHeader()->setVisible(false);
  ui->tableWidget->setHorizontalHeaderLabels(hg);
  prepareTable(22);
}

GNSS_Position::~GNSS_Position()
{
  delete ui;
}

void GNSS_Position::changeEvent(QEvent *e)
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
  pl = new GNSS_Position();
  msgOut = outFunc;
  signalClose = sClose;
  uid = index;
  return;
}

void GNSS_Position::dataUpdate(INT8U *inBuff, INT32U l)
{
  if(inBuff[0] == 0x90)
  {
    useX90(inBuff, l);
  }
}

void GNSS_Position::closeEvent(QCloseEvent *)
{
  signalClose(uid);
}

void GNSS_Position::changeStyle(QString style)
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

void GNSS_Position::showEvent(QShowEvent *)
{
  memcpy(outBuff, x90Req, 5);
  msgOut(outBuff, 5);
}

void GNSS_Position::useX90(INT8U *data, INT32U l)
{
  INT32U len = 1;
  x90.weekTime   = load32lu(data + len); len += 4;
  x90.weekTimeMs = load32lu(data + len); len += 4;
  x90.week       = load16lu(data + len); len += 2;
  x90.timeScale  = load8lu(data + len);  len += 1;
  x90.clokBias   = load32ls(data + len); len += 4;
  x90.lat        = load32ls(data + len); len += 4;
  x90.lon        = load32ls(data + len); len += 4;
  x90.height     = load32ls(data + len); len += 4;
  x90.geoidHeight= load16ls(data + len); len += 2;
  x90.latRMS     = load16lu(data + len); len += 2;
  x90.lonRMS     = load16lu(data + len); len += 2;
  x90.heightRMS  = load16lu(data + len); len += 2;
  x90.vLat       = load32ls(data + len); len += 4;
  x90.vLon       = load32ls(data + len); len += 4;
  x90.vHeight    = load32ls(data + len); len += 4;
  x90.HDOP       = load8lu(data + len);  len += 1;
  x90.VDOP       = load8lu(data + len);  len += 1;
  x90.TDOP       = load8lu(data + len);  len += 1;
  x90.pvtStatus  = load32lu(data + len); len += 4;
  x90.nGPS       = load8lu(data + len);  len += 1;
  x90.nGLN       = load8lu(data + len);  len += 1;
  x90.nGLL       = load8lu(data + len);  len += 1;
  x90.nSBAS      = load8lu(data + len);  len += 1;
  printData();
}
void GNSS_Position::printData()
{
  QString str;
  str.sprintf("%0.9lf", double(x90.weekTime + x90.weekTimeMs / 1E9));
  ui->tableWidget->item(0, 1)->setText(str);
  str.sprintf("%d", x90.week);
  ui->tableWidget->item(1, 1)->setText(str);
  switch (x90.timeScale)
  {
    case 0:
      str = "Timer";
    break;
    case 1:
      str = "GLN";
    break;
    case 2:
      str = "GPS";
    break;
    case 3:
      str = "SBAS";
    break;
    case 4:
      str = "UTC";
    break;
    case 5:
      str = "GLL";
    break;
    default:
    break;
  }
  ui->tableWidget->item(2, 1)->setText(str);
  str.sprintf("%0.9lf", (double)(x90.clokBias / 1E9));
  ui->tableWidget->item(3, 1)->setText(str);
  str.sprintf("%0.7lf", (double)(x90.lat / 1E7));
  ui->tableWidget->item(4, 1)->setText(str);
  str.sprintf("%0.7lf", (double)(x90.lon / 1E7));
  ui->tableWidget->item(5, 1)->setText(str);
  str.sprintf("%0.2lf", (double)(x90.height / 1E2));
  ui->tableWidget->item(6, 1)->setText(str);
  str.sprintf("%0.2lf", (double)(x90.geoidHeight / 1E2));
  ui->tableWidget->item(7, 1)->setText(str);
  str.sprintf("%0.1lf", (double)(x90.latRMS / 1E1));
  ui->tableWidget->item(8, 1)->setText(str);
  str.sprintf("%0.1lf", (double)(x90.lonRMS / 1E1));
  ui->tableWidget->item(9, 1)->setText(str);
  str.sprintf("%0.1lf", (double)(x90.heightRMS / 1E1));
  ui->tableWidget->item(10, 1)->setText(str);
  str.sprintf("%0.2lf", (double)(x90.vLat / 1E2));
  ui->tableWidget->item(11, 1)->setText(str);
  str.sprintf("%0.2lf", (double)(x90.vLon / 1E2));
  ui->tableWidget->item(12, 1)->setText(str);
  str.sprintf("%0.2lf", (double)(x90.vHeight / 1E2));
  ui->tableWidget->item(13, 1)->setText(str);
  str.sprintf("%0.1lf", (double)(x90.HDOP / 1E1));
  ui->tableWidget->item(14, 1)->setText(str);
  str.sprintf("%0.1lf", (double)(x90.VDOP / 1E1));
  ui->tableWidget->item(15, 1)->setText(str);
  str.sprintf("%0.1lf", (double)(x90.TDOP / 1E1));
  ui->tableWidget->item(16, 1)->setText(str);
  str.sprintf("%08X", x90.pvtStatus);
  ui->tableWidget->item(17, 1)->setText(str);
  str.sprintf("%02d", x90.nGPS);
  ui->tableWidget->item(18, 1)->setText(str);
  str.sprintf("%02d", x90.nGLN);
  ui->tableWidget->item(19, 1)->setText(str);
  str.sprintf("%02d", x90.nGLL);
  ui->tableWidget->item(20, 1)->setText(str);
  str.sprintf("%02d", x90.nSBAS);
  ui->tableWidget->item(21, 1)->setText(str);
}

void GNSS_Position::prepareTable(int n)
{
  int curRow = ui->tableWidget->rowCount();
  int curCol = ui->tableWidget->columnCount();
  ui->tableWidget->setRowCount(n);
  ui->tableWidget->setColumnCount(2);

  for(curRow; curRow < n; curRow++)
  {
    for(int j = 0; j < 2; j++)
      ui->tableWidget->setItem(curRow, j, new QTableWidgetItem(" "));
  }

  ui->tableWidget->item(0, 0)->setText(tr("Time"));
  ui->tableWidget->item(1, 0)->setText(tr("Week"));
  ui->tableWidget->item(2, 0)->setText(tr("Time scale"));
  ui->tableWidget->item(3, 0)->setText(tr("Clock bias"));
  ui->tableWidget->item(4, 0)->setText(tr("Lat"));
  ui->tableWidget->item(5, 0)->setText(tr("Lon"));
  ui->tableWidget->item(6, 0)->setText(tr("Height"));
  ui->tableWidget->item(7, 0)->setText(tr("Geoid H."));
  ui->tableWidget->item(8, 0)->setText(tr("Lat RMS"));
  ui->tableWidget->item(9, 0)->setText(tr("Lon RMS"));
  ui->tableWidget->item(10, 0)->setText(tr("Height RMS"));
  ui->tableWidget->item(11, 0)->setText(tr("VLat"));
  ui->tableWidget->item(12, 0)->setText(tr("Vlon"));
  ui->tableWidget->item(13, 0)->setText(tr("VHeight"));
  ui->tableWidget->item(14, 0)->setText(tr("HDOP"));
  ui->tableWidget->item(15, 0)->setText(tr("VDOP"));
  ui->tableWidget->item(16, 0)->setText(tr("TDOP"));
  ui->tableWidget->item(17, 0)->setText(tr("PVT status"));
  ui->tableWidget->item(18, 0)->setText(tr("GPS"));
  ui->tableWidget->item(19, 0)->setText(tr("GLN"));
  ui->tableWidget->item(20, 0)->setText(tr("GLL"));
  ui->tableWidget->item(21, 0)->setText(tr("SBAS"));
}
