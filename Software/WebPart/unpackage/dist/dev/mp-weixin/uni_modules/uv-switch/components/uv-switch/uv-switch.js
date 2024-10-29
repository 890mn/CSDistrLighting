"use strict";
const uni_modules_uvUiTools_libs_mixin_mpMixin = require("../../../uv-ui-tools/libs/mixin/mpMixin.js");
const uni_modules_uvUiTools_libs_mixin_mixin = require("../../../uv-ui-tools/libs/mixin/mixin.js");
const uni_modules_uvSwitch_components_uvSwitch_props = require("./props.js");
const common_vendor = require("../../../../common/vendor.js");
const _sfc_main = {
  name: "uv-switch",
  mixins: [uni_modules_uvUiTools_libs_mixin_mpMixin.mpMixin, uni_modules_uvUiTools_libs_mixin_mixin.mixin, uni_modules_uvSwitch_components_uvSwitch_props.props],
  data() {
    return {
      bgColor: "#ffffff",
      innerValue: false
    };
  },
  watch: {
    modelValue: {
      immediate: true,
      handler(newVal) {
        if (newVal !== this.inactiveValue && newVal !== this.activeValue) {
          return this.$uv.error("v-model绑定的值必须为inactiveValue、activeValue二者之一");
        }
        this.innerValue = newVal;
      }
    }
  },
  created() {
    this.innerValue = this.value || this.modelValue;
  },
  computed: {
    isActive() {
      return this.innerValue === this.activeValue;
    },
    switchStyle() {
      let style = {};
      style.width = this.$uv.addUnit(this.$uv.getPx(this.size) * 2 + 2);
      style.height = this.$uv.addUnit(this.$uv.getPx(this.size) + 2);
      if (this.customInactiveColor) {
        style.borderColor = "rgba(0, 0, 0, 0)";
      }
      style.backgroundColor = this.isActive ? this.activeColor : this.inactiveColor;
      return style;
    },
    nodeStyle() {
      let style = {};
      style.width = this.$uv.addUnit(this.$uv.getPx(this.size) - this.space);
      style.height = this.$uv.addUnit(this.$uv.getPx(this.size) - this.space);
      const translateX = this.isActive ? this.$uv.addUnit(this.space) : this.$uv.addUnit(this.$uv.getPx(this.size));
      style.transform = `translateX(-${translateX})`;
      return style;
    },
    bgStyle() {
      let style = {};
      style.width = this.$uv.addUnit(this.$uv.getPx(this.size) * 2 - this.$uv.getPx(this.size) / 2);
      style.height = this.$uv.addUnit(this.$uv.getPx(this.size));
      style.backgroundColor = this.inactiveColor;
      style.transform = `scale(${this.isActive ? 0 : 1})`;
      return style;
    },
    customInactiveColor() {
      return this.inactiveColor !== "#fff" && this.inactiveColor !== "#ffffff";
    }
  },
  methods: {
    clickHandler() {
      if (!this.disabled && !this.loading) {
        const oldValue = this.isActive ? this.inactiveValue : this.activeValue;
        if (!this.asyncChange) {
          this.$emit("input", oldValue);
          this.$emit("update:modelValue", oldValue);
        }
        this.$nextTick(() => {
          this.$emit("change", oldValue);
        });
      }
    }
  }
};
if (!Array) {
  const _easycom_uv_loading_icon2 = common_vendor.resolveComponent("uv-loading-icon");
  _easycom_uv_loading_icon2();
}
const _easycom_uv_loading_icon = () => "../../../uv-loading-icon/components/uv-loading-icon/uv-loading-icon.js";
if (!Math) {
  _easycom_uv_loading_icon();
}
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return {
    a: common_vendor.s($options.bgStyle),
    b: common_vendor.p({
      show: _ctx.loading,
      mode: "circle",
      timingFunction: "linear",
      color: $data.innerValue ? _ctx.activeColor : "#AAABAD",
      size: _ctx.size * 0.6
    }),
    c: common_vendor.n($data.innerValue && "uv-switch__node--on"),
    d: common_vendor.s($options.nodeStyle),
    e: common_vendor.n(_ctx.disabled && "uv-switch--disabled"),
    f: common_vendor.s($options.switchStyle),
    g: common_vendor.s(_ctx.$uv.addStyle(_ctx.customStyle)),
    h: common_vendor.o((...args) => $options.clickHandler && $options.clickHandler(...args))
  };
}
const Component = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render], ["__scopeId", "data-v-c713e4c9"]]);
wx.createComponent(Component);
