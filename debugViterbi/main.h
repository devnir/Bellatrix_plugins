#ifndef debugViterbi_H
#define debugViterbi_H

#include <QDialog>
#include "declare_global.h"
#include "typedef.h"

#define _VERS_MAJOR_ 1
#define _VERS_MINOR_ 0
#define _PL_NAME_ "debugViterbi"
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
  class debugViterbi;
}


class debugViterbi : public QDialog
{
    Q_OBJECT

  public:
    explicit debugViterbi(QWidget *parent = 0);
    void dataUpdate(INT8U *inBuff, INT32U l);
    void changeStyle(QString style);
    ~debugViterbi();

  protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);

  private slots:

    void on_pushButton_clicked();

  private:
    Ui::debugViterbi *ui;
};

#endif // debugViterbi_H
