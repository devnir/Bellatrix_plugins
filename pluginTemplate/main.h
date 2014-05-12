#ifndef PluginName_H
#define PluginName_H

#include <QDialog>
#include "declare_global.h"
#include "typedef.h"

#define _VERS_MAJOR_ 1
#define _VERS_MINOR_ 0
#define _PL_NAME_ "PluginName"
#define _PL_DESC_ "Plugin Description"
#define _PL_PKG_  "0x01" //Plugin used msg

typedef struct
{
  int major;
  int minor;
  QString name;
  QString desc;
  QString usedPkg;
}TPluginVersion;

namespace Ui {
  class PluginName;
}


class PluginName : public QDialog
{
    Q_OBJECT

  public:
    explicit PluginName(QWidget *parent = 0);
    void dataUpdate(INT8U *inBuff, INT32U l);
    void changeStyle(QString style);
    ~PluginName();

  protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);

  private slots:

  private:
    Ui::PluginName *ui;
};

#endif // PluginName_H
