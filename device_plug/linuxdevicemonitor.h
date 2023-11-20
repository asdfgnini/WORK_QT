#ifndef LINUXDEVICEMONITOR_H
#define LINUXDEVICEMONITOR_H

#include <QObject>
#include <QTimer>
#include <QSerialPortInfo>
#include <QNetworkInterface>
#include <QDebug>
#include <QMap>

class LinuxDeviceMonitor : public QObject
{
    Q_OBJECT

public:
    LinuxDeviceMonitor(QObject *parent = 0);
    ~LinuxDeviceMonitor();
    QList<QString> getSerialPortNames();
    QList<QString> getNetworkNames();
    QMap<QString, QList<QString>> getAllDevice();
    void start();
    void update();
signals:
    void deviceChanged(QString);
private:
    QTimer *timer;
    QList<QString> _serialPortNames;
    QList<QString> _networkNames;
};

#endif // LINUXDEVICEMONITOR_H
