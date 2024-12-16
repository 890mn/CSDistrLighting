import QtQuick 2.15
import FluentUI

Rectangle {
    id: simulationCanvas
    radius: 10
    border.color: "#a0a0a0"
    border.width: 2
    color: "white"

    property real maxX: 100 // 最大 X 轴刻度
    property real maxY: 100 // 最大 Y 轴刻度
    property real rectWidth: 0 // 矩形宽度
    property real rectHeight: 0 // 矩形高度

    onRectWidthChanged: adjustAxes()
    onRectHeightChanged: adjustAxes()

    function updateRectangle(width, height) {
        rectWidth = width;
        rectHeight = height;
    }

    function adjustAxes() {
        const buffer = 20; // 为最大值加入缓冲
        const minRange = 100; // 坐标轴最小范围

        // 动态调整 X 轴范围
        const newMaxX = Math.max(Math.ceil((rectWidth + buffer) / 10) * 10, minRange);
        if (Math.abs(newMaxX - maxX) > maxX * 0.1) { // 变化超过 10% 时更新
            maxX = newMaxX;
        }

        // 动态调整 Y 轴范围
        const newMaxY = Math.max(Math.ceil((rectHeight + buffer) / 10) * 10, minRange);
        if (Math.abs(newMaxY - maxY) > maxY * 0.1) { // 变化超过 10% 时更新
            maxY = newMaxY;
        }

        canvas.requestPaint(); // 刷新画布
    }

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height); // 清空画布

            // 坐标轴设置
            const padding = 40; // 坐标轴边距
            const axisWidth = width - 2 * padding;
            const axisHeight = height - 2 * padding;

            // 绘制 X 轴和 Y 轴
            ctx.strokeStyle = "#000000";
            ctx.lineWidth = 2;

            // Y 轴
            ctx.beginPath();
            ctx.moveTo(padding, padding);
            ctx.lineTo(padding, height - padding);
            ctx.stroke();

            // X 轴
            ctx.beginPath();
            ctx.moveTo(padding, height - padding);
            ctx.lineTo(width - padding, height - padding);
            ctx.stroke();

            // 绘制刻度
            ctx.fillStyle = "#000000";
            ctx.font = "12px Arial";
            ctx.textAlign = "center";

            const xStep = maxX / 10; // X轴刻度间隔
            for (let i = 0; i <= maxX; i += xStep) {
                const x = padding + (i / maxX) * axisWidth;
                ctx.beginPath();
                ctx.moveTo(x, height - padding);
                ctx.lineTo(x, height - padding + 5);
                ctx.stroke();
                ctx.fillText(i.toFixed(0), x, height - padding + 15);
            }

            const yStep = maxY / 10; // Y轴刻度间隔
            for (let j = 0; j <= maxY; j += yStep) {
                const y = height - padding - (j / maxY) * axisHeight;
                ctx.beginPath();
                ctx.moveTo(padding, y);
                ctx.lineTo(padding - 5, y);
                ctx.stroke();
                ctx.fillText(j.toFixed(0), padding - 10, y + 3);
            }

            // 绘制矩形（如果有数据）
            if (rectWidth > 0 && rectHeight > 0) {
                ctx.strokeStyle = "#00ff00";
                ctx.lineWidth = 2;
                const rectX = padding; // 矩形左上角X坐标
                const rectY = height - padding - (rectHeight / maxY) * axisHeight; // 矩形左上角Y坐标
                const scaledWidth = (rectWidth / maxX) * axisWidth; // 宽度按比例缩放
                const scaledHeight = (rectHeight / maxY) * axisHeight; // 高度按比例缩放
                ctx.strokeRect(rectX, rectY, scaledWidth, scaledHeight);
            }
        }
    }
}
