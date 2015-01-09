#ifndef SatView_H
#define SatView_H

#include <QDialog>
#include "declare_global.h"
#include "typedef.h"
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <QGraphicsItem>
#include <QFont>
#include <QPainterPath>
#include <QtCore>

#define _VERS_MAJOR_ 1
#define _VERS_MINOR_ 1
#define _PL_NAME_ "SatView"
#define _PL_DESC_ "Plugin Description"
#define _PL_PKG_  "0x01" //Plugin used msg
#define MAX_XA0_SAT 128

typedef struct
{
  int major;
  int minor;
  QString name;
  QString desc;
  QString usedPkg;
}TPluginVersion;

typedef struct
{
  INT8U  sys;
  INT8U  PRN;
  INT8S  fLiter;
  INT16U elev;
  INT16U az;
  INT16U SN;
}TxA0Sat;

typedef struct
{
  INT8U id;
  TxA0Sat sat[MAX_XA0_SAT];
  INT32U  satN;
}BINR2xA0;

typedef struct
{
  INT8U  id;
  INT16U data;
  INT32U uGln;
  INT32U eGln;
  INT32U uGps;
  INT32U eGps;
  INT32U uSbas;
  INT32U eSbas;
  INT32U uGll0;
  INT32U eGll0;
  INT32U uGll1;
  INT32U eGll1;
}BINR2xA1;

namespace Ui {
  class SatView;
}

class myItem : public QGraphicsEllipseItem
{
  protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

class SatView : public QDialog
{
    Q_OBJECT

  public:
    explicit SatView(QWidget *parent = 0);
    void dataUpdate(INT8U *inBuff, INT32U len);
    void changeStyle(QString style);
    QGraphicsScene *scene;
    void printLogo();
    void printSat(int elev, int azim, int sys, int num, int sn, int used);
    ~SatView();

  protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

  private slots:

    void on_pushButton_clicked();

  private:
    Ui::SatView *ui;
};

#endif // SatView_H
