#include "connect.h"

Connect::Connect(QObject *parent)
    : QObject{parent}
{

    device = new LinuxDeviceMonitor(this);
    connect(device,&LinuxDeviceMonitor::deviceChanged,this,&Connect::deviceChanged);
    device->start();
}


void Connect::deviceChanged(QString msg)
{
    qDebug() << device->getAllDevice();
//    QMessageBox::information(this, tr("设备"),"Linux设备变动：" + msg);
    qDebug() << msg;
}
