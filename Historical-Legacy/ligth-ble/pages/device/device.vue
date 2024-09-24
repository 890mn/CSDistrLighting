<template>
	<uv-navbar :placeholder="true" :border="true" @leftClick="openModal" title="设备控制" bgColor="#3c9cff"
		titleStyle="color:white;" leftIconColor="white" left-text="断开连接"></uv-navbar>
	<uv-modal ref="modal" title="提示" content='是否断开连接此设备' :showCancelButton="true" @confirm="disconnect"></uv-modal>
	<uv-toast ref="toast"></uv-toast>
	<uv-loading-page :loading="loading" loading-text="连接中..." font-size="24rpx"></uv-loading-page>
	<uv-row customStyle="height:500rpx;margin:30rpx 0 40rpx;">
		<uv-col span="12">
			<image style="width: 500rpx;height: 500rpx;margin: 0 auto;display: block;" v-if="device.on"
				src="data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTAyNCIgaGVpZ2h0PSIxMDI0IiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIGNsYXNzPSJpY29uIj48cGF0aCBmaWxsPSIjZmZjMDAwIiBkPSJNNjM3LjMyMiA4MjYuNTdoLTIwNS42MmMtMTUuNDggMC0yOC4wNCAxMi41NS0yOC4wNCAyOC4wNHMxMi41NiAyOC4wNCAyOC4wNCAyOC4wNGgyMDUuNjJjMTUuNDggMCAyOC4wNC0xMi41NSAyOC4wNC0yOC4wNHMtMTIuNTYtMjguMDQtMjguMDQtMjguMDR6TTU4MS4yNDQgOTIwLjAzNEg0ODcuNzhjLTE1LjQ4IDAtMjguMDQgMTIuNTUtMjguMDQgMjguMDRzMTIuNTYgMjguMDQgMjguMDQgMjguMDRoOTMuNDY0YzE1LjQ4IDAgMjguMDQtMTIuNTUgMjguMDQtMjguMDRzLTEyLjU2LTI4LjA0LTI4LjA0LTI4LjA0ek01MjEuOTMgMTk5LjA0NWMtMTQ5LjA1IDAtMjcwLjI5NyAxMTkuMTEyLTI3MC4yOTcgMjY1LjUxNSAwIDk1LjM5IDUwLjgyMyAxODEuNjMgMTMzLjc5OCAyMjkuMjE0bDE1LjIzMiA4My44OGMyLjQ0NiAxMy41NDUgMTQuMjU3IDIzLjAzOCAyNy41NDcgMjMuMDM4YTI4LjcgMjguNyAwIDAgMCA1LjAzOC0uNDU2YzE1LjI0My0yLjc3NSAyNS4zNTYtMTcuMzcgMjIuNTgyLTMyLjYwM2wtMTcuNjM0LTk3LjEwNWMtMS40MDgtNy43ODItNS45NTgtMTQuMTg1LTEyLjA2OC0xOC4yNTVsLjEzLS4yNjVjLTczLjEyOC0zNS43NjItMTE4LjU0Ni0xMDcuNTg2LTExOC41NDYtMTg3LjQ1IDAtMTE1LjQ3OSA5Ni4wOTMtMjA5LjQzNSAyMTQuMjE4LTIwOS40MzVzMjE0LjIxOCA5My45NTYgMjE0LjIxOCAyMDkuNDM1YzAgNzAuNjk0LTM2LjA2MyAxMzUuOTQ4LTk2LjQ2IDE3NC45MDUtOC41OSAzLjM4OC0xNS4zODYgMTAuOS0xNy4zMDMgMjAuNjRMNjAxLjI4MiA3NjcuMjJjLTIuOTk0IDE1LjE5NyA2LjkgMjkuOTM4IDIyLjA4OSAzMi45MyAxLjgyNS4zNjYgMy42NS41MzkgNS40NTguNTM5IDEzLjEyNSAwIDI0Ljg0NS05LjI2NCAyNy40NzQtMjIuNjI2bDE4LjY3LTk0Ljc3NGM3My41MDctNDkuNjc1IDExNy4yNTQtMTMwLjgyNiAxMTcuMjU0LTIxOC43MzIgMC0xNDYuNDAyLTEyMS4yNDctMjY1LjUxMy0yNzAuMjk3LTI2NS41MTN6Ii8+PHBhdGggZmlsbD0iI2ZmYzAwMCIgZD0iTTQ5My45MjcgMzA0LjY5NGMtMS41ODgtMTAuMTk2LTExLjEzNS0xNy4yMDUtMjEuMzU4LTE1LjU4LTkwLjgxNyAxNC4xODQtMTI3LjE2MiA5OC40MDItMTMzLjY5NyAxNDAuOTQ0LTEuNTcgMTAuMTg2IDUuNDAzIDE5LjY4NyAxNS41ODkgMjEuMjc1Ljk2Ny4xNTYgMS45NTMuMjI4IDIuOTAyLjIyOCA5LjAzNiAwIDE2Ljk3Ny02LjU4IDE4LjQ1NS0xNS43NzIuNjIyLTMuOTI0IDE2LjMwMi05Ni4yNzQgMTAyLjUxOC0xMDkuNzQ2IDEwLjIwNy0xLjU4OCAxNy4xOC0xMS4xNTQgMTUuNTkxLTIxLjM1ek00NTMuNTg1IDYwOC42N2MxMC4zMzIgMCAxOC42OTItOC4zNyAxOC42OTItMTguNjkzdi05OC40MzhsNDIuOTU0IDM0LjU5M2M2LjcxOCA1LjQyMSAxNi4zMiA1LjUzIDIzLjE4My4yMWw0Ni4wMi0zNS43MDd2OTkuMzQyYzAgMTAuMzIzIDguMzYgMTguNjkzIDE4LjY5MiAxOC42OTMgMTAuMzMzIDAgMTguNjkzLTguMzcgMTguNjkzLTE4LjY5M1Y0NTIuNDc0YzAtNy4xMzctNC4wNy0xMy42NDYtMTAuNDc4LTE2Ljc4NS02LjM3Mi0zLjE0OS0xNC4wNTctMi4zNjQtMTkuNjc5IDIuMDE3bC02NC40OTQgNTAuMDM1LTYxLjg2NS00OS44MjVjLTUuNTg2LTQuNTE4LTEzLjI5LTUuNDEzLTE5Ljc4Ny0yLjNhMTguNjY4IDE4LjY2OCAwIDAgMC0xMC42MjQgMTYuODU3djEzNy41MDNjMCAxMC4zMjQgOC4zNjEgMTguNjk0IDE4LjY5MyAxOC42OTR6TTE3MS4zMTMgMjc5LjE4Mmw3MS43NzcgNDEuNDM4YTE4LjU5IDE4LjU5IDAgMCAwIDkuMzI5IDIuNTAxYzYuNDYyIDAgMTIuNzQyLTMuMzUgMTYuMjEtOS4zNDcgNS4xNjYtOC45NDQgMi4wOTktMjAuMzcyLTYuODQ2LTI1LjUzOGwtNzEuNzc4LTQxLjQzOGMtOC45NDQtNS4xNTctMjAuMzcyLTIuMTE3LTI1LjUzOCA2Ljg0Ni01LjE2NiA4Ljk0Ni0yLjA5OSAyMC4zNzMgNi44NDYgMjUuNTM4ek04NzkuMDQ3IDY0NC42MTNsLTcxLjc3OC00MS40MzdjLTguOTI2LTUuMTU3LTIwLjM3Mi0yLjEwOC0yNS41MzkgNi44NDUtNS4xNjUgOC45NDUtMi4wOTkgMjAuMzcyIDYuODQ2IDI1LjU0bDcxLjc3OCA0MS40MzdhMTguNTkgMTguNTkgMCAwIDAgOS4zMjggMi41YzYuNDYzIDAgMTIuNzQzLTMuMzQ4IDE2LjIxLTkuMzQ2IDUuMTY2LTguOTQ1IDIuMS0yMC4zNzItNi44NDUtMjUuNTM5ek01MDIuNjUzIDE2MC4wNDRjMTAuMzMyIDAgMTguNjkzLTguMzcgMTguNjkzLTE4LjY5M3YtNzQuNzdjMC0xMC4zMjQtOC4zNi0xOC42OTMtMTguNjkzLTE4LjY5My0xMC4zMzIgMC0xOC42OTMgOC4zNy0xOC42OTMgMTguNjkydjc0Ljc3MWMwIDEwLjMyMyA4LjM2IDE4LjY5MyAxOC42OTMgMTguNjkzek0zNTEuNTIzIDE5OC40OTdjMy40NjggNS45OTYgOS43NDggOS4zNDcgMTYuMjEgOS4zNDcgMy4xNzcgMCA2LjM5LS44MDQgOS4zMjktMi41MDEgOC45NDQtNS4xNjYgMTIuMDExLTE2LjU5NCA2Ljg0Ni0yNS41MzlsLTQxLjQzOC03MS43NzhjLTUuMTg0LTguOTU0LTE2LjYzLTEyLjAxMS0yNS41MzktNi44NDYtOC45NDQgNS4xNjYtMTIuMDExIDE2LjU5NC02Ljg0NiAyNS41NGw0MS40MzggNzEuNzc3ek0yMjIuMjYyIDQ0MC40MzVjMC0xMC4zMjMtOC4zNi0xOC42OTMtMTguNjkzLTE4LjY5M2gtOTMuNDYzYy0xMC4zMzMgMC0xOC42OTMgOC4zNy0xOC42OTMgMTguNjkzczguMzYgMTguNjkzIDE4LjY5MyAxOC42OTNoOTMuNDYzYzEwLjMzMyAwIDE4LjY5My04LjM3IDE4LjY5My0xOC42OTN6TTkxMy44OTQgNDIxLjc0MmgtOTMuNDYzYy0xMC4zMzMgMC0xOC42OTMgOC4zNy0xOC42OTMgMTguNjkzczguMzYgMTguNjkzIDE4LjY5MyAxOC42OTNoOTMuNDYzYzEwLjMzMyAwIDE4LjY5My04LjM3IDE4LjY5My0xOC42OTNzLTguMzYtMTguNjkzLTE4LjY5My0xOC42OTN6TTI0My4wOSA2MDMuMTc2bC03MS43NzcgNDEuNDM3Yy04Ljk0NSA1LjE2Ni0xMi4wMTIgMTYuNTk0LTYuODQ2IDI1LjUzOSAzLjQ2OCA1Ljk5NyA5Ljc0OCA5LjM0NyAxNi4yMSA5LjM0NyAzLjE3NiAwIDYuMzktLjgwMyA5LjMyOC0yLjUwMWw3MS43NzgtNDEuNDM4YzguOTQ1LTUuMTY2IDEyLjAxMi0xNi41OTQgNi44NDYtMjUuNTM5LTUuMTg1LTguOTUzLTE2LjYzLTEyLjAwMy0yNS41MzktNi44NDV6TTc5Ny45NCAzMjMuMTIyYzMuMTc3IDAgNi4zOS0uODAzIDkuMzI5LTIuNWw3MS43NzgtNDEuNDM4YzguOTQ0LTUuMTY2IDEyLjAxMS0xNi41OTQgNi44NDYtMjUuNTQtNS4xODUtOC45NjItMTYuNjQ5LTEyLjAwMi0yNS41NC02Ljg0NWwtNzEuNzc3IDQxLjQzOGMtOC45NDUgNS4xNjUtMTIuMDExIDE2LjU5NC02Ljg0NiAyNS41MzggMy40NyA1Ljk5NyA5Ljc0OCA5LjM0NyAxNi4yMSA5LjM0N3pNNjczLjMxNiAyMDUuMzQzYTE4LjU5IDE4LjU5IDAgMCAwIDkuMzI5IDIuNWM2LjQ2MiAwIDEyLjc0Mi0zLjM0OSAxNi4yMS05LjM0Nmw0MS40MzctNzEuNzc4YzUuMTY2LTguOTQ1IDIuMS0yMC4zNzItNi44NDUtMjUuNTM5LTguOTQ1LTUuMTY1LTIwLjM3Mi0yLjEwOC0yNS41NCA2Ljg0NmwtNDEuNDM3IDcxLjc3OGMtNS4xNjYgOC45NDUtMi4wOTkgMjAuMzczIDYuODQ2IDI1LjUzOXoiLz48L3N2Zz4=">
			</image>
			<image style="width: 500rpx;height: 500rpx;margin: 0 auto;display: block;" v-else
				src="data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTAyNCIgaGVpZ2h0PSIxMDI0IiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIGNsYXNzPSJpY29uIj48cGF0aCBmaWxsPSIjY2NjIiBkPSJNNjM3LjMyMiA4MjYuNTdoLTIwNS42MmMtMTUuNDggMC0yOC4wNCAxMi41NS0yOC4wNCAyOC4wNHMxMi41NiAyOC4wNCAyOC4wNCAyOC4wNGgyMDUuNjJjMTUuNDggMCAyOC4wNC0xMi41NSAyOC4wNC0yOC4wNHMtMTIuNTYtMjguMDQtMjguMDQtMjguMDR6TTU4MS4yNDQgOTIwLjAzNEg0ODcuNzhjLTE1LjQ4IDAtMjguMDQgMTIuNTUtMjguMDQgMjguMDRzMTIuNTYgMjguMDQgMjguMDQgMjguMDRoOTMuNDY0YzE1LjQ4IDAgMjguMDQtMTIuNTUgMjguMDQtMjguMDRzLTEyLjU2LTI4LjA0LTI4LjA0LTI4LjA0ek01MjEuOTMgMTk5LjA0NWMtMTQ5LjA1IDAtMjcwLjI5NyAxMTkuMTEyLTI3MC4yOTcgMjY1LjUxNSAwIDk1LjM5IDUwLjgyMyAxODEuNjMgMTMzLjc5OCAyMjkuMjE0bDE1LjIzMiA4My44OGMyLjQ0NiAxMy41NDUgMTQuMjU3IDIzLjAzOCAyNy41NDcgMjMuMDM4YTI4LjcgMjguNyAwIDAgMCA1LjAzOC0uNDU2YzE1LjI0My0yLjc3NSAyNS4zNTYtMTcuMzcgMjIuNTgyLTMyLjYwM2wtMTcuNjM0LTk3LjEwNWMtMS40MDgtNy43ODItNS45NTgtMTQuMTg1LTEyLjA2OC0xOC4yNTVsLjEzLS4yNjVjLTczLjEyOC0zNS43NjItMTE4LjU0Ni0xMDcuNTg2LTExOC41NDYtMTg3LjQ1IDAtMTE1LjQ3OSA5Ni4wOTMtMjA5LjQzNSAyMTQuMjE4LTIwOS40MzVzMjE0LjIxOCA5My45NTYgMjE0LjIxOCAyMDkuNDM1YzAgNzAuNjk0LTM2LjA2MyAxMzUuOTQ4LTk2LjQ2IDE3NC45MDUtOC41OSAzLjM4OC0xNS4zODYgMTAuOS0xNy4zMDMgMjAuNjRMNjAxLjI4MiA3NjcuMjJjLTIuOTk0IDE1LjE5NyA2LjkgMjkuOTM4IDIyLjA4OSAzMi45MyAxLjgyNS4zNjYgMy42NS41MzkgNS40NTguNTM5IDEzLjEyNSAwIDI0Ljg0NS05LjI2NCAyNy40NzQtMjIuNjI2bDE4LjY3LTk0Ljc3NGM3My41MDctNDkuNjc1IDExNy4yNTQtMTMwLjgyNiAxMTcuMjU0LTIxOC43MzIgMC0xNDYuNDAyLTEyMS4yNDctMjY1LjUxMy0yNzAuMjk3LTI2NS41MTN6Ii8+PHBhdGggZmlsbD0iI2NjYyIgZD0iTTQ5My45MjcgMzA0LjY5NGMtMS41ODgtMTAuMTk2LTExLjEzNS0xNy4yMDUtMjEuMzU4LTE1LjU4LTkwLjgxNyAxNC4xODQtMTI3LjE2MiA5OC40MDItMTMzLjY5NyAxNDAuOTQ0LTEuNTcgMTAuMTg2IDUuNDAzIDE5LjY4NyAxNS41ODkgMjEuMjc1Ljk2Ny4xNTYgMS45NTMuMjI4IDIuOTAyLjIyOCA5LjAzNiAwIDE2Ljk3Ny02LjU4IDE4LjQ1NS0xNS43NzIuNjIyLTMuOTI0IDE2LjMwMi05Ni4yNzQgMTAyLjUxOC0xMDkuNzQ2IDEwLjIwNy0xLjU4OCAxNy4xOC0xMS4xNTQgMTUuNTkxLTIxLjM1ek00NTMuNTg1IDYwOC42N2MxMC4zMzIgMCAxOC42OTItOC4zNyAxOC42OTItMTguNjkzdi05OC40MzhsNDIuOTU0IDM0LjU5M2M2LjcxOCA1LjQyMSAxNi4zMiA1LjUzIDIzLjE4My4yMWw0Ni4wMi0zNS43MDd2OTkuMzQyYzAgMTAuMzIzIDguMzYgMTguNjkzIDE4LjY5MiAxOC42OTMgMTAuMzMzIDAgMTguNjkzLTguMzcgMTguNjkzLTE4LjY5M1Y0NTIuNDc0YzAtNy4xMzctNC4wNy0xMy42NDYtMTAuNDc4LTE2Ljc4NS02LjM3Mi0zLjE0OS0xNC4wNTctMi4zNjQtMTkuNjc5IDIuMDE3bC02NC40OTQgNTAuMDM1LTYxLjg2NS00OS44MjVjLTUuNTg2LTQuNTE4LTEzLjI5LTUuNDEzLTE5Ljc4Ny0yLjNhMTguNjY4IDE4LjY2OCAwIDAgMC0xMC42MjQgMTYuODU3djEzNy41MDNjMCAxMC4zMjQgOC4zNjEgMTguNjk0IDE4LjY5MyAxOC42OTR6Ii8+PC9zdmc+">
			</image>
		</uv-col>
	</uv-row>
	<uv-row customStyle="background-color:white;">
		<uv-col span="12">
			<uv-cell-group>
				<uv-cell>
					<template v-slot:title>
						<text style="font-size: 32rpx;">当前照度 (Lx)</text>
					</template>
					<!-- 自定义右侧值 -->
					<template v-slot:value>
						<text style="font-size:32rpx;">{{device.light}}</text>
					</template>
				</uv-cell>
				<uv-cell>
					<template v-slot:title>
						<text style="font-size: 32rpx;">开关</text>
					</template>
					<!-- 自定义右侧值 -->
					<template v-slot:value>
						<uv-switch v-model="device.on"
							@change="writeBLECharacteristicValue(JSON.stringify(device))"></uv-switch>
					</template>
				</uv-cell>
				<uv-cell v-if="device.on">
					<template v-slot:title>
						<text style="font-size: 32rpx;">自动调光</text>
					</template>
					<!-- 自定义右侧值 -->
					<template v-slot:value>
						<uv-switch v-model="device.auto"
							@change="writeBLECharacteristicValue(JSON.stringify(device))"></uv-switch>
					</template>
				</uv-cell>
				<uv-cell v-if="device.on && !device.auto">
					<template v-slot:title>
						<text style="font-size: 32rpx;width: 200rpx;">亮度 (%)</text>
					</template>
					<!-- 自定义右侧值 -->
					<template v-slot:value>
						<uv-slider @change="writeBLECharacteristicValue(JSON.stringify(device))"
							customStyle="width:500rpx;" v-model="device.power" :show-value="true"></uv-slider>
					</template>
				</uv-cell>
				<uv-cell v-if="device.on && device.auto">
					<template v-slot:title>
						<text style="font-size: 32rpx;width: 200rpx;">恒定照度 (Lx)</text>
					</template>
					<!-- 自定义右侧值 -->
					<template v-slot:value>
						<uv-slider @change="writeBLECharacteristicValue(JSON.stringify(device))"
							customStyle="width:500rpx;" min="300" max="500" step="10" v-model="device.luminance" :show-value="true"></uv-slider>
					</template>
				</uv-cell>
				<uv-cell v-if="device.on">
					<template v-slot:title>
						<text style="font-size: 32rpx;width: 200rpx;">色温 (K)</text>
					</template>
					<!-- 自定义右侧值 -->
					<template v-slot:value>
						<uv-slider @change="writeBLECharacteristicValue(JSON.stringify(device))"
							customStyle="width:500rpx;" min="2700" max="6500" step="100" v-model="device.kelvin" :show-value="true"></uv-slider>
					</template>
				</uv-cell>
			</uv-cell-group>
		</uv-col>
	</uv-row>


