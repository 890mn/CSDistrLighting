import QtQuick 2.15
import QtQuick.Window 2.15
import FluentUI 1.0

FluWindow {
    width: 1081
    height: 627
    minimumWidth: 947
    minimumHeight: 422
    title: qsTr("CSDL-FluentUI-1.0")

    property color globalTextColor: "black" // 更改文本颜色以适应白色背景
    property color cosFTextColor: Qt.rgba(87/255,151/255,180/255,255/255)
    property color cosFSextColor: Qt.rgba(43/255,186/255,180/255,255/255)

    FontLoader {
        id: brushFont
        source: "qrc:/BrushGrunge.ttf"
    }

    FontLoader {
        id: smileFont
        source: "qrc:/SmileySans-Oblique.ttf"
    }

    // 背景换成白色纯色背景
    Rectangle {
        anchors.fill: parent
        color: "white"

        InitialLayout {
            id: initialLayout
            anchors.fill: parent
            onStartSimulation: {
                startAnimation.start()
            }
        }

        SimulationLayout {
            id: simulationLayout
            anchors.fill: parent
            visible: false
        }

        // Main.qml
        SequentialAnimation {
            id: startAnimation
            NumberAnimation { target: initialLayout; property: "opacity"; to: 0; duration: 500}
            ScriptAction {
                script: {
                    initialLayout.visible = false
                    simulationLayout.visible = true
                }
            }
        }
    }
}
