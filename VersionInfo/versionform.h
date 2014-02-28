#ifndef VERSIONFORM_H
#define VERSIONFORM_H

#include <QWidget>
#include <QtCore/qglobal.h>
#include <declare_global.h>
#include <QCloseEvent>
#include <QShowEvent>
#include <typedef.h>



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
