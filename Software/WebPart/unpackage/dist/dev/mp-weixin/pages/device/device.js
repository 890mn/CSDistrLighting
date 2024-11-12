"use strict";
const common_vendor = require("../../common/vendor.js");
const uni_modules_uvUiTools_libs_function_index = require("../../uni_modules/uv-ui-tools/libs/function/index.js");
if (!Array) {
  const _easycom_uv_navbar2 = common_vendor.resolveComponent("uv-navbar");
  const _easycom_uv_modal2 = common_vendor.resolveComponent("uv-modal");
  const _easycom_uv_toast2 = common_vendor.resolveComponent("uv-toast");
  const _easycom_uv_loading_page2 = common_vendor.resolveComponent("uv-loading-page");
  const _easycom_uv_col2 = common_vendor.resolveComponent("uv-col");
  const _easycom_uv_row2 = common_vendor.resolveComponent("uv-row");
  const _easycom_uv_cell2 = common_vendor.resolveComponent("uv-cell");
  const _easycom_uv_switch2 = common_vendor.resolveComponent("uv-switch");
  const _easycom_uv_slider2 = common_vendor.resolveComponent("uv-slider");
  const _easycom_uv_cell_group2 = common_vendor.resolveComponent("uv-cell-group");
  (_easycom_uv_navbar2 + _easycom_uv_modal2 + _easycom_uv_toast2 + _easycom_uv_loading_page2 + _easycom_uv_col2 + _easycom_uv_row2 + _easycom_uv_cell2 + _easycom_uv_switch2 + _easycom_uv_slider2 + _easycom_uv_cell_group2)();
}
const _easycom_uv_navbar = () => "../../uni_modules/uv-navbar/components/uv-navbar/uv-navbar.js";
const _easycom_uv_modal = () => "../../uni_modules/uv-modal/components/uv-modal/uv-modal.js";
const _easycom_uv_toast = () => "../../uni_modules/uv-toast/components/uv-toast/uv-toast.js";
const _easycom_uv_loading_page = () => "../../uni_modules/uv-loading-page/components/uv-loading-page/uv-loading-page.js";
const _easycom_uv_col = () => "../../uni_modules/uv-row/components/uv-col/uv-col.js";
const _easycom_uv_row = () => "../../uni_modules/uv-row/components/uv-row/uv-row.js";
const _easycom_uv_cell = () => "../../uni_modules/uv-cell/components/uv-cell/uv-cell.js";
const _easycom_uv_switch = () => "../../uni_modules/uv-switch/components/uv-switch/uv-switch.js";
const _easycom_uv_slider = () => "../../uni_modules/uv-slider/components/uv-slider/uv-slider.js";
const _easycom_uv_cell_group = () => "../../uni_modules/uv-cell/components/uv-cell-group/uv-cell-group.js";
if (!Math) {
  (_easycom_uv_navbar + _easycom_uv_modal + _easycom_uv_toast + _easycom_uv_loading_page + _easycom_uv_col + _easycom_uv_row + _easycom_uv_cell + _easycom_uv_switch + _easycom_uv_slider + _easycom_uv_cell_group)();
}
const serviceId = "6E400000-B5A3-F393-E0A9-E50E24DCCA9E";
const characteristicId = "6E400001-B5A3-F393-E0A9-E50E24DCCA9E";
const _sfc_main = {
  __name: "device",
  setup(__props) {
    const operatingSystem = uni_modules_uvUiTools_libs_function_index.os();
    const deviceId = operatingSystem === "ios" ? "4338C594-C742-429C-06A5-72A76E43374F" : "30:C6:F7:43:ED:CA";
    const toast = common_vendor.ref(null);
    const modal = common_vendor.ref(null);
    const loading = common_vendor.ref(false);
    const device = common_vendor.ref({
      light: 0,
      power: 50,
      on: false,
      auto: false,
      kelvin: 4e3,
      luminance: 400
    });
    const openModal = () => {
      modal.value.open();
    };
    const disconnect = () => {
      common_vendor.index.closeBLEConnection({
        deviceId,
        success(res) {
          common_vendor.index.navigateBack();
        }
      });
    };
    const showToast = (params) => {
      toast.value.show({
        ...params
      });
    };
    const createBLEConnection = () => {
      common_vendor.index.createBLEConnection({
        deviceId,
        success(res) {
          console.log("蓝牙连接成功", res);
          common_vendor.index.setBLEMTU({
            deviceId,
            mtu: 185,
            success(res2) {
              console.log("MTU设置成功", res2);
            },
            fail(res2) {
              console.log("MTU设置失败", res2);
            },
            complete() {
              getBLEDeviceServices();
            }
          });
        },
        fail(res) {
          console.log("蓝牙连接失败", res);
        }
      });
    };
    common_vendor.onReady(() => {
      loading.value = true;
      createBLEConnection();
    });
    const getBLEDeviceServices = () => {
      common_vendor.index.getBLEDeviceServices({
        deviceId,
        success: (res) => {
          console.log("device services:", res);
          getBLEDeviceCharacteristics();
        }
      });
    };
    const getBLEDeviceCharacteristics = () => {
      common_vendor.index.getBLEDeviceCharacteristics({
        deviceId,
        serviceId,
        success: (res) => {
          console.log("device characteristics:", res);
          notifyBLECharacteristicValueChange();
        }
      });
    };
    function stringToUtf8ArrayBuffer(str) {
      const utf8 = [];
      for (let i = 0; i < str.length; i++) {
        let charCode = str.charCodeAt(i);
        if (charCode < 128) {
          utf8.push(charCode);
        } else if (charCode < 2048) {
          utf8.push(192 | charCode >> 6);
          utf8.push(128 | charCode & 63);
        } else {
          utf8.push(224 | charCode >> 12);
          utf8.push(128 | charCode >> 6 & 63);
          utf8.push(128 | charCode & 63);
        }
      }
      const buffer = new ArrayBuffer(utf8.length);
      const view = new Uint8Array(buffer);
      for (let i = 0; i < utf8.length; i++) {
        view[i] = utf8[i];
      }
      return buffer;
    }
    function utf8ArrayBufferToString(buffer) {
      const view = new Uint8Array(buffer);
      let result = "";
      for (let i = 0; i < view.length; ) {
        const currentByte = view[i];
        if (currentByte < 128) {
          result += String.fromCharCode(currentByte);
          i++;
        } else if ((currentByte & 224) === 192) {
          const charCode = (currentByte & 31) << 6 | view[i + 1] & 63;
          result += String.fromCharCode(charCode);
          i += 2;
        } else {
          const charCode = (currentByte & 15) << 12 | (view[i + 1] & 63) << 6 | view[i + 2] & 63;
          result += String.fromCharCode(charCode);
          i += 3;
        }
      }
      return result;
    }
    const notifyBLECharacteristicValueChange = () => {
      common_vendor.index.onBLECharacteristicValueChange((res) => {
        let value = utf8ArrayBufferToString(res.value);
        console.log("====", value);
        if (value.startsWith("[")) {
          value = JSON.parse(value);
          device.value.power = value[0].power;
          device.value.on = value[0].on;
          device.value.auto = value[0].auto;
          device.value.kelvin = value[0].kelvin;
          device.value.luminance = value[0].luminance;
          loading.value = false;
          showToast({
            message: "连接成功"
          });
        } else {
          value = JSON.parse(value);
          device.value.light = value.light;
        }
      });
      common_vendor.index.onBLEConnectionStateChange((res) => {
        if (res.connected === false) {
          showToast({
            message: "蓝牙意外断开",
            complete() {
              common_vendor.index.navigateBack();
            }
          });
        }
      });
      common_vendor.index.notifyBLECharacteristicValueChange({
        state: true,
        deviceId,
        serviceId,
        characteristicId,
        success(res) {
          console.log("notifyBLECharacteristicValueChange success", res);
          writeBLECharacteristicValue("0");
        }
      });
    };
    const writeBLECharacteristicValue = (str) => {
      let buffer = stringToUtf8ArrayBuffer(str);
      common_vendor.index.writeBLECharacteristicValue({
        deviceId,
        serviceId,
        characteristicId,
        value: buffer,
        writeType: "writeNoResponse",
        success(res) {
          console.log("写入成功", res);
        },
        fail(res) {
          console.log("写入失败", res);
        }
      });
    };
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_vendor.o(openModal),
        b: common_vendor.p({
          placeholder: true,
          border: true,
          title: "设备控制",
          bgColor: "#3c9cff",
          titleStyle: "color:white;",
          leftIconColor: "white",
          ["left-text"]: "断开连接"
        }),
        c: common_vendor.sr(modal, "19f51743-1", {
          "k": "modal"
        }),
        d: common_vendor.o(disconnect),
        e: common_vendor.p({
          title: "提示",
          content: "是否断开连接此设备",
          showCancelButton: true
        }),
        f: common_vendor.sr(toast, "19f51743-2", {
          "k": "toast"
        }),
        g: common_vendor.p({
          loading: loading.value,
          ["loading-text"]: "连接中...",
          ["font-size"]: "24rpx"
        }),
        h: device.value.on
      }, device.value.on ? {} : {}, {
        i: common_vendor.p({
          span: "12"
        }),
        j: common_vendor.p({
          customStyle: "height:500rpx;margin:30rpx 0 40rpx;"
        }),
        k: common_vendor.t(device.value.light),
        l: common_vendor.o(($event) => writeBLECharacteristicValue(JSON.stringify(device.value))),
        m: common_vendor.o(($event) => device.value.on = $event),
        n: common_vendor.p({
          modelValue: device.value.on
        }),
        o: device.value.on
      }, device.value.on ? {
        p: common_vendor.o(($event) => writeBLECharacteristicValue(JSON.stringify(device.value))),
        q: common_vendor.o(($event) => device.value.auto = $event),
        r: common_vendor.p({
          modelValue: device.value.auto
        })
      } : {}, {
        s: device.value.on && !device.value.auto
      }, device.value.on && !device.value.auto ? {
        t: common_vendor.o(($event) => writeBLECharacteristicValue(JSON.stringify(device.value))),
        v: common_vendor.o(($event) => device.value.power = $event),
        w: common_vendor.p({
          customStyle: "width:500rpx;",
          ["show-value"]: true,
          modelValue: device.value.power
        })
      } : {}, {
        x: device.value.on && device.value.auto
      }, device.value.on && device.value.auto ? {
        y: common_vendor.o(($event) => writeBLECharacteristicValue(JSON.stringify(device.value))),
        z: common_vendor.o(($event) => device.value.luminance = $event),
        A: common_vendor.p({
          customStyle: "width:500rpx;",
          min: "300",
          max: "500",
          step: "10",
          ["show-value"]: true,
          modelValue: device.value.luminance
        })
      } : {}, {
        B: device.value.on
      }, device.value.on ? {
        C: common_vendor.o(($event) => writeBLECharacteristicValue(JSON.stringify(device.value))),
        D: common_vendor.o(($event) => device.value.kelvin = $event),
        E: common_vendor.p({
          customStyle: "width:500rpx;",
          min: "2700",
          max: "6500",
          step: "100",
          ["show-value"]: true,
          modelValue: device.value.kelvin
        })
      } : {}, {
        F: common_vendor.p({
          span: "12"
        }),
        G: common_vendor.p({
          customStyle: "background-color:white;"
        })
      });
    };
  }
};
wx.createPage(_sfc_main);
