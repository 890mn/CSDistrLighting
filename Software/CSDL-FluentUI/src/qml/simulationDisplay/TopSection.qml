import QtQuick 2.15
import QtQuick.Layouts
import FluentUI 1.0

Item {
    property alias simulationCanvas: canvasArea
    property alias rightSection: rightArea

    Row {
        id: topSection
        anchors.fill: parent
        spacing: 10
        padding: 10

        // 左侧画布区域
        SimulationCanvas {
            id: canvasArea
            width: topSection.width * 0.6 - topSection.padding
            height: parent.height
        }

        // 右侧模块区域
        RightSection {
            id: rightArea
            width: topSection.width * 0.4 - topSection.padding
            height: parent.height
        }
    }
}
