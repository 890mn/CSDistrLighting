import QtQuick 2.15
import FluentUI 1.0

Item {
    // 新的仿真布局
    Column {
        id: simulationLayout
        anchors.fill: parent

        // 上方区域，占九成
        Row {
            id: topSection
            height: parent.height * 0.9
            width: parent.width

            // 左边画布区域，占六成
            Rectangle {
                id: simulationCanvas
                width: parent.width * 0.6
                height: parent.height
                radius: 10
                border.color: "#c0c0c0"
                border.width: 2
                // 不填充，显示背景颜色
            }

            // 右边竖向排列的几个区块，占四成，且随着窗口大小调整
            Column {
                id: rightColumn
                width: parent.width * 0.4
                height: parent.height
                spacing: 20

                // 和左上侧一样高的圆角矩形，长度是左右两块六四分
                Rectangle {
                    width: parent.width * 0.4
                    height: simulationCanvas.height
                    radius: 10
                    border.color: "#a0a0a0"
                    border.width: 2
                    clip: true

                    // 可滚动的长条区域
                    Flickable {
                        anchors.fill: parent
                        contentHeight: childrenRect.height
                        width: parent.width * 0.4 - 20
                        height: parent.height

                        Column {
                            spacing: 20
                            // 先是四个长条圆角矩形顺序堆叠
                            Rectangle {
                                width: parent.width * 0.4 - 40 // 确保与父容器宽度保持一致
                                height: 60
                                color: "transparent"
                                radius: 10
                                border.color: "#a0a0a0"
                                border.width: 2
                                Text {
                                    text: "区块 1"
                                    anchors.centerIn: parent
                                    font.pixelSize: 20
                                    color: globalTextColor
                                }
                            }
                            Rectangle {
                                width: parent.width * 0.4 - 40
                                height: 60
                                color: "transparent"
                                radius: 10
                                border.color: "#a0a0a0"
                                border.width: 2
                                Text {
                                    text: "区块 2"
                                    anchors.centerIn: parent
                                    font.pixelSize: 20
                                    color: globalTextColor
                                }
                            }
                            Rectangle {
                                width: parent.width * 0.4 - 40
                                height: 60
                                color: "transparent"
                                radius: 10
                                border.color: "#a0a0a0"
                                border.width: 2
                                Text {
                                    text: "区块 3"
                                    anchors.centerIn: parent
                                    font.pixelSize: 20
                                    color: globalTextColor
                                }
                            }
                            Rectangle {
                                width: parent.width * 0.4 - 40
                                height: 60
                                color: "transparent"
                                radius: 10
                                border.color: "#a0a0a0"
                                border.width: 2
                                Text {
                                    text: "区块 4"
                                    anchors.centerIn: parent
                                    font.pixelSize: 20
                                    color: globalTextColor
                                }
                            }
                            // 两个按钮组成的row
                            Row {
                                spacing: 20
                                FluFilledButton {
                                    text: qsTr("按钮 1")
                                    font.pixelSize: 20
                                    implicitWidth: font.pixelSize * text.length * 0.65
                                    implicitHeight: font.pixelSize * 1.7
                                }
                                FluFilledButton {
                                    text: qsTr("按钮 2")
                                    font.pixelSize: 20
                                    implicitWidth: font.pixelSize * text.length * 0.65
                                    implicitHeight: font.pixelSize * 1.7
                                }
                            }
                            // 一个按钮组成的row
                            Row {
                                FluFilledButton {
                                    text: qsTr("按钮 3")
                                    font.pixelSize: 20
                                    implicitWidth: font.pixelSize * text.length * 0.65
                                    implicitHeight: font.pixelSize * 1.7
                                }
                            }
                        }
                    }
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
                font.pixelSize: 16
                color: globalTextColor
                font.family: smileFont.name
                font.bold: true
                text: qsTr("愿你在仿真的世界沐浴五束阳光 |")
            }
            FluText{
                font.pixelSize: 16
                font.family: smileFont.name
                font.bold: true
                text: " CSDLighting-Si"
                color: cosFTextColor
            }
            FluText{
                anchors.centerIn: parent.centerIn
                font.pixelSize: 14
                text: "ver.0.1 "
                font.family: brushFont.name
                color: cosFSextColor
            }
        }
    }
}
