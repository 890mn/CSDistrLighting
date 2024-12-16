import QtQuick 2.15
import QtQuick.Controls 2.15
import FluentUI
import QtQuick.Layouts

Item {

    RowLayout {
        width: parent.width * 0.7
        height: parent.height
        Layout.fillWidth: true
        x: 80

        Rectangle {
            color: "transparent"
            border.color: "transparent"
            Text {
                text: qsTr("区块 1")
                anchors.centerIn: parent
                font.pixelSize: 20
                font.family: smileFont.name
                color: globalTextColor
            }
        }
        Rectangle {
            color: "transparent"
            border.color: "transparent"
            Text {
                text: qsTr("区块 2")
                anchors.centerIn: parent
                font.pixelSize: 20
                font.family: smileFont.name
                color: globalTextColor
            }
        }
        Rectangle {
            color: "transparent"
            border.color: "transparent"
            Text {
                text: qsTr("区块 3")
                anchors.centerIn: parent
                font.pixelSize: 20
                font.family: smileFont.name
                color: globalTextColor
            }
        }
    }

    FluFilledButton {
        text: qsTr("返回主页 / Back")
        font.pixelSize: 25
        font.family: smileFont.name
        implicitWidth: font.pixelSize * text.length * 0.6
        implicitHeight: font.pixelSize * 1.7
        anchors {
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
        onClicked: {
            returnToHome()
        }
    }
}
