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
    INT32U	weekTime; //����� �� ������ ������
    INT32U	weekTimeMs; //�� �� �����, ������� ����� �����������
    INT16U	week; //����� ������ � ��� �� �����. ������������� ������� ��� ��������� �������� ���������� ���������� � ���� � �������
    INT8U	  timeScale; //������� ������� ����� ������� ���������*
    INT32S	clokBias; //���������� �������� ����������
    INT32S	lat; //������
    INT32S	lon; //�������
    INT32S	height; //������
    INT16S	geoidHeight; //�������� ����� ������� ��� ����������� � ������� ��� ������� ����
    INT16U	latRMS; //������ �������� �� ������
    INT16U	lonRMS; //������ �������� �� �������
    INT16U	heightRMS; //������ �������� �� ������
    INT32S	vLat; //�������� �� ������
    INT32S	vLon; //�������� �� �������
    INT32S	vHeight; //�������� �� ������
    INT8U	HDOP;
    INT8U	VDOP;
    INT8U	TDOP;
    INT32U	pvtStatus; //������ �������**
    INT8U	nGPS; //���������� GPS, ������������ � �������
    INT8U	nGLN; //���������� �������, ������������ � �������
    INT8U	nGLL; //���������� Galileo, ������������ � �������
    INT8U	nSBAS; //���������� SBAS, ������������ � �������

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
