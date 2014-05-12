#ifndef VERSIONFORM_H
#define VERSIONFORM_H

#include <QWidget>
#include <QtCore/qglobal.h>
#include <declare_global.h>
#include <QCloseEvent>
#include <QShowEvent>
#include <typedef.h>

#define _VERS_MAJOR_ 1
#define _VERS_MINOR_ 0
#define _PL_NAME_ "Firmware info"
#define _PL_DESC_ "Plugin displays version information"
#define _PL_PKG_  "0x01, 0xC0"

typedef struct
{
  int major;
  int minor;
  QString name;
  QString desc;
  QString usedPkg;
}TPluginVersion;

namespace Ui {
  class versionForm;
}

class versionForm :  public QWidget//, public defForm
{
    Q_OBJECT
  public:
    explicit versionForm(QWidget *parent = 0);
    ~versionForm();
    void dataUpdate(INT8U *inBuff, INT32U l);
    void changeStyle(QString style);
  protected:
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);
  private:
    Ui::versionForm *ui;
  public slots:
  signals:
    void writeBuff(QByteArray *arr);
  private slots:
};




#endif // VERSIONFORM_H
