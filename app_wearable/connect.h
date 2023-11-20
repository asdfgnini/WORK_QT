#ifndef CONNECT_H
#define CONNECT_H

#include <QObject>
#include <QDebug>
#include <QGuiApplication>
#include <QRect>
#include <QScreen>
#include <QUdpSocket>
#include <QNetworkDatagram>

class Connect : public QObject
{
    Q_OBJECT
public:
    explicit Connect(QObject *parent = nullptr);
    bool GPS_parser();//解析GPS
    bool LIJU_parser();//解析力矩

public:
    Q_INVOKABLE void start();
    Q_INVOKABLE void init_udpsocket();


private:
    QUdpSocket* udpsocket = nullptr;
    QHostAddress loacal_address;
    QByteArray arry;//原始数据
    //GPS
    QByteArray GPS_arry;//原始数据
    QByteArray weidu;//纬度
    QByteArray jingdu;//纬度
    QByteArray haiba;//海拔

    //力矩
    QByteArray LIJU_arry;//原始数据
    QByteArray Fx;
    QByteArray Fy;
    QByteArray Fz;
    QByteArray Mx;
    QByteArray My;
    QByteArray Mz;



signals:
    void screen(int weight,int heigh);

    void gps_Data(QString weidu,QString jingdu,QString haiba);
    void gps_Data_draw(QString weidu,QString jingdu,QString haiba);

    void liju_Data(QString Fx,QString Fy,QString Fz,QString Mx,QString My,QString Mz);
    void liju_Data_draw(QString Fx,QString Fy,QString Fz,QString Mx,QString My,QString Mz);

public slots:
    void readPendingDatagrams();

};

#endif // CONNECT_H
