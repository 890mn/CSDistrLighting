"use strict";
var _a, _b;
const common_vendor = require("../../../../common/vendor.js");
const props = {
  props: {
    value: {
      type: [Boolean, String, Number],
      default: false
    },
    modelValue: {
      type: [Boolean, String, Number],
      default: false
    },
    // 是否为加载中状态
    loading: {
      type: Boolean,
      default: false
    },
    // 是否为禁用装填
    disabled: {
      type: Boolean,
      default: false
    },
    // 开关尺寸，单位px
    size: {
      type: [String, Number],
      default: 25
    },
    // 打开时的背景颜色
    activeColor: {
      type: String,
      default: "#2979ff"
    },
    // 关闭时的背景颜色
    inactiveColor: {
      type: String,
      default: "#fff"
    },
    // switch打开时的值
    activeValue: {
      type: [String, Number, Boolean],
      default: true
    },
    // switch关闭时的值
    inactiveValue: {
      type: [String, Number, Boolean],
      default: false
    },
    // 是否开启异步变更，开启后需要手动控制输入值
    asyncChange: {
      type: Boolean,
      default: false
    },
    // 圆点与外边框的距离
    space: {
      type: [String, Number],
      default: 0
    },
    ...(_b = (_a = common_vendor.index.$uv) == null ? void 0 : _a.props) == null ? void 0 : _b.switch
  }
};
exports.props = props;
