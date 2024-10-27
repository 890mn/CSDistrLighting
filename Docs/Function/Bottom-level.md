# 底层模块设计

本文档为基于第二阶段的markdown底层设计，基于顶层设想初步构建代码块

![底层基于顶层设想初步构建代码块，需要框架易于维护，但不一定要详细](../Pic/func-1.jpg)

## TODO List

基于上层已合并TODO完成代码块构建

### Web端模式按钮设计

- [x] 已关联顶层TODO | [**日夜模式**](Top-level.md#日夜模式)
- [ ] ESP32
- [x] Web
- [ ] ESP8266

对于模式切换可以单独设计一个按钮，示例如下：  

```vue
<template>
	<view style="padding: 20px;">
		<uv-button type="primary" text="日/夜切换"></uv-button>
	</view>
</template>
<script>
export default {
	data() {
		return {
			disabled: true
		};
	}
};
</script>
```
