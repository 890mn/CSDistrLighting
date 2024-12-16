import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import FluentUI

Rectangle {
    id: lightSettings
    width: parent.width - 20
    height: 210
    radius: 10
    border.color: "#a0a0a0"
    color: "white"

    Column {
        anchors.fill: parent
        spacing: 10
        padding: 20

        Text {
            text: qsTr("光源设置")
            font.pixelSize: 25
            font.family: smileFont.name
        }

        Repeater {
            model: ListModel {
                ListElement { label: "强度"; min: 0; max: 100 }
                ListElement { label: "位置 X"; min: 0; max: 600 }
                ListElement { label: "位置 Y"; min: 0; max: 400 }
            }

            delegate: Row {
                spacing: 10
                width: parent.width

                Text {
                    y: 5
                    text: model.label
                    font.pixelSize: 18
                    font.family: smileFont.name
                    height: 40
                }

                FluSlider {
                    id: sliderControl
                    width: parent.width - 180
                    from: model.min
                    to: model.max
                    value: (model.min + model.max) / 2
                }

                FluTextBox {
                    text: sliderControl.value.toFixed(0)
                    font.pixelSize: 16
                    font.family: smileFont.name
                    width: 80
                    height: 30
                    inputMethodHints: Qt.ImhDigitsOnly
                    onEditingFinished: {
                        let newValue = parseInt(text);
                        if (!isNaN(newValue) && newValue >= sliderControl.from && newValue <= sliderControl.to) {
                            sliderControl.value = newValue;
                        } else {
                            text = sliderControl.value.toFixed(0); // 恢复为合法值
                        }
                    }
                }
            }
        }
    }
}
