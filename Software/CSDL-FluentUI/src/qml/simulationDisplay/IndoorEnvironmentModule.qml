import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Rectangle {
    id: indoorEnvironment
    width: parent.width - 20
    height: 160
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
            text: qsTr("[%1] x [%2]").arg(sliderX.value.toFixed(0)).arg(sliderY.value.toFixed(0))
            font.pixelSize: 20
            font.bold: true
        }

        // X 滑块
        Row {
            spacing: 10
            width: parent.width

            Text {
                text: qsTr("X 值")
                font.pixelSize: 20
                width: 80
            }

            Slider {
                id: sliderX
                width: parent.width - 180
                from: 0
                to: 600
                value: 300
                onValueChanged: simulationData.text = qsTr("[%1] x [%2]").arg(value.toFixed(0)).arg(sliderY.value.toFixed(0))
            }

            Text {
                text: sliderX.value.toFixed(0)
                font.pixelSize: 20
                width: 50
                horizontalAlignment: Text.AlignHCenter
            }
        }

        // Y 滑块
        Row {
            spacing: 10
            width: parent.width

            Text {
                text: qsTr("Y 值")
                font.pixelSize: 20
                width: 80
            }

            Slider {
                id: sliderY
                width: parent.width - 180
                from: 0
                to: 400
                value: 200
                onValueChanged: simulationData.text = qsTr("[%1] x [%2]").arg(sliderX.value.toFixed(0)).arg(value.toFixed(0))
            }

            Text {
                text: sliderY.value.toFixed(0)
                font.pixelSize: 20
                width: 50
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
}
