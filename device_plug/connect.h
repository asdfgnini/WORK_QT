#ifndef CONNECT_H
#define CONNECT_H

#include <QObject>


#include "linuxdevicemonitor.h"


class Connect : public QObject
{
    Q_OBJECT
public:
    explicit Connect(QObject *parent = nullptr);

private:
    LinuxDeviceMonitor* device;

signals:


public slots:
    void deviceChanged(QString msg);
};

#endif // CONNECT_H
