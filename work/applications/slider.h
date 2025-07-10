/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-01     lenovo       the first version
 */
#ifndef APPLICATIONS_SLIDER_H_
#define APPLICATIONS_SLIDER_H_
#include <rtthread.h>
#include "drv_common.h"
#include "cycfg_capsense.h"



#define CAPSENSE_INTR_PRIORITY      (7u)
#define EZI2C_INTR_PRIORITY         (6u)

#define PWM_DEV_NAME "pwm0"
#define PWM_DEV_CHANNEL 0

 void capsense_isr(void);
 void capsense_callback(cy_stc_active_scan_sns_t *ptrActiveScan);
 uint32_t initialize_capsense(void);
 void Slider_Init(void);
 void process_touch(void);


#endif /* APPLICATIONS_SLIDER_H_ */
