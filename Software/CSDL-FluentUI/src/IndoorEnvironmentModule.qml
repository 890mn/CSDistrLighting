import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Rectangle {
    id: indoorEnvironment
    width: parent.width - 20
    height: 200
    radius: 10
    border.color: "#a0a0a0"
    color: "#f9f9f9"

    Column {
        anchors.fill: parent
        spacing: 10
        padding: 10

        Text {
            text: qsTr("室内环境")
            font.pixelSize: 25
        }

        Text {
            id: simulationData
            text: qsTr("     大小 [%1] x [%2]").arg(sliderWidth.value.toFixed(0)).arg(sliderHeight.value.toFixed(0))
            font.pixelSize: 20
            font.bold: true
        }

        // 宽度滑块
        Row {
            spacing: 10
            width: parent.width

            Text {
                text: qsTr("宽度")
                font.pixelSize: 20
                width: 80
            }

            Slider {
                id: sliderWidth
                width: parent.width - 200
                height: 30 // 调整滑块高度
                from: 0
                to: 6400
                value: 300
                onValueChanged: {
                    simulationData.text = qsTr("     大小 [%1] x [%2]").arg(value.toFixed(0)).arg(sliderHeight.value.toFixed(0));
                    simulationCanvas.updateRectangle(value, sliderHeight.value);
                    textFieldWidth.text = value.toFixed(0);
                }
            }

            TextField {
                id: textFieldWidth
                text: sliderWidth.value.toFixed(0)
                font.pixelSize: 20
                width: 60
                height: 30
                inputMethodHints: Qt.ImhDigitsOnly
                onEditingFinished: {
                    let newValue = parseInt(text);
                    if (!isNaN(newValue) && newValue >= sliderWidth.from && newValue <= sliderWidth.to) {
                        sliderWidth.value = newValue;
                    } else {
                        text = sliderWidth.value.toFixed(0); // 恢复为合法值
                    }
                }
            }
        }

        // 高度滑块
        Row {
            spacing: 10
            width: parent.width

            Text {
                text: qsTr("长度")
                font.pixelSize: 20
                width: 80
            }

            Slider {
                id: sliderHeight
                width: parent.width - 200
                height: 30 // 调整滑块高度
                from: 0
                to: 6400
                value: 200
                onValueChanged: {
                    simulationData.text = qsTr("     大小 [%1] x [%2]").arg(sliderWidth.value.toFixed(0)).arg(value.toFixed(0));
                    simulationCanvas.updateRectangle(sliderWidth.value, value);
                    textFieldHeight.text = value.toFixed(0);
                }
            }

            TextField {
                id: textFieldHeight
                text: sliderHeight.value.toFixed(0)
                font.pixelSize: 20
                width: 60
                height: 30
                inputMethodHints: Qt.ImhDigitsOnly
                onEditingFinished: {
                    let newValue = parseInt(text);
                    if (!isNaN(newValue) && newValue >= sliderHeight.from && newValue <= sliderHeight.to) {
                        sliderHeight.value = newValue;
                    } else {
                        text = sliderHeight.value.toFixed(0); // 恢复为合法值
                    }
                }
            }
        }
    }
}
