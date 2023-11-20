import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import Qt.labs.settings 1.0
import "Style"
import Connect 1.0


ApplicationWindow {
    id:root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    //GPS
    property int gps_weidu: 0
    property int gps_jingdu: 0


    //力矩
    property int liju_Fx: 0
    property int liju_Fy: 0
    property int liju_Fz: 0
    property int liju_Mx: 0
    property int liju_My: 0
    property int liju_Mz: 0

    property int timer: 0


    //顶部返回图案
    header: NaviButton {
        id: homeButton

        edge: Qt.TopEdge
        enabled: stackView.depth > 1
        imageSource: "images/home.png"

        onClicked: stackView.pop(null)
    }

    StackView{
        id:stackView
        focus: true
        anchors.fill: parent
        initialItem: LauncherPage {
            id:launcherPage
        }
    }

    function onpush(page)
    {
        stackView.push(page)
    }
    Connect{
        id:connect
    }


    Connections{
        target: connect
        function onScreen(wight,height)
        {
            root.width = wight
            root.height = height

        }
        //GPS
        function onGps_Data(weidu,jingdu,haiba)
        {
//            weidu_data.text = weidu;
//            jingdu_data.text = jingdu;
//            haiba_data.text = haiba;
        }
        function onGps_Data_draw(weidu,jingdu,haiba)
        {
            gps_weidu = Number(weidu)
            gps_jingdu = Number(jingdu)

        }

        //力矩
        function onLiju_Data(Fx,Fy,Fz,Mx,My,Mz)
        {
//            fx_data.text = Fx;
//            fy_data.text = Fy;
//            fz_data.text = Fz;
//            mx_data.text = Mx;
//            my_data.text = My;
//            mz_data.text = Mz;
        }
        function onLiju_Data_draw(Fx,Fy,Fz,Mx,My,Mz)
        {
            liju_Fx = Fx
            liju_Fy = Fy
            liju_Fz = Fz
            liju_Mx = Mx
            liju_My = My
            liju_Mz = Mz
        }

    }
    Component.onCompleted: {
        launcherPage.launched.connect(onpush)

//        connect.start();
        connect.init_udpsocket()

    }
}
