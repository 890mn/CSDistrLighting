import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
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

                    // Expanded content
                    Column {
                        visible: model.expanded
                        spacing: 10
                        width: parent.width

                        Repeater {
                            model: ListModel {
                                ListElement { label: "强度"; min: 0; max: 100; property: "intensity" }
                                ListElement { label: "位置 X"; min: 0; max: 600; property: "positionX" }
                                ListElement { label: "位置 Y"; min: 0; max: 400; property: "positionY" }
                            }

                            delegate: Row {
                                spacing: 10
                                width: parent.width

                                Text {
                                    text: model.label
                                    font.pixelSize: 18
                                    font.family: smileFont.name
                                }

                                FluSlider {
                                    id: slider
                                    width: parent.width - 180
                                    from: model.min
                                    to: model.max
                                    value: lightSources.get(index) && lightSources.get(index)[model.property] !== undefined
                                        ? lightSources.get(index)[model.property]
                                        : 0 // 默认值

                                    onValueChanged: {
                                        // 检查是否能正确获取对象
                                        let lightData = lightSources.get(index);
                                        if (lightData) {
                                            lightData[model.property] = value;
                                            lightSources.set(index, lightData);
                                        }
                                    }
                                }

                                FluTextBox {
                                    text: slider.value.toFixed(0)
                                    font.pixelSize: 16
                                    font.family: smileFont.name
                                    width: 80
                                    height: 30
                                    inputMethodHints: Qt.ImhDigitsOnly
                                    onEditingFinished: {
                                        let newValue = parseInt(text);
                                        if (!isNaN(newValue) && newValue >= slider.from && newValue <= slider.to) {
                                            slider.value = newValue;
                                        } else {
                                            text = slider.value.toFixed(0); // 恢复合法值
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
}
