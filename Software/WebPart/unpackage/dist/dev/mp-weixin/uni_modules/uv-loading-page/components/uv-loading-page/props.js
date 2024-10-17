"use strict";
var _a, _b;
const common_vendor = require("../../../../common/vendor.js");
const props = {
  props: {
    // 提示内容
    loadingText: {
      type: [String, Number],
      default: ""
    },
    // 文字上方用于替换loading动画的图片
    image: {
      type: String,
      default: ""
    },
    // 加载动画的模式，circle-圆形，spinner-花朵形，semicircle-半圆形
    loadingMode: {
      type: String,
      default: "circle"
    },
    // 是否加载中
    loading: {
      type: Boolean,
      default: false
    },
    // 背景色
    bgColor: {
      type: String,
      default: "#fff"
    },
    // 文字颜色
    color: {
      type: String,
      default: "#C8C8C8"
    },
    // 文字大小
    fontSize: {
      type: [String, Number],
      default: 18
    },
    // 图标大小
    iconSize: {
      type: [String, Number],
      default: 28
    },
    // 加载中图标的颜色，只能rgb或者十六进制颜色值
    loadingColor: {
      type: String,
      default: "#C8C8C8"
    },
    ...(_b = (_a = common_vendor.index.$uv) == null ? void 0 : _a.props) == null ? void 0 : _b.loadingPage
  }
};
exports.props = props;
