///*
// * Copyright (c) 2006-2021, RT-Thread Development Team
// *
// * SPDX-License-Identifier: Apache-2.0
// *
// * Change Logs:
// * Date           Author       Notes
// * 2025-07-01     lenovo       the first version
// */
//
///*定义线程控制块*/
//static rt_thread_t receive_thread = RT_NULL;
//static rt_thread_t send_thread = RT_NULL;
//
///*消息队列控制块*/
//static rt_mq_t test_mq = RT_NULL;
//
///*函数声明*/
//static receive_thread_entry(void);
//static key1_thread_entry(void);
//static key2_thread_entry(void);
//
////main
//int main(void)
//{
//    /*
//* 开发板硬件初始化，RTT系统初始化已经在main函数之前完成，
//* 即在component.c文件中的rtthread_startup()函数中完成了。
//* 所以在main函数中，只需要创建线程和启动线程即可。
//*/
//rt_kprintf("这是一个[野火]-STM32F103-指南者-RTT消息队列实验！");
//  rt_kprintf("按下K1或者K2发送队列消息");
//  rt_kprintf("receive任务接收到消息在串口回显");
//
//  /* 创建一个消息队列 */
// test_mq = rt_mq_create("test_mq",/* 消息队列名字 */
//                      4,     /* 消息的最大长度 */
//                      10,    /* 消息队列的最大容量 */
//                      RT_IPC_FLAG_FIFO);/* 队列模式 FIFO(0x00)*/
//   if (test_mq != RT_NULL)
//     rt_kprintf("消息队列创建成功！");
// receive_thread =                          /* 线程控制块指针 */
//         rt_thread_create( "receive",              /* 线程名字 */
//                       receive_thread_entry,   /* 线程入口函数 */
//                       RT_NULL,             /* 线程入口函数参数 */
//                       512,                 /* 线程栈大小 */
//                       3,                   /* 线程的优先级 */
//                       20);                 /* 线程时间片 */
// /* 启动线程，开启调度 */
//    if (receive_thread != RT_NULL)
//         rt_thread_startup(receive_thread);
//     else
//         return -1;
//   send_thread =                          /* 线程控制块指针 */
//     rt_thread_create( "key1send",              /* 线程名字 */
//                       key1_send_thread_entry,   /* 线程入口函数 */
//                       RT_NULL,             /* 线程入口函数参数 */
//                       512,                 /* 线程栈大小 */
//                       2,                   /* 线程的优先级 */
//                       20);                 /* 线程时间片 */
//     /* 启动线程，开启调度 */
//    if (send_thread != RT_NULL)
//         rt_thread_startup(send_thread);
//     else
//         return -1;
//    send_thread =                          /* 线程控制块指针 */
//       rt_thread_create( "key2send",              /* 线程名字 */
//                         key2_send_thread_entry,   /* 线程入口函数 */
//                         RT_NULL,             /* 线程入口函数参数 */
//                         512,                 /* 线程栈大小 */
//                         2,                   /* 线程的优先级 */
//                         20);                 /* 线程时间片 */
//       /* 启动线程，开启调度 */
//      if (send_thread != RT_NULL)
//           rt_thread_startup(send_thread);
//       else
//           return -1;
//   }
///*************************************************************************
//*                             线程定义
//*************************************************************************
//*/
//static void receive_thread_entry(void* parameter)
//{
//  rt_err_t uwRet = RT_EOK;
//  uint32_t r_queue;
//  /* 任务都是一个无限循环，不能返回 */
//  while (1)
//  {
//    /* 队列读取（接收），等待时间为一直等待 */
//uwRet = rt_mq_recv(test_mq, /* 读取（接收）队列的ID(句柄) */
//&r_queue, /* 读取（接收）的数据保存位置 */
//sizeof(r_queue), /* 读取（接收）的数据的长度 */
//RT_WAITING_FOREVER); /* 等待时间：一直等 */
//if(RT_EOK == uwRet)
//{
//rt_kprintf("本次接收到的数据是：%x",r_queue);
//}
//else
//{
//rt_kprintf("数据接收出错,错误代码: 0x%lx",uwRet);
//}
//    rt_thread_delay(100);
//  }
//}
//static void key1_send_thread_entry(void* parameter)
//{
//  rt_err_t uwRet = RT_EOK;
//uint32_t send_data1 = 0x1111;
//while (1)
//{
//if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON )/* K1 被按下 */
//{
///* 将数据写入（发送）到队列中，等待时间为 0  */
//uwRet = rt_mq_send( test_mq, /* 写入（发送）队列的ID(句柄) */
//&send_data1, /* 写入（发送）的数据 */
//sizeof(send_data1)); /* 数据的长度 */
//if(RT_EOK != uwRet)
//{
//rt_kprintf("KEY1 数据不能发送到消息队列！错误代码: %lx",uwRet);
//}
//}
//rt_thread_delay(20);
//}
//}
//static void key2_send_thread_entry(void* parameter)
//{
//  rt_err_t uwRet = RT_EOK;
//  uint32_t send_data2 = 0x2222;
//          while (1)
//          {
//          if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON )/* K1 被按下 */
//          {
//          for(int i=0;i<22;i++)
//          {
//          /* 将数据写入（发送）到队列中，等待时间为 0  */
//          uwRet = rt_mq_send(test_mq, /* 写入（发送）队列的ID(句柄) */
//          &send_data2, /* 写入（发送）的数据 */
//          sizeof(send_data2)); /* 数据的长度 */
//          if(RT_EOK != uwRet)
//          {
//          rt_kprintf("KEY2 数据不能发送到消息队列！错误代码: %lx ",uwRet);
//          }
//          rt_thread_delay(50);
//          }
//          }
//          rt_thread_delay(20);
//          }
//          }

