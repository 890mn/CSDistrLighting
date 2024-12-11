import QtQuick 2.15
import QtQuick.Layouts 1.3
import FluentUI 1.0

Item {
    signal returnToHome()

    // 新的仿真布局
    Column {
        id: simulationLayout
        anchors.fill: parent

        // 上方区域，占九成
        Row {
            id: topSection
            height: parent.height * 0.9
            width: mainWindow.width
            padding: 5
            spacing: 5

            // 左边画布区域，占六成
            Rectangle {
                id: simulationCanvas
                width: mainWindow.width * 0.6 - 10
                height: parent.height
                radius: 10
                border.color: "#c0c0c0"
                border.width: 2
                color: "transparent"
            }

            // 右边竖向排列的几个区块，占四成，且随着窗口大小调整
            Column {
                id: rightColumn
                width: mainWindow.width * 0.4 - 10
                height: parent.height

                // 和左上侧一样高的圆角矩形，长度是左右两块六四分
                Rectangle {
                    id: rightRect
                    width: rightColumn.width
                    height: simulationCanvas.height
                    radius: 10
                    border.color: "#a0a0a0"
                    border.width: 2
                    clip: true

                    // 可滚动的长条区域
                    Flickable {
                        anchors.fill: parent
                        contentHeight: childrenRect.height
                        width: rightColumn.width
                        height: parent.height


                        Column {
                            spacing: 20
                            // 先是四个长条圆角矩形顺序堆叠
                            Rectangle {
                                width: parent.width
                                height: 160
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
                                width: parent.width
                                height: 160
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
                                width: rightRect.width
                                height: 160
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
                                width: rightRect.width - 40
                                height: 160
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
                                    implicitWidth: rightRect.width / 2 - 20
                                    implicitHeight: font.pixelSize * 1.7
                                }
                                FluFilledButton {
                                    text: qsTr("按钮 2")
                                    font.pixelSize: 20
                                    implicitWidth: rightRect.width / 2 - 20
                                    implicitHeight: font.pixelSize * 1.7
                                }
                            }
                            // 一个按钮组成的row
                            Row {
                                FluFilledButton {
                                    text: qsTr("按钮 3")
                                    font.pixelSize: 20
                                    implicitWidth: rightRect.width - 20
                                    implicitHeight: font.pixelSize * 1.7
                                }
                            }
                        }
                    }
                }
            }
        }

        // 下方区域，左边放置画布参数，右边是返回按钮
        RowLayout {
            width: parent.width
            height: parent.height * 0.1
            Layout.fillWidth: true

            // 左边区域
            Column {
                Layout.preferredWidth: parent.width * 0.75
                // 这里可以放画布的参数
                FluText {
                    text: "画布参数"
                    font.pixelSize: 20
                    color: globalTextColor
                }
            }


            FluFilledButton {
                text: qsTr("返回主页 / Back")
                font.pixelSize: 25
                font.family: smileFont.name
                implicitWidth: font.pixelSize * text.length * 0.6
                implicitHeight: font.pixelSize * 1.7
                onClicked: {
                    returnToHome()
                }
            }
        }
    }
}
