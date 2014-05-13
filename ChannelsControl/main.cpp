#include "main.h"
#include "ui_ChannelsControl.h"
#include "bufffunctions.h"
#include "QHeaderView"
#include "QStringList"


Channels *pl;
INT32U uid = 0;
void (*msgOut)(INT8U *buff, INT32U l) = NULL;
INT8U outBuff[256];
void (*signalClose)(INT32U) = NULL;
QString sysToStr(INT8U system);

typedef struct
{
  QString sys;
  QString prn;
  QString freq;
  QString chState;
  QString snr;
  QString phase;
  QString doppler;
  QString boardTime;
  QString measSign;
  QString RMS;
  QString satUse;
}TCHANNEL_DATA;

QVector<TCHANNEL_DATA> channData;

const INT8U x91Req[6] = "\x01\x91\x02\x01\x00";

Channels::Channels(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Channels)
{
  ui->setupUi(this);
  cMenu = new ContextMenu(this);
  cMenu->setWindowModality(Qt::WindowModal);
  connect(cMenu, SIGNAL(signalOkPress(INT8U,INT8U,INT8S)), this, SLOT(slotContextOk(INT8U,INT8U,INT8S)));
  //QHeaderView *hg = new QHeaderView(this);

  ui->tableWidget->verticalHeader()->setVisible(false);
 // prepareTable(64);
  ui->tableWidget->setColumnCount(12);
  QStringList hg;
  hg << "#" << "Sys" << "PRN" << "Freq" << "State" << "SNR" << "Phase" << "Doppler" << "Boardtime" << "Meas sign" << "RMS" << "Sat use sign";
  ui->tableWidget->setHorizontalHeaderLabels(hg);
}

Channels::~Channels()
{
  delete ui;
}

void Channels::changeEvent(QEvent *e)
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
  pl = new Channels();
  msgOut = outFunc;
  signalClose = sClose;
  uid = index;
  return;
}

void Channels::dataUpdate(INT8U *inBuff, INT32U l)
{
  if(inBuff[0] == 0x91)
  {
    useX91(inBuff, l);
  }
}

void Channels::closeEvent(QCloseEvent *)
{
  signalClose(uid);
}

void Channels::changeStyle(QString style)
{
  this->setStyleSheet(style);
}

void Channels::useX91(INT8U *inBuff, INT32U l)
{
  int n = (l - 8) / 23;
  prepareTable(n);
  channData.clear();
  for(int i = 0; i < n; i++)
  {
    TCHANNEL_DATA ch;
    ui->tableWidget->setRowHeight(i, 14);

    INT8U sys = load8lu(inBuff + 8 + i * 23);
    INT8U prn = load8lu(inBuff + 9 + i * 23);
    INT8S freq = load8ls(inBuff + 10 + i * 23);
    INT8U chState = load8lu(inBuff + 11 + i * 23);
    INT16U snr = load16lu(inBuff + 12 + i * 23);
    INT32U phase = load32lu(inBuff + 14 + i * 23);
    INT32S dopler = load32ls(inBuff + 18 + i * 23);
    INT32U boardTime = load32lu(inBuff + 22 + i * 23);
    INT16U measSign = load16lu(inBuff + 26 + i * 23);
    INT16U rms = load16lu(inBuff + 28 + i * 23);
    INT8U  satSign = load8lu(inBuff + 30 + i * 23);

    ch.sys = sysToStr(sys);
    ch.prn.sprintf("%d", prn);
    ch.freq.sprintf("%+d", freq);
    ch.chState.sprintf("0x%02X", chState);
    ch.snr.sprintf("%0.01f", snr/10.);
    ch.phase.sprintf("%0.09f", phase/1e9);
    ch.doppler.sprintf("%0.03f", dopler/1e3);
    ch.boardTime.sprintf("%d", boardTime);
    ch.measSign.sprintf("0x%04X", measSign);
    ch.RMS.sprintf("%0.01f", rms/10.);
    ch.satUse.sprintf("0x%02X", satSign);
    channData.append(ch);
  }
  putDataToTable();
}

void Channels::prepareTable(int n)
{
  int curRow = ui->tableWidget->rowCount();
  int curCol = ui->tableWidget->columnCount();

  ui->tableWidget->setRowCount(n);
  ui->tableWidget->setColumnCount(12);

  ui->tableWidget->setColumnWidth(0, 12 * 3);
  ui->tableWidget->setColumnWidth(1, 12 * 10);
  ui->tableWidget->setColumnWidth(2, 12 * 3);
  ui->tableWidget->setColumnWidth(3, 12 * 5);
  ui->tableWidget->setColumnWidth(4, 12 * 5);
  ui->tableWidget->setColumnWidth(5, 12 * 5);
  ui->tableWidget->setColumnWidth(6, 12 * 11);
  ui->tableWidget->setColumnWidth(7, 12 * 10);
  ui->tableWidget->setColumnWidth(8, 12 * 10);
  ui->tableWidget->setColumnWidth(9, 12 * 8);
  ui->tableWidget->setColumnWidth(10, 12 * 5);
  ui->tableWidget->setColumnWidth(11, 12 * 5);

  for(curRow; curRow < n; curRow++)
  {
    for(int j = 0; j < 12; j++)
      ui->tableWidget->setItem(curRow, j, new QTableWidgetItem(" "));
  }
}

