#include "linuxdevicemonitor.h"

LinuxDeviceMonitor::LinuxDeviceMonitor(QObject *parent)
    : QObject(parent)
{
    _serialPortNames = getSerialPortNames();
    _networkNames = getNetworkNames();
    qDebug() << "初始化设备";
    qDebug() <<"串口："<< _serialPortNames;
        qDebug() <<"网卡："<< _networkNames;
                    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LinuxDeviceMonitor::update);
}

LinuxDeviceMonitor::~LinuxDeviceMonitor(){timer->stop();}

QList<QString> LinuxDeviceMonitor::getSerialPortNames()
{
    QList<QString> serialPortNames;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        serialPortNames.append(info.portName());
    }
    return serialPortNames;
}

QList<QString> LinuxDeviceMonitor::getNetworkNames()
{
    QList<QString> networkNames;
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface interfaceItem, list) {
        if (!interfaceItem.isValid())
            continue;
        QList<QNetworkAddressEntry> addressEntryList = interfaceItem.addressEntries();
        foreach(QNetworkAddressEntry addressEntryItem, addressEntryList)
        {
            if(addressEntryItem.ip().protocol()==QAbstractSocket::IPv4Protocol&&
                addressEntryItem.ip().toString().left(3)=="192")
            {
                networkNames.append(interfaceItem.name());
            }
        }
    }
    return networkNames;
}

QMap<QString, QList<QString>> LinuxDeviceMonitor::getAllDevice()
{
    QMap<QString, QList<QString>> allDevice;
    allDevice.insert("network", _networkNames);
    allDevice.insert("serialPort",_serialPortNames);
    return allDevice;
}

void LinuxDeviceMonitor::start()
{
    timer->start(2000);
}

void LinuxDeviceMonitor::update()
{
    QList<QString> serialPortNames = getSerialPortNames();
    QList<QString> networkNames = getNetworkNames();
    if(_serialPortNames != serialPortNames)
    {
        if (serialPortNames.length() > _serialPortNames.length())
        {
            _serialPortNames = serialPortNames;
            emit deviceChanged("串口插入");
        }

        if (serialPortNames.length() < _serialPortNames.length())
        {
            _serialPortNames = serialPortNames;
            emit deviceChanged("串口拔出");
        }
    }
    if(_networkNames != networkNames)
    {
        if(networkNames.length()  > _networkNames.length())
        {
            _networkNames = networkNames;
            emit deviceChanged("网卡连接");
        }
        if(networkNames.length()  < _networkNames.length())
        {
            _networkNames = networkNames;
            emit deviceChanged("网卡断开");
        }
    }
}
