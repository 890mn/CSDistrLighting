#ifndef __MAIN_H
#define __MAIN_H

struct Device {
    bool on;       //< 设备开关状态
    int light;     //< 设备光强(lx)
    int power;     //< 设备
    bool autoMode; //<
    int kelvin;    //<
    int luminance; //<
};

#endif