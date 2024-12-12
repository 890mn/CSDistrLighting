import QtQuick 2.15
import FluentUI 1.0

Item {
    signal startSimulation()

    Column {
        id: mainState
        anchors.left: parent.left
        anchors.leftMargin: 10
        spacing: 15
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 100 // 调整竖向 offset

        opacity: 1

        FluText {
            text: qsTr("仿真 · 照度模拟")
            color: cosFTextColor
            font.pixelSize: mainWindow.height / 11
            font.family: smileFont.name
        }

        Row {
            FluText {
                text: qsTr("调控算法验证平台 |")
                color: globalTextColor
                font.pixelSize: mainWindow.height / 18
                font.family: smileFont.name
            }
            FluText {
                anchors.bottom: parent.bottom
                text: qsTr(" Powered By Qt6")
                color: globalTextColor
                font.pixelSize: mainWindow.height / 22
                font.family: smileFont.name
            }
        }

        Row {
            id: buttonRow
            spacing: 20
            baselineOffset: 20
            FluFilledButton {
                id: startSimButton
                text: qsTr("开始仿真 / Start")
                font.pixelSize: mainWindow.height / 22
                font.family: smileFont.name
                implicitWidth: font.pixelSize * text.length * 0.65
                implicitHeight: font.pixelSize * 1.7

                onClicked: {
                    startSimulation()
                }
            }
            FluFilledButton {
                text: qsTr("环境设置 / Setting")
                font.pixelSize: mainWindow.height / 22
                font.family: smileFont.name
                implicitWidth: font.pixelSize * text.length * 0.6
                implicitHeight: font.pixelSize * 1.7
            }
        }
    }

    // 下方区域，右边内容
    Row {
        anchors{
            bottom: parent.bottom
            bottomMargin: 10
            right: parent.right
        }
        FluText{
            font.pixelSize: mainWindow.height / 30
            color: globalTextColor
            font.family: smileFont.name
            font.bold: true
            text: qsTr("愿你在仿真的世界沐浴五束阳光 |")
        }
        FluText{
            font.pixelSize: mainWindow.height / 30
            font.family: smileFont.name
            font.bold: true
            text: " CSDLighting-Silver.0.1    "
            color: cosFTextColor
        }
    }
}
