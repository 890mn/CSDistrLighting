import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: additionalModule
    width: parent.width - 20
    height: 160
    radius: 10
    border.color: "#a0a0a0"

    Text {
        anchors.centerIn: parent
        text: qsTr("扩展模块")
        font.pixelSize: 20
    }
}
