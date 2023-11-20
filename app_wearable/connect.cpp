#include "connect.h"


Connect::Connect(QObject *parent)
    : QObject{parent}
{

}

void Connect::start()
{
    // 获取多显示器,通过list存储当前主机所有显示器
    QList<QScreen *> list_screen = QGuiApplication::screens();
    int desktop_width = 0;
    int desktop_height = 0;
    // 通过循环可以遍历每个显示器
    for (int i = 0; i < list_screen.size(); i++)
    {
        QRect rect = list_screen.at(i)->geometry();
        desktop_width = rect.width();
        desktop_height = rect.height();
        // 打印屏幕分辨率
        qDebug() << desktop_width <<desktop_height;
    }

    emit screen(desktop_width,desktop_height);
}


void Connect::init_udpsocket()
{
    udpsocket = new QUdpSocket(this);
    loacal_address.setAddress("192.168.10.100");
    udpsocket->bind(loacal_address, 8080);

    connect(udpsocket, &QUdpSocket::readyRead,
            this, &Connect::readPendingDatagrams);
}
//解析GPS
bool Connect::GPS_parser()
{
    int pre_pos = 0;
    int next_pos = 0;
    int len = 0;
    if(GPS_arry.startsWith("GPS:") == false)
    {
        return false;
    }
    //解析纬度
    len = (int)strlen("weidu:");
    pre_pos = GPS_arry.indexOf("weidu:");
    next_pos = GPS_arry.indexOf("jingdu:");
    weidu = GPS_arry.mid(pre_pos + len, (next_pos-2) - (pre_pos + len));
    QString raw_weidu(weidu);
    QString raw_weidu_draw(weidu);
    raw_weidu.append("°");
        //解析经度
        pre_pos = next_pos;
    next_pos = GPS_arry.indexOf("haiba:");
    len = (int)strlen("jingdu:");
    jingdu = GPS_arry.mid(pre_pos + len, (next_pos-2) - (pre_pos + len));
    QString raw_jingdu(jingdu);
    QString raw_jingdu_draw(jingdu);
    raw_jingdu.append("°");

    //解析海拔
    pre_pos = next_pos;
    next_pos = GPS_arry.indexOf("\n");
    len = (int)strlen("haiba:");
    haiba = GPS_arry.mid(pre_pos + len, (next_pos-2) - (pre_pos + len));
    QString raw_haiba(haiba);
    QString raw_haiba_draw(haiba);
    raw_haiba.append("m");

    if((raw_weidu.isEmpty() == false) && (raw_jingdu.isEmpty() == false) && (raw_haiba.isEmpty() == false) )
    {
        emit gps_Data(raw_weidu,raw_jingdu,raw_haiba);
        emit gps_Data_draw(raw_weidu_draw,raw_jingdu_draw,raw_haiba_draw);

    }
    else
    {
        emit gps_Data_draw("0","0","0");
    }

    return true;
}
//解析力矩
bool Connect::LIJU_parser()
{
    int liju_pre_pos = 0;
    int liju_next_pos = 0;
    int len = 0;
    if(LIJU_arry.startsWith("LIJU:") == false)
    {
        return false;
    }
    //解析Fx
    len = (int)strlen("Fx:");
    liju_pre_pos = LIJU_arry.indexOf("Fx:");
    liju_next_pos = LIJU_arry.indexOf("Fy:");
    Fx = LIJU_arry.mid(liju_pre_pos + len, (liju_next_pos-2) - (liju_pre_pos + len));
    QString raw_Fx(Fx);
    QString raw_Fx_draw(Fx);
    raw_Fx.append(QString::fromLocal8Bit("N"));

    //解析Fy
    liju_pre_pos = liju_next_pos;
    len = (int)strlen("Fy:");
    liju_next_pos = LIJU_arry.indexOf("Fz:");
    Fy = LIJU_arry.mid(liju_pre_pos + len, (liju_next_pos-2) - (liju_pre_pos + len));
    QString raw_Fy(Fy);
    QString raw_Fy_draw(Fy);
    raw_Fy.append(QString::fromLocal8Bit("N"));

    //解析Fz
    liju_pre_pos = liju_next_pos;
    len = (int)strlen("Fz:");
    liju_next_pos = LIJU_arry.indexOf("Mx:");
    Fz = LIJU_arry.mid(liju_pre_pos + len, (liju_next_pos-2) - (liju_pre_pos + len));
    QString raw_Fz(Fz);
    QString raw_Fz_draw(Fz);
    raw_Fz.append(QString::fromLocal8Bit("N"));

    //解析Mx
    liju_pre_pos = liju_next_pos;
    len = (int)strlen("Mx:");
    liju_next_pos = LIJU_arry.indexOf("My:");
    Mx = LIJU_arry.mid(liju_pre_pos + len, (liju_next_pos-2) - (liju_pre_pos + len));
    QString raw_Mx(Mx);
    QString raw_Mx_draw(Mx);
    raw_Mx.append("N·m");

    //解析My
    liju_pre_pos = liju_next_pos;
    len = (int)strlen("My:");
    liju_next_pos = LIJU_arry.indexOf("Mz:");
    My = LIJU_arry.mid(liju_pre_pos + len, (liju_next_pos-2) - (liju_pre_pos + len));
    QString raw_My(My);
    QString raw_My_draw(My);
    raw_My.append("N·m");

    //解析Mz
    liju_pre_pos = liju_next_pos;
    len = (int)strlen("Mz:");
    liju_next_pos = LIJU_arry.indexOf("\n");
    Mz = LIJU_arry.mid(liju_pre_pos + len, (liju_next_pos-2) - (liju_pre_pos + len));
    QString raw_Mz(Mz);
    QString raw_Mz_draw(Mz);
    raw_Mz.append("N·m");

    if((raw_Fx.isEmpty() == false) && (raw_Fy.isEmpty() == false) && (raw_Fz.isEmpty() == false) && (raw_Mx.isEmpty() == false) && (raw_My.isEmpty() == false) && (raw_Mz.isEmpty() == false) )
    {
        emit liju_Data(raw_Fx,raw_Fy,raw_Fz,raw_Mx,raw_My,raw_Mz);
        emit liju_Data_draw(raw_Fx_draw,raw_Fy_draw,raw_Fz_draw,raw_Mx_draw,raw_My_draw,raw_Mz_draw);

    }

    return true;
}

//UDP 接收回调
void Connect::readPendingDatagrams()
{
    QNetworkDatagram datagram;
    while (udpsocket->hasPendingDatagrams())
    {
        datagram = udpsocket->receiveDatagram();

        qDebug() <<"[readPendingDatagrams]: " << datagram.data();
    }
    //获取原始数据
    arry = datagram.data();
    //获取GPS数据
    bool re_value = arry.startsWith("GPS:");
    if(re_value == true)
    {
        GPS_arry = datagram.data();

    }
    //获取力矩数据
    re_value = arry.startsWith("LIJU:");
    if(re_value == true)
    {
        LIJU_arry = datagram.data();
    }
    //解析GPS
    GPS_parser();

    //解析LIJU
    LIJU_parser();
}



