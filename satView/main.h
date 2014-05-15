#ifndef SatView_H
#define SatView_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QPixmap>
#include "declare_global.h"
#include "typedef.h"
#include <QGraphicsView>

#define _VERS_MAJOR_ 1
#define _VERS_MINOR_ 0
#define _PL_NAME_ "SatView"
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
  class SatView;
}


class SatView : public QDialog
{
    Q_OBJECT

  public:
    explicit SatView(QWidget *parent = 0);
    void dataUpdate(INT8U *inBuff, INT32U l);
    void changeStyle(QString style);
    void paintBackgr();
    void paintSat();
    QPainter *painter;
    ~SatView();

  protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *ev);

  private slots:

  private:
    Ui::SatView *ui;
};

#endif // SatView_H