void Channels::putDataToTable()
{
  for(int i = 0; (i < channData.size())&&(i < ui->tableWidget->rowCount()); i++)
  {
    ui->tableWidget->item(i, 0)->setText(QString("%1").arg(i+1));
    ui->tableWidget->item(i, 1)->setText(channData.at(i).sys);
    ui->tableWidget->item(i, 2)->setText(channData.at(i).prn);
    ui->tableWidget->item(i, 3)->setText(channData.at(i).freq);
    ui->tableWidget->item(i, 4)->setText(channData.at(i).chState);
    ui->tableWidget->item(i, 5)->setText(channData.at(i).snr);
    ui->tableWidget->item(i, 6)->setText(channData.at(i).phase);
    ui->tableWidget->item(i, 7)->setText(channData.at(i).doppler);
    ui->tableWidget->item(i, 8)->setText(channData.at(i).boardTime);
    ui->tableWidget->item(i, 9)->setText(channData.at(i).measSign);
    ui->tableWidget->item(i, 10)->setText(channData.at(i).RMS);
    ui->tableWidget->item(i, 11)->setText(channData.at(i).satUse);
  }
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

void Channels::showEvent(QShowEvent *)
{  
  memcpy(outBuff, x91Req, 5);
  msgOut(outBuff, 5);
}

void Channels::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
  cMenu->show();
}

void Channels::slotContextOk(INT8U mode, INT8U signalType, INT8S prn)
{
  INT8U x05Req[6] = "\x05\x00\x00\x00\x00";
  QItemSelectionModel *select = ui->tableWidget->selectionModel();
  if(select->hasSelection())  //check if has selection
  {
    foreach (QModelIndex index, select->selectedRows())
    {
      INT8U row = index.row();
      x05Req[1] = row;
      x05Req[2] = mode;
      x05Req[3] = signalType;
      x05Req[4] = prn;
      memcpy(outBuff, x05Req, 5);
      msgOut(outBuff, 5);
    }
  }
}

ContextMenu::ContextMenu(QWidget *parent) :
    QDialog(parent)
{
  QHBoxLayout   *modeLt = new QHBoxLayout;
  QHBoxLayout   *snsLt = new QHBoxLayout;
  QHBoxLayout   *prnLt = new QHBoxLayout;
  QHBoxLayout   *codeLt = new QHBoxLayout;
  QHBoxLayout   *freqLt = new QHBoxLayout;

  QLayout *lt = new QVBoxLayout;

  okBtn = new QPushButton;
  okBtn->setText(tr("Ok"));

  modeLbl = new QLabel;
  modeLbl->setText(tr("Channel mode:"));
  modeCombo = new QComboBox;
  modeCombo->addItem("Off");
  modeCombo->addItem("Auto");
  modeCombo->addItem("Manual");
  modeCombo->setCurrentIndex(0);

  snsLbl = new QLabel;
  snsLbl->setText("SNS:");
  snsCombo = new QComboBox;
  snsCombo->addItem("None");
  snsCombo->addItem("GLN");
  snsCombo->addItem("GPS");
  snsCombo->addItem("SBAS");
  snsCombo->addItem("GLL");
  snsCombo->addItem("Beidou");

  prnLbl = new QLabel;
  prnSpin = new QSpinBox;

  freqLbl = new QLabel;
  freqCombo = new QComboBox;

  codeLbl = new QLabel;
  codeCombo = new QComboBox;

  modeLt->addWidget(modeLbl);
  modeLt->addWidget(modeCombo);

  snsLt->addWidget(snsLbl);
  snsLt->addWidget(snsCombo);

  prnLt->addWidget(prnLbl);
  prnLt->addWidget(prnSpin);

  freqLt->addWidget(freqLbl);
  freqLt->addWidget(freqCombo);

  codeLt->addWidget(codeLbl);
  codeLt->addWidget(codeCombo);



  lt->addItem(modeLt);
  lt->addItem(snsLt);
  lt->addItem(prnLt);
  lt->addItem(freqLt);
  lt->addItem(codeLt);
  lt->addWidget(okBtn);
  setLayout(lt);

  snsCombo->setCurrentIndex(0);
  connect(snsCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_snsComboCurCh(int)));
  connect(freqCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_freqComboCurCh(int)));
  connect(okBtn, SIGNAL(clicked()), this, SLOT(slotOkPress()));
  slot_snsComboCurCh(0);

}

