import QtQuick 2.15
import QtQuick.Window 2.15
import FluentUI 1.0

FluWindow {
    id: mainWindow
    width: 1081
    height: 627
    minimumWidth: 947
    minimumHeight: 422
    title: qsTr("CSilver")

    property color globalTextColor: "black" // 更改文本颜色以适应白色背景
    property color cosFTextColor: Qt.rgba(87/255,151/255,180/255,255/255)
    property color cosSTextColor: Qt.rgba(43/255,186/255,180/255,255/255)

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

        Image{
            source: "qrc:/back.png"
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
            opacity: 0.7
        }

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
            onReturnToHome: {
                returnAnimation.start()
            }
        }

        SequentialAnimation {
            id: startAnimation
            ParallelAnimation {
                NumberAnimation { target: initialLayout; property: "opacity"; to: 0; duration: 400 }
                NumberAnimation { target: simulationLayout; property: "opacity"; to: 1; duration: 400 }
            }
            ScriptAction {
                script: {
                    initialLayout.visible = false
                    initialLayout.opacity = 0
                    simulationLayout.visible = true
                    simulationLayout.opacity = 1
                }
            }
        }

        SequentialAnimation {
            id: returnAnimation
            ParallelAnimation {
                NumberAnimation { target: initialLayout; property: "opacity"; to: 1; duration: 400 }
                NumberAnimation { target: simulationLayout; property: "opacity"; to: 0; duration: 400 }
            }
            ScriptAction {
                script: {
                    simulationLayout.visible = false
                    simulationLayout.opacity = 0
                    initialLayout.visible = true
                    initialLayout.opacity = 1
                }
            }
        }
    }
}
