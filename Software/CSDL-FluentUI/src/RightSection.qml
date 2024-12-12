import QtQuick 2.15
import QtQuick.Controls 2.15

ScrollView {
    id: rightSection
    clip: true
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff

    Column {
        id: rightContent
        width: rightSection.width
        spacing: 10

        // 室内环境模块
        IndoorEnvironmentModule {}

        // 光源设置模块
        LightSettingsModule {}

        // 其他模块和按钮
        AdditionalModule {}
    }
}
