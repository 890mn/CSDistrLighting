# CSDistrLighting

This Project is about the Control System of Distributed Lighting (CSDL) Based on ESP32 & ESP8266.  
The final goal is to complete the Main Control System to the Distribute Lighting.

- 第一次了解本项目/没有安装环境？ -> 请从 [这里](Docs/入门指南-上.md) 开始

## 项目进度 | Work Sync

- 2024-10-15 | [Request #1](https://github.com/890mn/CSDistrLighting/pull/1#) | Write the guide
- 2024-10-17 | [Request #2](https://github.com/890mn/CSDistrLighting/pull/2#) | Restruct this Project and All in PlatformIO
- 2024-10-25 | [Request #5](https://github.com/890mn/CSDistrLighting/pull/5#) | Restruct with Doxygen & HinarNoteFormat
- 2024-10-27 | [Request #7](https://github.com/890mn/CSDistrLighting/pull/7#) | Create basic MD frame

## 项目构成 | Project Architecture

About the document composition:

```plaintext
CSDistrLighting
 ├─ Hardware
 │   ├─ ESP32Part   | platformIO
 │   └─ ESP8266Part | platformIO
 ├─ Software
 │   └─ WebPart | uni-app
 ├─ Historical-Legacy
 │   ├─ esp32   | microPython
 │   └─ esp8266 | arduinoIDE
 ├─ Docs
 │   ├─ Function
 │   ├─ Research
 │   ├─ Pic
 │   ├─ 入门指南-上.md
 │   └─ 入门指南-下.md
 └─ README.md
```

About the structrue:

```plaintext

  Phone/Web ─────[BLE]──────┐
                          ESP32──[ESP-NOW]─┬─ 1·ESP8266
  GY30 ──[0x23]──┬──[I2C]───┘              │       └───[Pin4]── WS2812
  OLED ──[0x3C]──┘                         ├─ ...
                                           └─ N·ESP8266 
                                                   └───[Pin4]── WS2812
```

About the Further Note format `HinarNoteFormat` :

```cpp
/* Format Example
 * <> The range of this part may occur
 * <> 关于对应变量的简述
 * <> About which Device it includes
*/ 
```

For Example:

```cpp
struct Device {
    /* <> PowerON - True / PowerOFF - False 
     * <> 设备开关状态 
     * <> Web -[BLE]-> ESP32 -[ESP-NOW]-> ESP8266
     */ 
    bool powerStatus;  
    
    /* <> Auto Mode - True / Manual Mode - False
     * <> 模式切换 对应自动/手动调光模式
     * <> Web -[BLE]-> ESP32
     */ 
    bool modeSwitch;

    ...
}
```

## 主线规划 | Current direction

- [x] **第一阶段：**
  - [x] 基于接手项目资料整理入门指南
  - [x] 重构项目结构
    - [x] 硬件 VS Code + PlatformIO 开发
    - [x] 软件 uni-app 开发  

- [ ] **第二阶段：**
  - [ ] **调研市场LED产品并分析可行性方案**
    - [ ] 对市场常见灯具进行分类总结，表格罗列功能、成本等内容-> [调研表格](Docs/Research/sheet.md)
    - [ ] 进一步分析可控硅调光和DALI两种调光策略 -> [调研分析](Docs/Research/Si-DALI.md)
    - [ ] 设计组合硬件连接实施 -> [电路设计](Docs/Research/Circuit.md)

  - [ ] **优化使用体验 | 熟悉markdown语法**
    - [ ] 顶层抽象出总结可能的场景，不涉及底层实现 -> [顶层模型](Docs/Function/Top-level.md)
    - [ ] 底层基于顶层设想初步构建代码块，框架易于维护 -> [底层实现](Docs/Function/Bottom-level.md)

  - [ ] **完善单点灯光控制 | 熟悉cpp编程调试**
    - ESP8266 LED参数设置、功能测试、ESP-NOW通信
    - ESP32 主控逻辑、BLE通信、ESP-NOW通信、OLED调试参数
    - Web 模块搭建、调试理解

- [ ] **第三阶段:**
  - 引入多传感器并设计**分布式**控制
  - 引入多光源并设计**分布式**部署
  - ...

## 项目简述 | Project Design

1. 硬件部分
   - **ESP8266**：
   作为单点控制模块，但需要扩展为多个节点，各个节点控制不同区域的灯具，同时通过ESP-NOW或Wi-Fi进行分布式数据共享和协调控制

   - **ESP32**：
   用于多个点的环境光感知，数据从各个点收集，传回到主控制节点进行分析和调节

2. 软件部分
   - **uni-app**：
   用于手机端控制，增加对多节点的可视化管理，支持对每个控制点的独立调整或统一调节

   - **ESP-NOW通信协议**：
   使用该协议进行低延迟的数据传输，但需要解决多个节点的通信协调和广播问题，确保数据同步和一致性

3. 功能逻辑
   - **分布式光照控制**：
   通过多点测试，系统可以对不同区域的光线进行实时调整，确保各节点的灯具根据其所在环境的光照强度作出独立调整，也可设定统一策略进行协同调节

   - **主控与分控机制**：
   引入主控节点负责统一策略的制定，分控节点负责具体区域的执行,各节点根据局部环境或主控指令进行调整

4. 未来优化方向
    - 多点数据聚合与优化
      - **数据融合**：
      汇集所有感知节点的数据，基于整体环境情况进行全局优化，调整各区域的灯具亮度以实现最佳照明效果

      - **负载均衡与故障恢复**：
      如果某一节点出现问题，系统可以通过邻近节点进行补偿，确保照明系统稳定运行

    - 多节点通信策略优化：
      - **ESP-NOW优化**：
      探索如何在多个ESP节点间进行高效通信，解决节点间的广播、协作以及数据同步问题

      - **分布式算法引入**：
       研究引入分布式算法进行局部决策和全局优化，确保多个节点之间能够高效地共同决策

    - 实验与多点测试：
      - **多点测试平台**：
      搭建物理实验平台，进行多个感知点的光照数据采集，调试并优化各个节点的响应时间和通信质量

      - **测试与迭代**：
      通过实地测试验证系统的稳定性、响应速度以及分布式布局的效果，并根据测试结果进行调优和算法改进

|1||
|---|--|
{1}|1