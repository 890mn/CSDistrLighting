"use strict";
const uni_modules_uvUiTools_libs_mixin_mpMixin = require("../../../uv-ui-tools/libs/mixin/mpMixin.js");
const uni_modules_uvUiTools_libs_mixin_mixin = require("../../../uv-ui-tools/libs/mixin/mixin.js");
const common_vendor = require("../../../../common/vendor.js");
require("../../../uv-ui-tools/libs/function/index.js");
require("../../../uv-ui-tools/libs/function/test.js");
require("../../../uv-ui-tools/libs/function/digit.js");
require("../../../uv-ui-tools/libs/util/route.js");
require("../../../uv-ui-tools/libs/function/debounce.js");
require("../../../uv-ui-tools/libs/function/throttle.js");
const _sfc_main = {
  name: "uv-toast",
  mixins: [uni_modules_uvUiTools_libs_mixin_mpMixin.mpMixin, uni_modules_uvUiTools_libs_mixin_mixin.mixin],
  data() {
    return {
      isShow: false,
      timer: null,
      // 定时器
      config: {
        message: "",
        // 显示文本
        type: "",
        // 主题类型，primary，success，error，warning，black
        duration: 2e3,
        // 显示的时间，毫秒
        icon: true,
        // 显示的图标
        position: "center",
        // toast出现的位置
        complete: null,
        // 执行完后的回调函数
        overlay: false,
        // 是否防止触摸穿透
        loading: false
        // 是否加载中状态
      },
      tmpConfig: {}
      // 将用户配置和内置配置合并后的临时配置变量
    };
  },
  computed: {
    iconName() {
      if (!this.tmpConfig.icon || this.tmpConfig.icon == "none") {
        return "";
      }
      if (["error", "warning", "success", "primary"].includes(this.tmpConfig.type)) {
        return this.$uv.type2icon(this.tmpConfig.type);
      } else {
        return "";
      }
    },
    overlayStyle() {
      const style = {
        justifyContent: "center",
        alignItems: "center",
        display: "flex"
      };
      style.backgroundColor = "rgba(0, 0, 0, 0)";
      return style;
    },
    iconStyle() {
      const style = {};
      style.marginRight = "4px";
      return style;
    },
    // 内容盒子的样式
    contentStyle() {
      const windowHeight = this.$uv.sys().windowHeight, style = {};
      let value = 0;
      if (this.tmpConfig.position === "top") {
        value = -windowHeight * 0.25;
      } else if (this.tmpConfig.position === "bottom") {
        value = windowHeight * 0.25;
      }
      style.transform = `translateY(${value}px)`;
      return style;
    }
  },
  created() {
    ["primary", "success", "error", "warning", "default", "loading"].map((item) => {
      this[item] = (message) => this.show({
        type: item,
        message
      });
    });
  },
  methods: {
    // 显示toast组件，由父组件通过this.$refs.xxx.show(options)形式调用
    show(options) {
      this.tmpConfig = this.$uv.deepMerge(this.config, options);
      this.clearTimer();
      this.isShow = true;
      this.timer = setTimeout(() => {
        this.clearTimer();
        typeof this.tmpConfig.complete === "function" && this.tmpConfig.complete();
      }, this.tmpConfig.duration);
    },
    // 隐藏toast组件，由父组件通过this.$refs.xxx.hide()形式调用
    hide() {
      this.clearTimer();
    },
    clearTimer() {
      this.isShow = false;
      clearTimeout(this.timer);
      this.timer = null;
    }
  },
  unmounted() {
    this.clearTimer();
  }
};
if (!Array) {
  const _easycom_uv_loading_icon2 = common_vendor.resolveComponent("uv-loading-icon");
  const _easycom_uv_icon2 = common_vendor.resolveComponent("uv-icon");
  const _easycom_uv_gap2 = common_vendor.resolveComponent("uv-gap");
  const _easycom_uv_overlay2 = common_vendor.resolveComponent("uv-overlay");
  (_easycom_uv_loading_icon2 + _easycom_uv_icon2 + _easycom_uv_gap2 + _easycom_uv_overlay2)();
}
const _easycom_uv_loading_icon = () => "../../../uv-loading-icon/components/uv-loading-icon/uv-loading-icon.js";
const _easycom_uv_icon = () => "../../../uv-icon/components/uv-icon/uv-icon.js";
const _easycom_uv_gap = () => "../../../uv-gap/components/uv-gap/uv-gap.js";
const _easycom_uv_overlay = () => "../../../uv-overlay/components/uv-overlay/uv-overlay.js";
if (!Math) {
  (_easycom_uv_loading_icon + _easycom_uv_icon + _easycom_uv_gap + _easycom_uv_overlay)();
}
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return common_vendor.e({
    a: $data.tmpConfig.type === "loading"
  }, $data.tmpConfig.type === "loading" ? {
    b: common_vendor.p({
      mode: "circle",
      color: "rgb(255, 255, 255)",
      inactiveColor: "rgb(120, 120, 120)",
      size: "25"
    })
  } : $data.tmpConfig.type !== "defalut" && $options.iconName ? {
    d: common_vendor.p({
      name: $options.iconName,
      size: "17",
      color: $data.tmpConfig.type,
      customStyle: $options.iconStyle
    })
  } : {}, {
    c: $data.tmpConfig.type !== "defalut" && $options.iconName,
    e: $data.tmpConfig.type === "loading" || $data.tmpConfig.loading
  }, $data.tmpConfig.type === "loading" || $data.tmpConfig.loading ? {
    f: common_vendor.p({
      height: "12",
      bgColor: "transparent"
    })
  } : {}, {
    g: common_vendor.t($data.tmpConfig.message),
    h: common_vendor.n("uv-toast__content__text--" + $data.tmpConfig.type),
    i: common_vendor.s($options.contentStyle),
    j: common_vendor.n("uv-type-" + $data.tmpConfig.type),
    k: common_vendor.n($data.tmpConfig.type === "loading" || $data.tmpConfig.loading ? "uv-toast__content--loading" : ""),
    l: common_vendor.p({
      show: $data.isShow,
      ["custom-style"]: $options.overlayStyle
    })
  });
}
const Component = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render], ["__scopeId", "data-v-70f56d7c"], ["__file", "C:/Users/binar/Downloads/ligth-ble/uni_modules/uv-toast/components/uv-toast/uv-toast.vue"]]);
wx.createComponent(Component);
