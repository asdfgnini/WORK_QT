#ifndef INTERACTION_H
#define INTERACTION_H

#include <QObject>
#include <QDebug>
#include "thread/worker.h"


class Interaction : public QObject
{
    Q_OBJECT
public:
    explicit Interaction(QObject *parent = nullptr);

    Q_INVOKABLE void start_ros();

private:
    Controller control;
signals:

    void ros_value(QString value);
public slots:
    void Receive_value(QString value); //接收来自线程的数据


};

#endif // INTERACTION_H
