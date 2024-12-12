import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Rectangle {
    id: lightSettings
    width: parent.width - 20
    height: 190
    radius: 10
    border.color: "#a0a0a0"

    Column {
        anchors.fill: parent
        spacing: 10
        padding: 10

        Text {
            text: qsTr("光源设置")
            font.pixelSize: 25
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
                    text: model.label
                    font.pixelSize: 20
                    width: 80
                }

                Slider {
                    id: sliderControl
                    width: parent.width - 180
                    from: model.min
                    to: model.max
                    value: (model.min + model.max) / 2
                }

                Text {
                    text: sliderControl.value.toFixed(0)
                    font.pixelSize: 20
                    width: 50
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
    }
}