void ContextMenu::slot_snsComboCurCh(int index)
{
  prnLbl->setText("PRN:");
  freqLbl->setText("Freq:");
  codeLbl->setText("Code:");
  freqCombo->setEnabled(true);
  codeCombo->setEnabled(true);
  prnSpin->setEnabled(true);
  switch(index)
  {
    case 0:
      prnSpin->setMaximum(0);
      prnSpin->setMinimum(0);
      prnSpin->setValue(0);
      prnSpin->setEnabled(false);
      freqCombo->clear();
      freqCombo->setEnabled(false);
      codeCombo->clear();
      codeCombo->setEnabled(false);
      break;
    case 1:
      prnSpin->setMaximum(6);
      prnSpin->setMinimum(-7);
      prnSpin->setValue(0);
      freqCombo->clear();
      freqCombo->blockSignals(true);
      freqCombo->addItem("L1");
      freqCombo->addItem("L2");
      freqCombo->addItem("L3");
      freqCombo->blockSignals(false);
      freqCombo->setCurrentIndex(0);
      slot_freqComboCurCh(0);
      break;
    case 2:
      prnSpin->setMaximum(32);
      prnSpin->setMinimum(1);
      prnSpin->setValue(1);
      prnSpin->setEnabled(true);
      freqCombo->clear();
      freqCombo->blockSignals(true);
      freqCombo->addItem("L1");
      freqCombo->addItem("L2");
      freqCombo->addItem("");
      freqCombo->addItem("L5");
      freqCombo->blockSignals(false);
      freqCombo->setEnabled(true);
      freqCombo->setCurrentIndex(0);
      slot_freqComboCurCh(0);
      break;
  }
}

void ContextMenu::slot_freqComboCurCh(int index)
{
  codeCombo->clear();
  switch(index)
  {
    case 0:
      if(snsCombo->currentIndex() == 1)
      {
        codeCombo->addItem("CT");
        codeCombo->addItem("BT");
        codeCombo->addItem("Pilot");
      }
      else if(snsCombo->currentIndex() == 2)
      {
        codeCombo->addItem("C/A");
        codeCombo->addItem("P-code");
        codeCombo->addItem("Pilot");
      }
    break;
    case 1:
      if(snsCombo->currentIndex() == 1)
      {
        codeCombo->addItem("CT");
        codeCombo->addItem("BT");
        codeCombo->addItem("Pilot");
      }
      else if(snsCombo->currentIndex() == 2)
      {
        codeCombo->addItem("C/A");
        codeCombo->addItem("P-code");
        codeCombo->addItem("Pilot");
      }
    break;
    case 2:
      if(snsCombo->currentIndex() == 1)
      {
        codeCombo->addItem("data");
        codeCombo->addItem("");
        codeCombo->addItem("Pilot");
      }else if(snsCombo->currentIndex() == 2)
      {
      }
    break;
    case 3:
      if(snsCombo->currentIndex() == 2)
      {
        codeCombo->addItem("L2C");
        codeCombo->addItem("");
        codeCombo->addItem("Pilot");
      }
    break;
  }
}

void ContextMenu::slotOkPress()
{
  INT8U mode = modeCombo->currentIndex();
  INT8U signal = snsCombo->currentIndex();
  signal |= (freqCombo->currentIndex() & 0x03) << 3;
  signal |= (codeCombo->currentIndex() & 0x03) << 5;
  INT8S prn = prnSpin->value();
  emit signalOkPress(mode,signal, prn);
  this->close();
}

QString sysToStr(INT8U system)
{
  QString str;
  INT8U sys  = system & 0x07;
  INT8U freq = (system >> 3) & 0x03;
  INT8U code = (system >> 5) & 0x03;

  switch(sys)
  {
    case 0:
      str = "NON";
      break;
    case 1:
      str = "GLN";
      switch(freq)
      {
        case 0:
          str += " L1";
          switch(code)
          {
            case 0:
              str += " CT";
              break;
            case 1:
              str += " BT";
              break;
            case 2:
              str += " Pilot";
              break;
            case 3:
              break;
          }
        break;
        case 1:
          str += " L2";
          switch(code)
          {
            case 0:
              str += " CT";
              break;
            case 1:
              str += " BT";
              break;
            case 2:
              str += " Pilot";
              break;
            case 3:
              break;
          }
        break;
        case 2:
          str += " L3";
          switch(code)
          {
            case 0:
              str += " data";
              break;
            case 1:
              break;
            case 2:
              str += " Pilot";
              break;
            case 3:
              break;
          }
        break;
      }
      break;
    case 2:
      str = "GPS";
      switch(freq)
      {
        case 0:
          str += " L1";
          switch(code)
          {
            case 0:
              str += " C/A";
            break;
            case 1:
              str += " P-code";
              break;
            case 2:
              str += " Pilot";
            break;
            case 3:
              break;
          }
        break;
        case 1:
          str += " L2";
          switch(code)
          {
            case 0:
              str += " C/A";
            break;
            case 1:
              str += " P-code";
              break;
            case 2:
              str += " Pilot";
            break;
            case 3:
              break;
          }
        break;
        case 3:
          str += " L5";
          switch(code)
          {
            case 0:
              str += " L2C";
            break;
            case 1:
              break;
            case 2:
              str += " Pilot";
            break;
            case 3:
              break;
          }
        break;
      }
      break;
    case 3:
      str = "SBAS";
      break;
    case 4:
      str = "GLL";
      break;
    case 5:
      str = "BDS";
      break;
  }
  return str;
}


