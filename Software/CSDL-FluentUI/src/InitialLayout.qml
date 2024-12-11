import QtQuick 2.15
import FluentUI 1.0

Item {
    signal startSimulation()

    Column {
        id: mainState
        anchors.left: parent.left
        anchors.leftMargin: 10
        spacing: 20
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 100 // 调整竖向 offset

        opacity: 1

        FluText {
            text: qsTr("仿真 · 照度模拟")
            color: globalTextColor
            font.pixelSize: 60
            font.family: smileFont.name
        }

        Row {
            FluText {
                text: qsTr("基于CSDLighting的仿真验证软件开发 |")
                color: globalTextColor
                font.pixelSize: 35
                font.family: smileFont.name
            }
            FluText {
                anchors.bottom: parent.bottom
                text: qsTr(" Powered By Qt6 / FluentUI")
                color: globalTextColor
                font.pixelSize: 25
                font.family: smileFont.name
            }
        }

        Row {
            id: buttonRow
            spacing: 20
            FluFilledButton {
                id: startSimButton
                text: qsTr("开始仿真 / Start")
                font.pixelSize: 30
                font.family: smileFont.name
                implicitWidth: font.pixelSize * text.length * 0.65
                implicitHeight: font.pixelSize * 1.7
                onClicked: {
                    startSimulation()
                }
            }
            FluFilledButton {
                text: qsTr("环境设置 / Setting")
                font.pixelSize: 30
                font.family: smileFont.name
                implicitWidth: font.pixelSize * text.length * 0.6
                implicitHeight: font.pixelSize * 1.7
            }
        }
    }
}
