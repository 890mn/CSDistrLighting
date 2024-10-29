"use strict";
const uni_modules_uvUiTools_libs_mixin_mpMixin = require("../../../uv-ui-tools/libs/mixin/mpMixin.js");
const uni_modules_uvUiTools_libs_mixin_mixin = require("../../../uv-ui-tools/libs/mixin/mixin.js");
const uni_modules_uvSlider_components_uvSlider_props = require("./props.js");
const common_vendor = require("../../../../common/vendor.js");
const _sfc_main = {
  name: "uv-slider",
  mixins: [uni_modules_uvUiTools_libs_mixin_mpMixin.mpMixin, uni_modules_uvUiTools_libs_mixin_mixin.mixin, uni_modules_uvSlider_components_uvSlider_props.props],
  computed: {
    sliderValue() {
      return this.value || this.modelValue;
    }
  },
  methods: {
    // 拖动过程中触发
    changingHandler(e) {
      const { value } = e.detail;
      this.$emit("input", value);
      this.$emit("update:modelValue", value);
      this.$emit("changing", value);
    },
    // 滑动结束时触发
    changeHandler(e) {
      const {
        value
      } = e.detail;
      this.$emit("input", value);
      this.$emit("update:modelValue", value);
      this.$emit("change", value);
    }
  }
};
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return {
    a: _ctx.min,
    b: _ctx.max,
    c: _ctx.step,
    d: $options.sliderValue,
    e: _ctx.activeColor,
    f: _ctx.backgroundColor,
    g: _ctx.$uv.getPx(_ctx.blockSize),
    h: _ctx.blockColor,
    i: _ctx.showValue,
    j: _ctx.disabled,
    k: common_vendor.o((...args) => $options.changingHandler && $options.changingHandler(...args)),
    l: common_vendor.o((...args) => $options.changeHandler && $options.changeHandler(...args)),
    m: common_vendor.s(_ctx.$uv.addStyle(_ctx.customStyle))
  };
}
const Component = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render]]);
wx.createComponent(Component);