</template>

<script setup>
	import {
		ref,
	} from 'vue'

	import {
		onReady
	} from '@dcloudio/uni-app';
	import { os } from '@/uni_modules/uv-ui-tools/libs/function/index.js';

	const operatingSystem=os();
	const deviceId = operatingSystem==='ios'?'4338C594-C742-429C-06A5-72A76E43374F':'30:C6:F7:43:ED:CA'
	const serviceId = "6E400000-B5A3-F393-E0A9-E50E24DCCA9E"
	const characteristicId = "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
	const toast = ref(null)
	const modal = ref(null)
	const loading = ref(false)
	const device = ref({
		light: 0,
		power: 50,
		on: false,
		auto: false,
		kelvin:4000,
		luminance:400,
	})


	const openModal = () => {
		modal.value.open();
	}


	const disconnect = () => {
		uni.closeBLEConnection({
			deviceId,
			success(res) {
				uni.navigateBack();
			}
		})
	}

	const showToast = (params) => {
		toast.value.show({
			...params,
		})
	}

	const createBLEConnection = () => {
		uni.createBLEConnection({
			deviceId,
			success(res) {
				console.log("蓝牙连接成功", res)
				uni.setBLEMTU({
					deviceId,
					mtu:185,
					success(res) {
						console.log("MTU设置成功", res)
					},
					fail(res){
						console.log("MTU设置失败", res)
					},
					complete() {
						getBLEDeviceServices()
					}
				})
			},
			fail(res) {
				console.log("蓝牙连接失败", res)
			}
		})
	}

	onReady(() => {
		loading.value = true;
		createBLEConnection()
	})



	const getBLEDeviceServices = () => {
		uni.getBLEDeviceServices({
			deviceId,
			success: (res) => {
				console.log('device services:', res)
				getBLEDeviceCharacteristics()
			}
		})
	}

	const getBLEDeviceCharacteristics = () => {
		uni.getBLEDeviceCharacteristics({
			deviceId,
			serviceId,
			success: (res) => {
				console.log('device characteristics:', res)
				notifyBLECharacteristicValueChange()
			},
		})
	}

	function stringToUtf8ArrayBuffer(str) {
		const utf8 = [];
		for (let i = 0; i < str.length; i++) {
			let charCode = str.charCodeAt(i);
			if (charCode < 0x80) {
				utf8.push(charCode);
			} else if (charCode < 0x800) {
				utf8.push(0xC0 | (charCode >> 6));
				utf8.push(0x80 | (charCode & 0x3F));
			} else {
				utf8.push(0xE0 | (charCode >> 12));
				utf8.push(0x80 | ((charCode >> 6) & 0x3F));
				utf8.push(0x80 | (charCode & 0x3F));
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

		for (let i = 0; i < view.length;) {
			const currentByte = view[i];

			if (currentByte < 0x80) {
				result += String.fromCharCode(currentByte);
				i++;
			} else if ((currentByte & 0xE0) === 0xC0) {
				const charCode = ((currentByte & 0x1F) << 6) | (view[i + 1] & 0x3F);
				result += String.fromCharCode(charCode);
				i += 2;
			} else {
				const charCode = ((currentByte & 0x0F) << 12) | ((view[i + 1] & 0x3F) << 6) | (view[i + 2] & 0x3F);
				result += String.fromCharCode(charCode);
				i += 3;
			}
		}

		return result;
	}

	const notifyBLECharacteristicValueChange = () => {
		// 必须在这里的回调才能获取
		uni.onBLECharacteristicValueChange((res) => {
			let value = utf8ArrayBufferToString(res.value)
			console.log("====", value);
			if (value.startsWith('[')) {
				value = JSON.parse(value)
				device.value.power = value[0].power
				device.value.on = value[0].on
				device.value.auto = value[0].auto
				device.value.kelvin=value[0].kelvin
				device.value.luminance=value[0].luminance
				loading.value = false
				showToast({
					message: '连接成功'
				})
			} else {
				value = JSON.parse(value)
				device.value.light = value.light
			}
		})

		uni.onBLEConnectionStateChange((res) => {
			if (res.connected === false) {
				showToast({
					message: '蓝牙意外断开',
					complete() {
						uni.navigateBack()
					}
				})
			}
		})
		uni.notifyBLECharacteristicValueChange({
			state: true,
			deviceId,
			serviceId,
			characteristicId,
			success(res) {
				console.log('notifyBLECharacteristicValueChange success', res)
				writeBLECharacteristicValue('0')
			}
		})



	}




	const writeBLECharacteristicValue = (str) => {
		let buffer = stringToUtf8ArrayBuffer(str)
		uni.writeBLECharacteristicValue({
			deviceId,
			serviceId,
			characteristicId,
			value: buffer,
			writeType:'writeNoResponse',
			success(res) {
				console.log("写入成功", res);
			},
			fail(res) {
				console.log("写入失败", res)
			}
		})
	}
</script>

<style lang="scss">
	page {
		background-color: #f4f4f5;
	}
</style>