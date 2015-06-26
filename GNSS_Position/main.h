#ifndef GNSS_Position_H
#define GNSS_Position_H

#include <QDialog>
#include "declare_global.h"
#include "typedef.h"

#define _VERS_MAJOR_ 1
#define _VERS_MINOR_ 0
#define _PL_NAME_ "GNSS_Position"
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
  class GNSS_Position;
}

typedef struct
{
    INT32U	weekTime; //Время от начала недели
    INT32U	weekTimeMs; //То же время, дробная часть миллисекунд
    INT16U	week; //Номер недели в той же шкале. Установленный старший бит параметра означает отсутствие информации о дате и времени
    INT8U	  timeScale; //Признак текущей шкалы времени приемника*
    INT32S	clokBias; //Отклонение опорного генератора
    INT32S	lat; //Широта
    INT32S	lon; //Долгота
    INT32S	height; //Высота
    INT16S	geoidHeight; //Разность между высотой над эллипсоидом и высотой над уровнем моря
    INT16U	latRMS; //Оценка точности по широте
    INT16U	lonRMS; //Оценка точности по долготе
    INT16U	heightRMS; //Оценка точности по высоте
    INT32S	vLat; //Скорость по широте
    INT32S	vLon; //Скорость по долготе
    INT32S	vHeight; //Скорость по высоте
    INT8U	HDOP;
    INT8U	VDOP;
    INT8U	TDOP;
    INT32U	pvtStatus; //Статус решения**
    INT8U	nGPS; //Количество GPS, используемых в решении
    INT8U	nGLN; //Количество ГЛОНАСС, используемых в решении
    INT8U	nGLL; //Количество Galileo, используемых в решении
    INT8U	nSBAS; //Количество SBAS, используемых в решении

}BINR2_x90;

class GNSS_Position : public QDialog
{
    Q_OBJECT

  public:
    explicit GNSS_Position(QWidget *parent = 0);
    void dataUpdate(INT8U *inBuff, INT32U l);
    void changeStyle(QString style);
    ~GNSS_Position();

  protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);

  private slots:

  private:
    Ui::GNSS_Position *ui;
    void useX90(INT8U *data, INT32U l);
    void printData();
    void prepareTable(int n);
};

#endif // GNSS_Position_H
