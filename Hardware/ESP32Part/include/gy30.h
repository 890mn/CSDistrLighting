#ifndef __GY30_H
#define __GY30_H

#define GY30_ADDRESS 0x23

/* initGY30 Function
 * <> Initializes the GY30 light sensor
 * <> 初始化GY30光传感器
*/
void initGY30();

/* updateGY30 Function
 *
 * <> Reads data from the GY30 light sensor and returns the light intensity
 *
 * <> 从GY30光传感器读取数据并返回光强度
 *
 * @return The light intensity in lux
*/
float updateGY30();

#endif
