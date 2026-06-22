// sensor_data.h
#ifndef __SENSOR_DATA_H
#define __SENSOR_DATA_H

#include <stdint.h>

// 传感器数据
typedef struct {
    uint8_t temp;           // DHT11 温度
    uint8_t humi;            // DHT11 湿度
    uint8_t light_status;    // 光敏状态 0=亮 1=暗
    uint8_t dht11_valid;     // DHT11 读取成功标志
} SensorData_t;

// 控制状态
typedef struct {
    uint8_t motor_level;     // 电机档位 0-3
    uint8_t motor_running;   // 电机运行标志
    uint8_t led_on;          // LED 状态
    uint8_t voice_cmd;       // 最新语音命令
} ControlState_t;

// 显示缓冲区
typedef struct {
    char line1[32];          // OLED 第0行
    char line2[32];          // OLED 第2行
    char line3[32];          // OLED 第4行
    char line4[32];          // OLED 第6行
} DisplayBuf_t;

// 全局变量（extern 声明，在 main.c 定义）
extern SensorData_t g_sensor;
extern ControlState_t g_ctrl;
extern DisplayBuf_t g_display;
extern osMutexId_t data_mutex;    // 数据互斥锁

#endif