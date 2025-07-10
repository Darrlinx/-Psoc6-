/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-28     Rbb666       first version
 */

#include "slider.h"

static rt_sem_t trans_done_semphr = RT_NULL;


static struct rt_device_pwm *pwm_dev;

//中断处理
void capsense_isr(void)
{
    rt_interrupt_enter();

    Cy_CapSense_InterruptHandler(CYBSP_CSD_HW, &cy_capsense_context);

    rt_interrupt_leave();
}

//释放信号量
void capsense_callback(cy_stc_active_scan_sns_t *ptrActiveScan)
{
    rt_sem_release(trans_done_semphr);
}

//触摸滑条初始化
uint32_t initialize_capsense(void)
{
    uint32_t status = CYRET_SUCCESS;

    /* CapSense interrupt configuration parameters */
    static const cy_stc_sysint_t capSense_intr_config =
    {
        .intrSrc = csd_interrupt_IRQn,
        .intrPriority = CAPSENSE_INTR_PRIORITY,
    };

    /* Capture the CSD HW block and initialize it to the default state. */
    status = Cy_CapSense_Init(&cy_capsense_context);
    if (CYRET_SUCCESS != status)
    {
        return status;
    }

    /* Initialize CapSense interrupt */
    cyhal_system_set_isr(csd_interrupt_IRQn, csd_interrupt_IRQn, CAPSENSE_INTR_PRIORITY, &capsense_isr);
    NVIC_ClearPendingIRQ(capSense_intr_config.intrSrc);
    NVIC_EnableIRQ(capSense_intr_config.intrSrc);

    /* Initialize the CapSense firmware modules. */
    status = Cy_CapSense_Enable(&cy_capsense_context);
    if (CYRET_SUCCESS != status)
    {
        return status;
    }

    /* Assign a callback function to indicate end of CapSense scan. */
    status = Cy_CapSense_RegisterCallback(CY_CAPSENSE_END_OF_SCAN_E,
                                          capsense_callback, &cy_capsense_context);
    if (CYRET_SUCCESS != status)
    {
        return status;
    }

    return status;
}

 void Slider_Init(void)
 {

    cy_rslt_t result;

    result = initialize_capsense();

    if (CYRET_SUCCESS != result)
    {
        /* Halt the CPU if CapSense initialization failed */
        RT_ASSERT(0);
    }
    //创建邮箱
//    SLD_MQ_Dis = rt_mq_create("Slider_MQ_Dis", 8, 10, RT_IPC_FLAG_PRIO);
//    if(SLD_MQ_Dis == RT_NULL)
//    {
//        rt_kprintf("Dis_Thread MB Recv Data Error\n");
//    }

    /* Initiate first scan */
    Cy_CapSense_ScanAllWidgets(&cy_capsense_context);

    trans_done_semphr = rt_sem_create("slider_sem", 0, RT_IPC_FLAG_PRIO);
    if (trans_done_semphr == RT_NULL)
    {
        rt_kprintf("create transform done semphr failed.\n");
        RT_ASSERT(0);
        return;
    }
}

 void process_touch(void)
{
    cy_stc_capsense_touch_t *slider_touch_info;
    uint16_t slider_pos;
    uint8_t slider_touch_status;
    bool led_update_req = false;

    static uint16_t slider_pos_prev;
//    static led_data_t led_data = {LED_ON, LED_MAX_BRIGHTNESS};

    /* Get slider status */
    slider_touch_info = Cy_CapSense_GetTouchInfo(
                            CY_CAPSENSE_LINEARSLIDER0_WDGT_ID, &cy_capsense_context);
    slider_touch_status = slider_touch_info->numPosition;
    slider_pos = slider_touch_info->ptrPosition->x;

    /* Detect the new touch on slider */
    if ((RT_NULL != slider_touch_status) &&
            (slider_pos != slider_pos_prev))
    {
        if(slider_pos > slider_pos_prev){

            rt_kprintf("cur???");

        }
        if(slider_pos < slider_pos_prev){
            rt_kprintf("cur!!!");
        }
    }
    slider_pos_prev = slider_pos;
}


// void Slider_thread_entry(void *parameter)
//{
//    Slider_Init();
//
//    for (;;)
//    {
//        rt_err_t result;
//        rt_sem_take(trans_done_semphr, RT_WAITING_FOREVER);
//
//        /* Process all widgets */
//        Cy_CapSense_ProcessAllWidgets(&cy_capsense_context);
//
//        /* Process touch input */
//        process_touch();
//        Cy_CapSense_RunTuner(&cy_capsense_context);
//
//        /* Initiate next scan */
//        Cy_CapSense_ScanAllWidgets(&cy_capsense_context);
//
//        rt_thread_mdelay(50);
//    }
//}
//
//int Slider(void)
//{
//    rt_err_t ret = RT_EOK;
//
//    sld_thread = rt_thread_create("slider_th",
//                                  Slider_thread_entry,
//                                  RT_NULL,
//                                  1024,
//                                  25,
//                                  10);
//    if (sld_thread != RT_NULL)
//    {
//        rt_thread_startup(sld_thread);
//    }
//    else
//    {
//        ret = -RT_ERROR;
//    }
//
//    return ret;
//}
