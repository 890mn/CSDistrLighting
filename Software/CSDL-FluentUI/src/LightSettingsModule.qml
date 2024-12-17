import QtQuick 2.15
import QtQuick.Controls 2.15
import FluentUI

Rectangle {
    id: lightSettings
    width: parent.width - 20
    height: 400
    radius: 10
    border.color: "#a0a0a0"
    color: "white"

    property alias lightSources: lightList.model
    Component.onCompleted: {
        simulationCanvas.lightSources = lightSources; // 绑定外部模型
    }

    Column {
        anchors.fill: parent
        spacing: 10
        padding: 20

        Row {
            spacing: 10
            width: parent.width

            Text {
                text: qsTr("光源设置")
                font.pixelSize: 25
                font.family: smileFont.name
            }

            Button {
                text: qsTr("添加光源")
                onClicked: {
                    lightSources.append({
                        "name": "光源 " + (lightSources.count + 1),
                        "intensity": 50,
                        "positionX": 300,
                        "positionY": 200,
                        "expanded": false // 初始化展开状态
                    });
                }
            }
        }

        ListView {
            id: lightList
            width: parent.width
            height: parent.height - 80
            spacing: 10
            model: ListModel { } // 初始化空模型
            delegate: Rectangle {
                id: lightItem
                width: parent.width
                height: model.expanded ? 150 : 50
                radius: 5
                border.color: "#d0d0d0"
                color: "lightgray"

                Column {
                    anchors.fill: parent
                    spacing: 10
                    padding: 10

                    Row {
                        spacing: 10
                        width: parent.width - 20

                        Text {
                            text: model.name
                            font.pixelSize: 20
                            font.family: smileFont.name
                        }

                        Button {
                            text: model.expanded ? qsTr("折叠") : qsTr("展开")
                            onClicked: {
                                // 更新展开状态
                                if (lightSources.get(index)) {
                                    lightSources.set(index, {
                                        name: model.name,
                                        intensity: model.intensity,
                                        positionX: model.positionX,
                                        positionY: model.positionY,
                                        expanded: !model.expanded
                                    });
                                }
                            }
                        }

                        Button {
                            text: qsTr("删除")
                            onClicked: lightSources.remove(index)
                        }
                    }

                    // Expanded content: 使用 Column 来排列属性
                    Column {
                        visible: model.expanded
                        spacing: 10
                        width: parent.width

                        // 强度调整
                        Row {
                            spacing: 10
                            width: parent.width

                            Text {
                                text: qsTr("强度")
                                font.pixelSize: 18
                                font.family: smileFont.name
                            }

                            FluSlider {
                                id: intensitySlider
                                width: parent.width - 180
                                from: 0
                                to: 100
                                value: model.intensity

                                onValueChanged: {
                                    let lightData = lightSources.get(index);
                                    if (lightData) {
                                        lightData.intensity = value;
                                        lightSources.set(index, {
                                            name: lightData.name,
                                            intensity: lightData.intensity,
                                            positionX: lightData.positionX,
                                            positionY: lightData.positionY,
                                            expanded: lightData.expanded
                                        });
                                    }
                                }
                            }

                            FluTextBox {
                                text: intensitySlider.value.toFixed(0)
                                font.pixelSize: 16
                                font.family: smileFont.name
                                width: 80
                                height: 30
                                inputMethodHints: Qt.ImhDigitsOnly
                                onEditingFinished: {
                                    let newValue = parseInt(text);
                                    if (!isNaN(newValue) && newValue >= intensitySlider.from && newValue <= intensitySlider.to) {
                                        intensitySlider.value = newValue;
                                    } else {
                                        text = intensitySlider.value.toFixed(0); // 恢复合法值
                                    }
                                }
                            }
                        }

                        // 位置 X 调整
                        Row {
                            spacing: 10
                            width: parent.width

                            Text {
                                text: qsTr("位置 X")
                                font.pixelSize: 18
                                font.family: smileFont.name
                            }

                            FluSlider {
                                id: positionXSlider
                                width: parent.width - 180
                                from: 0
                                to: 600
                                value: model.positionX

                                onValueChanged: {
                                    let lightData = lightSources.get(index);
                                    if (lightData) {
                                        lightData.positionX = value;
                                        lightSources.set(index, {
                                            name: lightData.name,
                                            intensity: lightData.intensity,
                                            positionX: lightData.positionX,
                                            positionY: lightData.positionY,
                                            expanded: lightData.expanded
                                        });
                                    }
                                }
                            }

                            FluTextBox {
                                text: positionXSlider.value.toFixed(0)
                                font.pixelSize: 16
                                font.family: smileFont.name
                                width: 80
                                height: 30
                                inputMethodHints: Qt.ImhDigitsOnly
                                onEditingFinished: {
                                    let newValue = parseInt(text);
                                    if (!isNaN(newValue) && newValue >= positionXSlider.from && newValue <= positionXSlider.to) {
                                        positionXSlider.value = newValue;
                                    } else {
                                        text = positionXSlider.value.toFixed(0); // 恢复合法值
                                    }
                                }
                            }
                        }

                        // 位置 Y 调整
                        Row {
                            spacing: 10
                            width: parent.width

                            Text {
                                text: qsTr("位置 Y")
                                font.pixelSize: 18
                                font.family: smileFont.name
                            }

                            FluSlider {
                                id: positionYSlider
                                width: parent.width - 180
                                from: 0
                                to: 400
                                value: model.positionY

                                onValueChanged: {
                                    let lightData = lightSources.get(index);
                                    if (lightData) {
                                        lightData.positionY = value;
                                        lightSources.set(index, {
                                            name: lightData.name,
                                            intensity: lightData.intensity,
                                            positionX: lightData.positionX,
                                            positionY: lightData.positionY,
                                            expanded: lightData.expanded
                                        });
                                    }
                                }
                            }

                            FluTextBox {
                                text: positionYSlider.value.toFixed(0)
                                font.pixelSize: 16
                                font.family: smileFont.name
                                width: 80
                                height: 30
                                inputMethodHints: Qt.ImhDigitsOnly
                                onEditingFinished: {
                                    let newValue = parseInt(text);
                                    if (!isNaN(newValue) && newValue >= positionYSlider.from && newValue <= positionYSlider.to) {
                                        positionYSlider.value = newValue;
                                    } else {
                                        text = positionYSlider.value.toFixed(0); // 恢复合法值
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
