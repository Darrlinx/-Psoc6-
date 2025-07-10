//#include <Wire.h>
//#include <Adafruit_TCS34725.h>
//#include "RTduino.h"
//#include "Config.h"
//
//#if defined IOT_THREAD_ENABLE
//#define RGB_EVENT 1 << 2                // RGB采集数据事件标志
//extern rt_event_t IOT_EVENT;            // IOT事件集
//rt_mq_t RGB_Data_MQ = RT_NULL;          // 传递给IOT线程的消息队列
//#endif
//
//#if defined DIS_THREAD_ENABLE
//rt_mq_t RGB_Data_MQ_Dis = RT_NULL;      // 传递给Display线程的消息队列
//#endif
//
//// 存储RGB数据: 颜色温度(K), 光照强度(lux), R, G, B, C(清晰度)
//float RGB_Data[6] = {0};
//
//// 初始化传感器(积分时间614ms, 增益1x)
//Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
//
//void RGB_setup() {
//  Serial.begin();
//
//#if defined IOT_THREAD_ENABLE
//    RGB_Data_MQ = rt_mq_create("RGB_Mq", sizeof(RGB_Data), 10, RT_IPC_FLAG_PRIO);
//    if(RGB_Data_MQ == RT_NULL) {
//      Serial.println("RGB MessageQueue_IOT Create Error");
//    }
//#endif
//
//#if defined DIS_THREAD_ENABLE
//    RGB_Data_MQ_Dis = rt_mq_create("RGB_Mq_Dis", sizeof(RGB_Data), 10, RT_IPC_FLAG_PRIO);
//    if(RGB_Data_MQ_Dis == RT_NULL) {
//      Serial.println("RGB MessageQueue_Dis Create Error");
//    }
//#endif
//
//  while (!Serial) delay(100);   // 等待串口就绪
//
//  if (tcs.begin()) {
//    Serial.println("Found TCS34725 sensor");
//  } else {
//    Serial.println("No TCS34725 found ... check your connections");
//    while (1); // 挂起程序
//  }
//
//  // 可以在这里配置传感器参数(可选)
//  // tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_154MS);
//  // tcs.setGain(TCS34725_GAIN_4X);
//}
//
//void RGB_loop() {
//  uint16_t r, g, b, c;
//
//  // 获取原始数据
//  tcs.getRawData(&r, &g, &b, &c);
//
//  // 计算颜色温度和光照强度
//  RGB_Data[0] = tcs.calculateColorTemperature_dn40(r, g, b, c); // 颜色温度(K)
//  RGB_Data[1] = tcs.calculateLux(r, g, b);                     // 光照强度(lux)
//  RGB_Data[2] = r;                                             // 红色分量
//  RGB_Data[3] = g;                                             // 绿色分量
//  RGB_Data[4] = b;                                             // 蓝色分量
//  RGB_Data[5] = c;                                             // 清晰度
//
//#ifndef NO_USING_DATA_OUTPUT
//  // 串口输出数据
//  Serial.print("Color Temp: "); Serial.print(RGB_Data[0]); Serial.print(" K - ");
//  Serial.print("Lux: "); Serial.print(RGB_Data[1]); Serial.print(" - ");
//  Serial.print("R: "); Serial.print(RGB_Data[2]); Serial.print(" ");
//  Serial.print("G: "); Serial.print(RGB_Data[3]); Serial.print(" ");
//  Serial.print("B: "); Serial.print(RGB_Data[4]); Serial.print(" ");
//  Serial.print("C: "); Serial.print(RGB_Data[5]); Serial.println(" ");
//#endif
//
//#if defined IOT_THREAD_ENABLE
//  // 当启动IOT线程的时候
//  if(IOT_EVENT != RT_NULL) {
//      // 触发事件，通知IOT线程来取数据
//      if(rt_event_send(IOT_EVENT, RGB_EVENT) != RT_EOK) {
//          Serial.println("RGB Event Send Error");
//      }
//      // 使用消息队列，将数据传输给IOT线程
//      if(rt_mq_send_wait(RGB_Data_MQ, &RGB_Data, sizeof(RGB_Data), 100) != RT_EOK) {
//          Serial.println("RGB MQ Send To IOT Error");
//      }
//  }
//#endif
//
//#if defined DIS_THREAD_ENABLE
//  // 使用消息队列，将数据传输到Display线程
//  if(rt_mq_send_wait(RGB_Data_MQ_Dis, &RGB_Data, sizeof(RGB_Data), 1000) != RT_EOK) {
//      Serial.println("RGB MQ Send To Dis Error");
//  }
//#endif
//
//  delay(500); // 适当延迟，避免数据更新过快
//}
//
//// 初始化RTduino线程
//static int rtduino_init(void) {
//    rtduino_sketch_loader_create("RT_RGB", RGB_setup, RGB_loop);
//    return 0;
//}
//INIT_COMPONENT_EXPORT(rtduino_init);
