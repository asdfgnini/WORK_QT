import QtQuick 2.9
import QtQuick.Controls 2.2
import TaoQuick 1.0

Item {
    anchors.fill: parent
    readonly property color blueNormal: "#1890ff"
    readonly property color blueHover: "#40a9ff"
    readonly property color bluePressed: "#096dd9"

    CusButton_Red{
        text: "点击"
        anchors.centerIn: parent
    }

}
