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
    property var rectangles: [] // 矩形数据 [{x: 10, y: 20, width: 30, height: 40}, ...]

    property real rectWidth: 0
    property real rectHeight: 0

    onRectanglesChanged: {
        // 根据矩形数据动态扩展坐标范围
        for (let rect of rectangles) {
            if (rect.x + rect.width > maxX) maxX = Math.ceil((rect.x + rect.width) / 10) * 10;
            if (rect.y + rect.height > maxY) maxY = Math.ceil((rect.y + rect.height) / 10) * 10;
        }
        canvas.requestPaint();
    }

    onRectWidthChanged: canvas.requestPaint()
    onRectHeightChanged: canvas.requestPaint()

    function updateRectangle(width, height) {
        rectWidth = width;
        rectHeight = height;
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

            // X 轴刻度
            const xStep = rectWidth ? axisWidth / rectWidth : axisWidth / 10; // 默认 10 个刻度
            for (let i = 0; i <= rectWidth; i += rectWidth / 10 || 1) {
                const x = padding + i * xStep;
                ctx.beginPath();
                ctx.moveTo(x, height - padding);
                ctx.lineTo(x, height - padding + 5);
                ctx.stroke();
                ctx.fillText(i.toFixed(0), x, height - padding + 15);
            }

            // Y 轴刻度
            const yStep = rectHeight ? axisHeight / rectHeight : axisHeight / 10; // 默认 10 个刻度
            ctx.textAlign = "right";
            for (let j = 0; j <= rectHeight; j += rectHeight / 10 || 1) {
                const y = height - padding - j * yStep;
                ctx.beginPath();
                ctx.moveTo(padding, y);
                ctx.lineTo(padding - 5, y);
                ctx.stroke();
                ctx.fillText(j.toFixed(0), padding - 10, y + 3);
            }

            // 绘制矩形（无填充，边框宽度 2）
            ctx.strokeStyle = "#ff0000";
            ctx.lineWidth = 2;
            const rectX = padding;
            const rectY = height - padding - rectHeight;
            ctx.strokeRect(rectX, rectY, rectWidth, rectHeight);
        }
    }
}
