import QtQuick 2.15
import FluentUI

Rectangle {
    id: simulationCanvas
    radius: 10
    border.color: "#a0a0a0"
    border.width: 2
    color: "white"

    property real maxX: 400 // 最大 X 轴刻度
    property real maxY: 400 // 最大 Y 轴刻度
    property real rectWidth: 0 // 矩形宽度
    property real rectHeight: 0 // 矩形高度

    onRectWidthChanged: adjustAxes()
    onRectHeightChanged: adjustAxes()

    function updateRectangle(width, height) {
        rectWidth = width;
        rectHeight = height;
    }

    function adjustAxes() {
        maxX = Math.ceil(rectWidth / 10) * 10 + 50; // 额外保留空间
        maxY = Math.ceil(rectHeight / 10) * 10 + 50; // 额外保留空间
        canvas.requestPaint();
    }

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height); // 清空画布

            // 坐标轴设置
            const padding = 60; // 坐标轴边距
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

            // X 轴刻度
            const xStep = maxX / 10; // 分为 10 个刻度
            for (let i = 0; i <= maxX; i += xStep) {
                const x = padding + (i / maxX) * axisWidth;
                ctx.beginPath();
                ctx.moveTo(x, height - padding);
                ctx.lineTo(x, height - padding + 5);
                ctx.stroke();
                ctx.fillText(i.toFixed(0), x, height - padding + 20); // 调整文字位置
            }

            // Y 轴刻度
            const yStep = maxY / 10; // 分为 10 个刻度
            ctx.textAlign = "right";
            for (let j = 0; j <= maxY; j += yStep) {
                const y = height - padding - (j / maxY) * axisHeight;
                ctx.beginPath();
                ctx.moveTo(padding, y);
                ctx.lineTo(padding - 5, y);
                ctx.stroke();
                ctx.fillText(j.toFixed(0), padding - 20, y + 3); // 调整文字位置与轴线分离
            }

            // 绘制矩形（如果有数据）
            if (rectWidth > 0 && rectHeight > 0) {
                ctx.strokeStyle = cosFTextColor;
                ctx.lineWidth = 2;
                const rectX = padding;
                const rectY = height - padding - (rectHeight / maxY) * axisHeight;
                const scaledWidth = (rectWidth / maxX) * axisWidth;
                const scaledHeight = (rectHeight / maxY) * axisHeight;
                ctx.strokeRect(rectX, rectY, scaledWidth, scaledHeight);
            }
        }
    }
}
