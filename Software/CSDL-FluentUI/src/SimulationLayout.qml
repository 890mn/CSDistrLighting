import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import FluentUI 1.0

Item {
    signal returnToHome()

    Column {
        id: simulationLayout
        anchors.fill: parent

        // 顶部区域
        TopSection {
            id: topSection
            width: parent.width
            height: parent.height * 0.9
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // 底部区域
        BottomSection {
            id: bottomSection
            width: parent.width
            height: parent.height * 0.1 + 5
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
