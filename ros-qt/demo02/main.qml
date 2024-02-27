import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import Interaction 1.0
import Sekiro

ApplicationWindow
{
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property string ros_vlaue: ""


    //SekProgressButton
    Timer{
        id:timer_progress
        interval: 200
        onTriggered: {
            btn_progress.progress = (btn_progress.progress + 0.1).toFixed(1)
            if(btn_progress.progress==1){
                timer_progress.stop()
            }else{
                timer_progress.start()
            }
        }
    }

    SekProgressButton{
        id:btn_progress
        text:"Progress Button"
        onClicked: {
            btn_progress.progress = 0
            timer_progress.restart()
        }
    }



    //交互
    Interaction{
        id:interaction

    }

    // Connections{
    //     id:connects
    //     target: interaction

    //     function onRos_value(value)
    //     {
    //         ros_vlaue = value
    //     }
    // }
    Component.onCompleted: {
        interaction.start_ros();
    }

}
