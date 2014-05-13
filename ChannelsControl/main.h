#ifndef CHANNELS_CONTROL_H
#define CHANNELS_CONTROL_H

#include <QDialog>
#include <QVector>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLayout>
#include <QPushButton>
#include <QSpinBox>

#include "declare_global.h"
#include "typedef.h"

#define _VERS_MAJOR_ 1
#define _VERS_MINOR_ 0
#define _PL_NAME_ "Channels control"
#define _PL_DESC_ "Channel management plugin"
#define _PL_PKG_  "0x01, 0x91" //Plugin used msg

typedef struct
{
  int major;
  int minor;
  QString name;
  QString desc;
  QString usedPkg;
}TPluginVersion;


namespace Ui {
  class Channels;
}
class ContextMenu : public QDialog
{
    Q_OBJECT
public:
    explicit ContextMenu(QWidget *parent = 0);

private:
    QPushButton *okBtn;
    QLabel      *modeLbl;
    QComboBox   *modeCombo;

    QLabel      *prnLbl;
    QSpinBox    *prnSpin;

    QLabel      *snsLbl;
    QComboBox   *snsCombo;

    QLabel      *freqLbl;
    QComboBox   *freqCombo;

    QLabel      *codeLbl;
    QComboBox   *codeCombo;

  private slots:
    void slot_snsComboCurCh(int index);
    void slot_freqComboCurCh(int index);
    void slotOkPress();
  signals:
    void signalOkPress(INT8U mode, INT8U signalType, INT8S prn);
};


class Channels : public QDialog
{
    Q_OBJECT

  public:
    explicit Channels(QWidget *parent = 0);
    void dataUpdate(INT8U *inBuff, INT32U l);
    void changeStyle(QString style);
    void useX91(INT8U *inBuff, INT32U l);
    void prepareTable(int n);
    void putDataToTable();
    ContextMenu  *cMenu;
    ~Channels();

  protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);

  private slots:

    void on_tableWidget_customContextMenuRequested(const QPoint &pos);
    void slotContextOk(INT8U mode, INT8U signalType, INT8S prn);

  private:
    Ui::Channels *ui;
};






#endif // CHANNELS_CONTROL_H
