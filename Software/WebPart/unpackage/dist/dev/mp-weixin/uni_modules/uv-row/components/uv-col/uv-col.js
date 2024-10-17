"use strict";
const uni_modules_uvUiTools_libs_mixin_mpMixin = require("../../../uv-ui-tools/libs/mixin/mpMixin.js");
const uni_modules_uvUiTools_libs_mixin_mixin = require("../../../uv-ui-tools/libs/mixin/mixin.js");
const uni_modules_uvRow_components_uvCol_props = require("./props.js");
const common_vendor = require("../../../../common/vendor.js");
require("../../../uv-ui-tools/libs/function/index.js");
require("../../../uv-ui-tools/libs/function/test.js");
require("../../../uv-ui-tools/libs/function/digit.js");
require("../../../uv-ui-tools/libs/util/route.js");
require("../../../uv-ui-tools/libs/function/debounce.js");
require("../../../uv-ui-tools/libs/function/throttle.js");
const _sfc_main = {
  name: "uv-col",
  emits: ["click"],
  mixins: [uni_modules_uvUiTools_libs_mixin_mpMixin.mpMixin, uni_modules_uvUiTools_libs_mixin_mixin.mixin, uni_modules_uvRow_components_uvCol_props.props],
  data() {
    return {
      width: 0,
      parentData: {
        gutter: 0
      },
      gridNum: 12
    };
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
    colStyle() {
      const style = {
        // 这里写成"padding: 0 10px"的形式是因为nvue的需要
        paddingLeft: this.$uv.addUnit(this.$uv.getPx(this.parentData.gutter) / 2),
        paddingRight: this.$uv.addUnit(this.$uv.getPx(this.parentData.gutter) / 2),
        alignItems: this.uAlignItem,
        justifyContent: this.uJustify,
        textAlign: this.textAlign,
        // 在非nvue上，使用百分比形式
        flex: `0 0 ${100 / this.gridNum * this.span}%`,
        marginLeft: 100 / 12 * this.offset + "%"
      };
      return this.$uv.deepMerge(style, this.$uv.addStyle(this.customStyle));
    }
  },
  mounted() {
    this.init();
  },
  methods: {
    async init() {
      this.updateParentData();
      this.width = await this.parent.getComponentWidth();
    },
    updateParentData() {
      this.getParentData("uv-row");
    },
    clickHandler(e) {
      this.$emit("click");
    }
  }
};
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return {
    a: common_vendor.n("uv-col-" + _ctx.span),
    b: common_vendor.s($options.colStyle),
    c: common_vendor.o((...args) => $options.clickHandler && $options.clickHandler(...args))
  };
}
const Component = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render], ["__scopeId", "data-v-d2bffd23"], ["__file", "C:/Users/binar/Downloads/ligth-ble/uni_modules/uv-row/components/uv-col/uv-col.vue"]]);
wx.createComponent(Component);
