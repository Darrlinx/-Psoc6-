/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-06-29     lenovo       the first version
 */
#ifndef APPLICATIONS_HX_H_
#define APPLICATIONS_HX_H_

#include <Arduino.h>


class HX711
{
public:
    HX711(int SCK_PIN,int DT_PIN,float GapValueIn=44);
    long Get_Weight();
    void begin();
    int Pressed(int AlarmValue);

    int HX711_SCK;
    int HX711_DT;
    float ValueGap;
    long HX711_Buffer;
    long Weight_Maopi;
    long Weight_Shiwu;
    int CurrentAlarm;
private:
    void Get_Maopi();
    unsigned long HX711_Read();

};

#endif /* APPLICATIONS_HX_H_ */
