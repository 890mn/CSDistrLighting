"use strict";
const common_vendor = require("../../common/vendor.js");
const uni_modules_uvUiTools_libs_function_index = require("../../uni_modules/uv-ui-tools/libs/function/index.js");
if (!Array) {
  const _easycom_uv_navbar2 = common_vendor.resolveComponent("uv-navbar");
  const _easycom_uv_toast2 = common_vendor.resolveComponent("uv-toast");
  const _easycom_uv_button2 = common_vendor.resolveComponent("uv-button");
  const _easycom_uv_col2 = common_vendor.resolveComponent("uv-col");
  const _easycom_uv_row2 = common_vendor.resolveComponent("uv-row");
  const _easycom_uv_list_item2 = common_vendor.resolveComponent("uv-list-item");
  const _easycom_uv_list2 = common_vendor.resolveComponent("uv-list");
  const _easycom_uv_empty2 = common_vendor.resolveComponent("uv-empty");
  (_easycom_uv_navbar2 + _easycom_uv_toast2 + _easycom_uv_button2 + _easycom_uv_col2 + _easycom_uv_row2 + _easycom_uv_list_item2 + _easycom_uv_list2 + _easycom_uv_empty2)();
}
const _easycom_uv_navbar = () => "../../uni_modules/uv-navbar/components/uv-navbar/uv-navbar.js";
const _easycom_uv_toast = () => "../../uni_modules/uv-toast/components/uv-toast/uv-toast.js";
const _easycom_uv_button = () => "../../uni_modules/uv-button/components/uv-button/uv-button.js";
const _easycom_uv_col = () => "../../uni_modules/uv-row/components/uv-col/uv-col.js";
const _easycom_uv_row = () => "../../uni_modules/uv-row/components/uv-row/uv-row.js";
const _easycom_uv_list_item = () => "../../uni_modules/uv-list/components/uv-list-item/uv-list-item.js";
const _easycom_uv_list = () => "../../uni_modules/uv-list/components/uv-list/uv-list.js";
const _easycom_uv_empty = () => "../../uni_modules/uv-empty/components/uv-empty/uv-empty.js";
if (!Math) {
  (_easycom_uv_navbar + _easycom_uv_toast + _easycom_uv_button + _easycom_uv_col + _easycom_uv_row + _easycom_uv_list_item + _easycom_uv_list + _easycom_uv_empty)();
}
const _sfc_main = {
  __name: "index",
  setup(__props) {
    const loading = common_vendor.ref(false);
    const bleDeviceList = common_vendor.ref([]);
    const operatingSystem = uni_modules_uvUiTools_libs_function_index.os();
    const deviceIdList = operatingSystem === "ios" ? ["4338C594-C742-429C-06A5-72A76E43374F"] : ["30:C6:F7:43:ED:CA"];
    const toast = common_vendor.ref(null);
    const showToast = (params) => {
      toast.value.show({
        ...params
      });
    };
    const onBleDevicesFounded = () => {
      common_vendor.index.onBluetoothDeviceFound((res) => {
        const temp = [];
        for (const device of res.devices.filter((d) => deviceIdList.includes(d.deviceId))) {
          if (temp.find((d) => d.deviceId === device.deviceId)) {
            continue;
          }
          temp.push(device);
        }
        bleDeviceList.value = [...temp];
        console.log(bleDeviceList.value);
      });
    };
    const startDiscoveringBleDevices = () => {
      common_vendor.index.startBluetoothDevicesDiscovery({
        allowDuplicatesKey: true,
        interval: 1e3,
        success: (res) => {
          console.log("startBluetoothDevicesDiscovery success", res);
          onBleDevicesFounded();
        },
        fail: (err) => {
          console.log(err, "错误信息");
        }
      });
    };
    const start = () => {
      const systemSetting = common_vendor.index.getSystemSetting();
      if (!systemSetting.bluetoothEnabled) {
        showToast({
          message: "请打开手机蓝牙"
        });
        return;
      }
      common_vendor.index.openBluetoothAdapter({
        success(res) {
          loading.value = true;
          startDiscoveringBleDevices();
        },
        fail(res) {
          if (res.errno === 103) {
            showToast({
              message: "请打开设置并允许程序使用手机蓝牙"
            });
          }
        }
      });
    };
    const stop = () => {
      common_vendor.index.stopBluetoothDevicesDiscovery({
        success: (e) => {
          loading.value = false;
        }
      });
    };
    const openSetting = () => {
      stop();
      common_vendor.index.openSetting({
        success(res) {
        }
      });
    };
    const connect = (device) => {
      stop();
      common_vendor.index.navigateTo({
        url: `/pages/device/device?id=${device.deviceId}`
      });
    };
    common_vendor.onHide(() => {
      stop();
    });
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_vendor.p({
          placeholder: true,
          border: true,
          title: "设备扫描",
          bgColor: "#3c9cff",
          titleStyle: "color:white;",
          ["left-icon-size"]: "0"
        }),
        b: common_vendor.sr(toast, "53726069-1", {
          "k": "toast"
        }),
        c: common_vendor.o(start),
        d: common_vendor.p({
          loading: loading.value,
          ["loading-text"]: "扫描中",
          loadingMode: "circle",
          icon: "search",
          iconColor: "white",
          type: "primary",
          text: "扫描"
        }),
        e: common_vendor.p({
          span: "5"
        }),
        f: common_vendor.o(stop),
        g: common_vendor.p({
          icon: "pause-circle",
          iconColor: "white",
          type: "error",
          text: "停止扫描"
        }),
        h: common_vendor.p({
          span: "4"
        }),
        i: common_vendor.o(openSetting),
        j: common_vendor.p({
          icon: "setting",
          iconColor: "white",
          type: "success",
          text: "设置"
        }),
        k: common_vendor.p({
          span: "3"
        }),
        l: common_vendor.p({
          customStyle: "padding:4px;background-color:#f4f4f5;",
          gutter: "4"
        }),
        m: bleDeviceList.value.length !== 0
      }, bleDeviceList.value.length !== 0 ? {
        n: common_vendor.f(bleDeviceList.value, (item, index, i0) => {
          return {
            a: common_vendor.t(item.name.trim() !== "" ? item.name.trim() : "未知设备"),
            b: common_vendor.t(item.deviceId),
            c: common_vendor.t(item.RSSI),
            d: index,
            e: common_vendor.o(($event) => connect(item), index),
            f: "53726069-12-" + i0 + ",53726069-11"
          };
        }),
        o: common_vendor.p({
          clickable: true,
          ["show-arrow"]: true,
          customStyle: "padding:20rpx 30rpx;border:1rpx solid #dadbde;"
        }),
        p: common_vendor.p({
          border: true
        })
      } : {
        q: common_vendor.p({
          mode: "search",
          text: "没有扫描结果",
          icon: "https://cdn.uviewui.com/uview/empty/search.png"
        })
      }, {
        r: common_vendor.p({
          span: "12"
        }),
        s: common_vendor.p({
          customStyle: "background-color:white;"
        })
      });
    };
  }
};
wx.createPage(_sfc_main);
