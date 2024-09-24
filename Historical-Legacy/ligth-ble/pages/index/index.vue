<template>
	<uv-navbar :placeholder="true" :border="true" title="设备扫描" bgColor="#3c9cff" titleStyle="color:white;"
		left-icon-size="0"></uv-navbar>
	<uv-toast ref="toast"></uv-toast>
	<uv-row customStyle="padding:4px;background-color:#f4f4f5;" gutter="4">
		<uv-col span="5">
			<uv-button :loading="loading" loading-text="扫描中" loadingMode="circle" icon="search" iconColor="white"
				type="primary" text="扫描" @click="start"></uv-button>
		</uv-col>
		<uv-col span="4">
			<uv-button @click="stop" icon="pause-circle" iconColor="white" type="error" text="停止扫描"></uv-button>
		</uv-col>
		<uv-col span="3">
			<uv-button @click="openSetting" icon="setting" iconColor="white" type="success" text="设置"></uv-button>
		</uv-col>
	</uv-row>
	<uv-row customStyle="background-color:white;">
		<uv-col span="12">
			<uv-list border v-if="bleDeviceList.length!==0">
				<uv-list-item v-for="(item,index) in bleDeviceList" :key="index" @click="connect(item)" clickable show-arrow customStyle="padding:20rpx 30rpx;border:1rpx solid #dadbde;">
					<view style="display: flex;align-items: center;justify-content: space-between;">
						<view>
							<text
								style="font-size: 28rpx;display: block;">{{item.name.trim()!==""?item.name.trim():'未知设备'}}</text>
							<text style="display: block;color:#c4c6c9;font-size:24rpx;width: 500rpx;">{{item.deviceId}}</text>
							<text style="display: block;color: #53c21d;font-size:24rpx;width: 500rpx;">信号:
								{{item.RSSI}}</text>
						</view>
						<text style="color:#c4c6c9;font-size:28rpx;display: block;margin-right: 10rpx;margin-bottom: 5rpx;">No services</text>
					</view>
				</uv-list-item>
			</uv-list>
			<uv-empty v-else mode="search" text="没有扫描结果"
				icon="https://cdn.uviewui.com/uview/empty/search.png"></uv-empty>
		</uv-col>
	</uv-row>
</template>

<script setup>
	import {
		ref
	} from 'vue'
	import {
		onHide
	} from '@dcloudio/uni-app';
	import { os } from '@/uni_modules/uv-ui-tools/libs/function/index.js';


	const loading = ref(false)
	const bleDeviceList = ref([])
	const operatingSystem=os();
	const deviceIdList = operatingSystem==='ios'?['4338C594-C742-429C-06A5-72A76E43374F']:['30:C6:F7:43:ED:CA']
	const toast = ref(null)

	const showToast = (params) => {
		toast.value.show({
			...params,
		})
	}

	const onBleDevicesFounded = () => {
		uni.onBluetoothDeviceFound((res) => {
			const temp = [];
			for (const device of res.devices.filter(d => deviceIdList.includes(d.deviceId))) {
				if (temp.find(d => d.deviceId === device.deviceId)) {
					continue
				}
				temp.push(device);
			}
			bleDeviceList.value = [...temp]
			console.log(bleDeviceList.value);
		})
	}


	const startDiscoveringBleDevices = () => {
		uni.startBluetoothDevicesDiscovery({
			allowDuplicatesKey: true,
			interval: 1000,
			success: (res) => {
				console.log('startBluetoothDevicesDiscovery success', res)
				onBleDevicesFounded()
			},
			fail: err => {
				console.log(err, '错误信息')
			}
		})
	}


	const start = () => {
		const systemSetting = uni.getSystemSetting()

		if (!systemSetting.bluetoothEnabled) {
			showToast({
				message: "请打开手机蓝牙"
			})
			return;
		}
		uni.openBluetoothAdapter({
			success(res) {
				loading.value = true
				startDiscoveringBleDevices()
			},
			fail(res) {
				if(res.errno===103){
					showToast({
						message: "请打开设置并允许程序使用手机蓝牙"
					})
				}
			}
		})
	}

	const stop = () => {
		uni.stopBluetoothDevicesDiscovery({
			success: e => {
				loading.value = false
			},
		});
	}

	const openSetting = () => {
		stop()
		uni.openSetting({
			success(res) {}
		});
	}

	const connect = (device) => {
		stop()
		uni.navigateTo({
			url: `/pages/device/device?id=${device.deviceId}`
		})
	}

	onHide(() => {
		stop()
	})
</script>

<style lang="scss">
	page {
		background-color: white;
	}
</style>