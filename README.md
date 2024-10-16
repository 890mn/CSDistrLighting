# CSDistrLighting

This Project is about the Control System of Distributed Lighting (CSDL) Based on ESP32 & ESP8266.
The final goal is to complete the Main Control System to the Distribute Lighting.

## Project Progress

- 2024-10-15 | [Request #1](https://github.com/890mn/CSDistrLighting/pull/1#) | Write the guide
- 2024-10-17 | [Request #2](https://github.com/890mn/CSDistrLighting/pull/2#) | Restruct this Project and All in PlatformIO


## Project Structure

```plaintext
CSDistrLighting
├─ Hardware
│   ├─ ESP32Part(platformIO)
│   └─ ESP8266Part(platformIO)
├─ Software
│   └─ WebPart
├─ Historical-Legacy
│   ├─ esp32(microPython)
│   └─ esp8266(arduinoIDE)
├─ Pic
├─ 入门指南-上.md
└─ 入门指南-下.md
```

## Current direction

- **第一阶段：**
   - 基于接手项目资料整理入门指南
   - 重构项目结构
      - 硬件统一 VS Code + PlatformIO 开发
      - 软件 uni-app 开发  

- **第二阶段：[Current Stage]**
   - **调研市场LED产品并分析可行性方案**
      - 对市场常见灯具进行分类总结，表格罗列功能、成本、是否带有资料等内容
      - 与当前设计的5050规格RGB相比是否有可替代的产品？
         - 有 -> 对新灯管进行电路设计并尝试移植当前逻辑
         - 无 -> 设计220v降压模块使用DC供电

   - **优化使用体验 | 熟悉markdown语法**
      - 顶层抽象出总结可能的场景，不涉及底层实现 -> 顶层markdown文档
      - 底层基于顶层设想初步构建代码块，需要框架易于维护，但不一定要详细 [例如可将一些不懂的用注释伪代码标明] -> 底层markdown文档

   - **完善单点灯光控制 | 熟悉cpp编程调试**
      - ESP8266 LED参数设置、功能测试、ESP-NOW通信
      - ESP32 主控逻辑、BLE通信、ESP-NOW通信、OLED调试参数
      - Web 模块搭建、调试理解

- **第三阶段:**
   - 引入多传感器并设计**分布式**控制
   - 引入多光源并设计**分布式**部署
   - ...

## Project Design

1. **硬件部分：**
   - **ESP8266**：
   作为单点控制模块，但需要扩展为多个节点，各个节点控制不同区域的灯具，同时通过ESP-NOW或Wi-Fi进行分布式数据共享和协调控制

   - **ESP32**：
   用于多个点的环境光感知，数据从各个点收集，传回到主控制节点进行分析和调节

2. **软件部分：**
   - **uni-app**：
   用于手机端控制，增加对多节点的可视化管理，支持对每个控制点的独立调整或统一调节

   - **ESP-NOW通信协议**：
   使用该协议进行低延迟的数据传输，但需要解决多个节点的通信协调和广播问题，确保数据同步和一致性

3. **功能逻辑：**
   - **分布式光照控制**：
   通过多点测试，系统可以对不同区域的光线进行实时调整，确保各节点的灯具根据其所在环境的光照强度作出独立调整，也可设定统一策略进行协同调节

   - **主控与分控机制**：
   引入主控节点负责统一策略的制定，分控节点负责具体区域的执行,各节点根据局部环境或主控指令进行调整

## Expand Part

1. **多点数据聚合与优化：**
   - **数据融合**：
   汇集所有感知节点的数据，基于整体环境情况进行全局优化，调整各区域的灯具亮度以实现最佳照明效果

   - **负载均衡与故障恢复**：
   如果某一节点出现问题，系统可以通过邻近节点进行补偿，确保照明系统稳定运行

2. **多节点通信策略优化：**
   - **ESP-NOW优化**：
   探索如何在多个ESP节点间进行高效通信，解决节点间的广播、协作以及数据同步问题

   - **分布式算法引入**：
   研究引入分布式算法进行局部决策和全局优化，确保多个节点之间能够高效地共同决策

3. **实验与多点测试：**
   - **多点测试平台**：
   搭建物理实验平台，进行多个感知点的光照数据采集，调试并优化各个节点的响应时间和通信质量

   - **测试与迭代**：
   通过实地测试验证系统的稳定性、响应速度以及分布式布局的效果，并根据测试结果进行调优和算法改进
