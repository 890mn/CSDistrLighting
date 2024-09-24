"use strict";
const uni_modules_uvUiTools_libs_mixin_mpMixin = require("../../../uv-ui-tools/libs/mixin/mpMixin.js");
const uni_modules_uvUiTools_libs_mixin_mixin = require("../../../uv-ui-tools/libs/mixin/mixin.js");
const uni_modules_uvRow_components_uvRow_props = require("./props.js");
const common_vendor = require("../../../../common/vendor.js");
require("../../../uv-ui-tools/libs/function/index.js");
require("../../../uv-ui-tools/libs/function/test.js");
require("../../../uv-ui-tools/libs/function/digit.js");
require("../../../uv-ui-tools/libs/util/route.js");
require("../../../uv-ui-tools/libs/function/debounce.js");
require("../../../uv-ui-tools/libs/function/throttle.js");
const _sfc_main = {
  name: "uv-row",
  emits: ["click"],
  mixins: [uni_modules_uvUiTools_libs_mixin_mpMixin.mpMixin, uni_modules_uvUiTools_libs_mixin_mixin.mixin, uni_modules_uvRow_components_uvRow_props.props],
  data() {
    return {};
  },
  computed: {
    uJustify() {
      if (this.justify == "end" || this.justify == "start")
        return "flex-" + this.justify;
      else if (this.justify == "around" || this.justify == "between")
        return "space-" + this.justify;
      else
        return this.justify;
    },
    uAlignItem() {
      if (this.align == "top")
        return "flex-start";
      if (this.align == "bottom")
        return "flex-end";
      else
        return this.align;
    },
    rowStyle() {
      const style = {
        alignItems: this.uAlignItem,
        justifyContent: this.uJustify
      };
      if (this.gutter) {
        style.marginLeft = this.$uv.addUnit(-Number(this.gutter) / 2);
        style.marginRight = this.$uv.addUnit(-Number(this.gutter) / 2);
      }
      return this.$uv.deepMerge(style, this.$uv.addStyle(this.customStyle));
    }
  },
  methods: {
    clickHandler(e) {
      this.$emit("click");
    },
    async getComponentWidth() {
      await this.$uv.sleep();
      return new Promise((resolve) => {
        this.$uvGetRect(".uv-row").then((res) => {
          resolve(res.width);
        });
      });
    }
  }
};
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return {
    a: common_vendor.s($options.rowStyle),
    b: common_vendor.o((...args) => $options.clickHandler && $options.clickHandler(...args))
  };
}
const Component = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render], ["__scopeId", "data-v-692ff899"], ["__file", "C:/Users/binar/Downloads/ligth-ble/uni_modules/uv-row/components/uv-row/uv-row.vue"]]);
wx.createComponent(Component);
