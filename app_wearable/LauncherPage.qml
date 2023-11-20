import QtQuick 2.15
import QtQuick.Controls 2.15
import "./Style"


PathView{
    id:pathview

    signal launched(string page)

    readonly property int cX: width / 2
    readonly property int cY: height / 2
    readonly property int size: Math.min(width - 80, height)
    readonly property int itemSize: size / 4
    readonly property int radius: size / 2 - itemSize / 3

    snapMode: PathView.SnapToItem

    model: ListModel {
        ListElement {
            title: qsTr("位置传感器")
            icon: "worldclock"
            page: "GPS/GPS.qml"
        }
        ListElement {
            title: qsTr("速度传感器")
            icon: "navigation"
            page: "SPEED/SPEED.qml"
        }
        ListElement {
            title: qsTr("姿态传感器")
            icon: "weather"
            page: "IMU/IMU.qml"
        }
        ListElement {
            title: qsTr("测距传感器")
            icon: "fitness"
            page: "CEJU/CEJU.qml"
        }
        ListElement {
            title: qsTr("视觉传感器")
            icon: "notifications"
            page: "SHIJU/SHIJU.qml"
        }
        ListElement {
            title: qsTr("力矩传感器")
            icon: "alarms"
            page: "LIJU/LIJU.qml"
        }
        ListElement {
            title: qsTr("触觉传感器")
            icon: "settings"
            page: "LIJU/LIJU.qml"
        }
    }
    //委托
    delegate: RoundButton{
        width:pathview.itemSize
        height:pathview.itemSize

        property string title: model.title

        icon.width: 36
        icon.height: 36
        icon.source: "/images/36x36/" + model.icon + ".png"
        opacity: PathView.itemOpacity
        padding: 12

        background: Rectangle {
            radius: width / 2
            border.width: 3
            border.color: parent.PathView.isCurrentItem ? UIStyle.colorQtPrimGreen : UIStyle.themeColorQtGray4
        }

        onClicked: {
            if(PathView.isCurrentItem)
            {
                pathview.launched(Qt.resolvedUrl(page))
            }
            else
            {
                pathview.currentIndex = index

            }
        }
    }
    path: Path {
        startX: pathview.cX
        startY: pathview.cY
        PathAttribute {
            name: "itemOpacity"
            value: 1.0
        }
        PathLine {
            x: pathview.cX + pathview.radius
            y: pathview.cY
        }
        PathAttribute {
            name: "itemOpacity"
            value: 0.7
        }
        PathArc {
            x: pathview.cX - pathview.radius
            y: pathview.cY
            radiusX: pathview.radius
            radiusY: pathview.radius
            useLargeArc: true
            direction: PathArc.Clockwise
        }
        PathAttribute {
            name: "itemOpacity"
            value: 0.5
        }
        PathArc {
            x: pathview.cX + pathview.radius
            y: pathview.cY
            radiusX: pathview.radius
            radiusY: pathview.radius
            useLargeArc: true
            direction: PathArc.Clockwise
        }
        PathAttribute {
            name: "itemOpacity"
            value: 0.3
        }
    }
    Text {
        id: appTitle

        property Item currentItem: pathview.currentItem

        visible: currentItem ? currentItem.PathView.itemOpacity === 1.0 : 0

        text: currentItem ? currentItem.title : ""
        anchors.centerIn: parent
        anchors.verticalCenterOffset: (pathview.itemSize + height) / 2

        font.bold: true
        font.pixelSize: UIStyle.fontSizeL
        font.letterSpacing: 1
        color: UIStyle.themeColorQtGray1
    }

}
