import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import Interaction 1.0

ApplicationWindow
{
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property string ros_vlaue: ""


    header: ToolBar
    {
       id: toolBar
       RowLayout
       {
           id: rowLayout
           anchors.fill: parent
           ToolButton {
               text: qsTr("IMU")
               onClicked: view.currentIndex = 0
           }
           ToolButton {
               text: qsTr("雷达")
               onClicked: view.currentIndex = 1
           }
           ToolButton {
               text: qsTr("目录2")
               onClicked: view.currentIndex = 2
           }
       }
   }

    SwipeView
    {
        id: view
        anchors.fill: parent
        //[ToolBar修改]2: 修改控件之间的触发逻辑
        //currentIndex: tabBar.currentIndex
        onCurrentIndexChanged:
        {
            //tabBar.currentIndex = currentIndex
            for (var i=0; i<rowLayout.children.length; i++)
            {
                rowLayout.children[i].checked = false
            }
            rowLayout.children[currentIndex].checked = true

            indicator.currentIndex = currentIndex
        }

        //第一页
        Rectangle
        {
            id: firstPage
            color: "steelblue"

            //POLL
            Button{
                id:poll_value
                x:10
                y:20
                text:"poll"
            }
            Button{
                x:poll_value.x + 100
                y:poll_value.y
                text: ros_vlaue
            }
        }

        //第二页
        Image {
            id:                 secondPage
            smooth:             true
            mipmap:             true
            antialiasing:       true
            fillMode:           Image.PreserveAspectFit
            sourceSize.height:  height
            source:             "qrc:/res/find.bmp"
        }
        //第三页
        Image {
            id:                 thirdPage
            smooth:             true
            mipmap:             true
            antialiasing:       true
            fillMode:           Image.PreserveAspectFit
            sourceSize.height:  height
            source:             "qrc:/res/lock.bmp"
        }
    }

    //底部导航小园点
    PageIndicator
    {
        id: indicator
        count: view.count
        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }


    //交互
    Interaction{
        id:interaction


    }

    Connections{
        id:connects
        target: interaction

        function onRos_value(value)
        {
            ros_vlaue = value
        }
    }
    Component.onCompleted: {
        interaction.start_ros();
    }

}
