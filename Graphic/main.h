#ifndef Graphic_H
#define Graphic_H

#include <QDialog>
#include "declare_global.h"
#include "typedef.h"

#include <qwt_plot.h>
#include <qwt_plot_grid.h>

#include <qwt_legend.h>

#include <qwt_plot_curve.h>
#include <qwt_symbol.h>

#include <qwt_plot_magnifier.h>

#include <qwt_plot_panner.h>

#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>

#define _VERS_MAJOR_ 1
#define _VERS_MINOR_ 0
#define _PL_NAME_ "Graphic"
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
  class Graphic;
}


class Graphic : public QDialog
{
    Q_OBJECT

  public:
    explicit Graphic(QWidget *parent = 0);
    void dataUpdate(INT8U *inBuff, INT32U l);
    void changeStyle(QString style);
    ~Graphic();
    QwtPlot *d_plot;
  protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);

  private slots:

  private:
    Ui::Graphic *ui;
};

#endif // Graphic_H
