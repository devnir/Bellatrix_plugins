#ifndef TIMELABEL_H
#define TIMELABEL_H

#include <QDialog>
#include "declare_global.h"
#include "typedef.h"
namespace Ui {
  class TimeLabel;
}


class TimeLabel : public QDialog
{
    Q_OBJECT

  public:
    explicit TimeLabel(QWidget *parent = 0);
    void dataUpdate(INT8U *inBuff, INT32U l);
    void changeStyle(QString style);
    ~TimeLabel();

  protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);

  private slots:

    void on_changeButton_clicked();

    void on_xB6ReqBtn_clicked();

  private:
    Ui::TimeLabel *ui;
    void updateB6(INT8U *inBuff, INT32U l);
    void updateC3(INT8U *inBuff, INT32U l);

};

#endif // TIMELABEL_H
