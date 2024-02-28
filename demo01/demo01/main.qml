import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4

import Interaction 1.0
import TaoQuick 1.0

import "./Qml/Dialog"
import "./Qml/Pane"

ApplicationWindow {
    id: rootBackground
    width: 1440
    height: 960
    visible: true //设置可见性
    CusImage{
        id: bgImg
        source: "qrc:/Image/Window/flower.jpg"
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        opacity: 0.1
    }
    CusFPS {
        anchors {
            right: parent.right
            top: parent.top
            rightMargin: 5
        }
    }

    LeftPane {
        id: leftPane
        objectName: "leftPane"
        property real targetW: parent.width * 0.233
        width: targetW
        height: parent.height
        property bool isOpen: true
        x: isOpen ? 0 : -targetW - 4
        Behavior on x {
            NumberAnimation { duration: 350}
        }
        onLoadHome: function() {
            rightPane.source = rightPane.homeUrl
        }
        onLoadContent: function(path) {
            rightPane.source = "qrc:/Contents/" + path
        }
    }

    CusButton_Red {
        icon.source: "qrc:/Image/Common/view02.png"
        objectName: "menuBtn"
        anchors {
            left: leftPane.right
            top: leftPane.top
            topMargin: 2
        }
        width: 32
        height: 32
        onClicked: {
            leftPane.isOpen = !leftPane.isOpen
        }
    }

    Rectangle {
        width: 1
        anchors {
            top: leftPane.top
            bottom: leftPane.bottom
            right: leftPane.right
        }
        color: CusConfig.controlBorderColor
    }

    RightPane {
        id: rightPane
        objectName: "contentRect"
        anchors {
            left: leftPane.right
            leftMargin: 40
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
    }

    Interaction{
        id:interaction
    }

    Component.onCompleted: {
        interaction.start_ros()
    }

}
