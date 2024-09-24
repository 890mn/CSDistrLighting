"use strict";
const uni_modules_uvUiTools_libs_mixin_mpMixin = require("../../../uv-ui-tools/libs/mixin/mpMixin.js");
const uni_modules_uvUiTools_libs_mixin_mixin = require("../../../uv-ui-tools/libs/mixin/mixin.js");
const uni_modules_uvLoadingPage_components_uvLoadingPage_props = require("./props.js");
const common_vendor = require("../../../../common/vendor.js");
require("../../../uv-ui-tools/libs/function/index.js");
require("../../../uv-ui-tools/libs/function/test.js");
require("../../../uv-ui-tools/libs/function/digit.js");
require("../../../uv-ui-tools/libs/util/route.js");
require("../../../uv-ui-tools/libs/function/debounce.js");
require("../../../uv-ui-tools/libs/function/throttle.js");
const _sfc_main = {
  name: "uv-loading-page",
  mixins: [uni_modules_uvUiTools_libs_mixin_mpMixin.mpMixin, uni_modules_uvUiTools_libs_mixin_mixin.mixin, uni_modules_uvLoadingPage_components_uvLoadingPage_props.props]
};
if (!Array) {
  const _easycom_uv_loading_icon2 = common_vendor.resolveComponent("uv-loading-icon");
  const _easycom_uv_transition2 = common_vendor.resolveComponent("uv-transition");
  (_easycom_uv_loading_icon2 + _easycom_uv_transition2)();
}
const _easycom_uv_loading_icon = () => "../../../uv-loading-icon/components/uv-loading-icon/uv-loading-icon.js";
const _easycom_uv_transition = () => "../../../uv-transition/components/uv-transition/uv-transition.js";
if (!Math) {
  (_easycom_uv_loading_icon + _easycom_uv_transition)();
}
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return common_vendor.e({
    a: _ctx.image
  }, _ctx.image ? {
    b: _ctx.image,
    c: _ctx.$uv.addUnit(_ctx.iconSize),
    d: _ctx.$uv.addUnit(_ctx.iconSize)
  } : {
    e: common_vendor.p({
      mode: _ctx.loadingMode,
      size: _ctx.$uv.addUnit(_ctx.iconSize),
      color: _ctx.loadingColor
    })
  }, {
    f: common_vendor.t(_ctx.loadingText),
    g: _ctx.$uv.addUnit(_ctx.fontSize),
    h: _ctx.color,
    i: common_vendor.p({
      show: _ctx.loading,
      ["custom-style"]: {
        position: "fixed",
        top: 0,
        left: 0,
        right: 0,
        bottom: 0,
        zIndex: 999,
        backgroundColor: _ctx.bgColor,
        display: "flex"
      }
    })
  });
}
const Component = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render], ["__scopeId", "data-v-a1a98476"], ["__file", "C:/Users/binar/Downloads/ligth-ble/uni_modules/uv-loading-page/components/uv-loading-page/uv-loading-page.vue"]]);
wx.createComponent(Component);
