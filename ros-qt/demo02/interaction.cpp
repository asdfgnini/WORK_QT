#include "interaction.h"

Interaction::Interaction(QObject *parent)
    : QObject{parent}
{
    connect(&control,&Controller::Send_value,this,&Interaction::Receive_value);

}

void Interaction::start_ros()
{
    control.start();
}



void Interaction::Receive_value(QString value)
{
    qDebug() << "ros value: " <<  value;
    emit ros_value(value);
}
