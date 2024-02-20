/**@file queue_func.h
 * @note 
 * @brief  
 * 
 * @author   luoxi
 * @date    20221014
 * @version  1.0
 * 
 * @note 
 * @note History:        
 * @note     <author>   <time>    <version >   <desc>
 * @note  
 * @warning  
 */

#ifndef _QUEUE_FUNC_H_
#define _QUEUE_FUNC_H_




#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>	

#include <libfunc.h>


/************************数据定义********************************/
#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef QUEUE_DATA_TYPE

#define QUEUE_DATA_TYPE     u8
#endif

//队列操作返回值
#define QUEUE_OK    		(0)					// 操作成功
#define QUEUE_FAIL  		(-1)				//操作失败


//队列状态管理
typedef enum{	
	QUEUE_EMPTY=1,					// 无数据 
	QUEUE_FULL=2, 					// 队列满 
	Q_WRITE_MODE=3,					// FIFO模式成功
	Q_WRITE_FRONT_MODE=4			// LIFO模式成功
}QUEUE_STUTAS;                       

//队列结构
typedef struct {
    QUEUE_DATA_TYPE     *Out;                // 指向数据输出位置
    QUEUE_DATA_TYPE     *In;                 // 指向数据输入位置         
    QUEUE_DATA_TYPE     *End;                // 指向数据的结束位置
    u16           	    NBlock;            	 // 队列中数据块个数 
    u16                 MaxBlock;          	 // 队列中允许存储的数据块个数
    u16					BlockSize;			 // 队列的块大小
    u8             (* ReadEmpty)();   	 // 读空处理函数
    u8             (* WriteFull)();   	 // 写满处理函数    
    QUEUE_DATA_TYPE     *DataBuf;            // 存储数据的空间
    
} DataQueue;

/*******************************************************************
							功能统一管理宏
********************************************************************/

#ifndef EN_QUEUE_READ
#define EN_QUEUE_READ    		 	(1)
#endif

#ifndef EN_QUEUE_WRITE
#define EN_QUEUE_WRITE     		 	(1)
#endif

#ifndef EN_QUEUE_WRITE_FRONT
#define EN_QUEUE_WRITE_FRONT    	(0)
#endif

#ifndef EN_QUEUE_NDATA
#define EN_QUEUE_NDATA   		 	(1)
#endif

#ifndef EN_QUEUE_SIZE
#define EN_QUEUE_SIZE    			(1)
#endif

#ifndef EN_QUEUE_FLUSH
#define EN_QUEUE_FLUSH    			(1)
#endif

#ifndef EN_QUEUE_DESTROY 
#define EN_QUEUE_DESTROY    		(1)
#endif

extern DataQueue *by485DataQueue;
/*******************************************************************
							外部接口
********************************************************************/

/*********************************************************************************************************
** 函数名称: QueueCreate
** 功能描述: 初始化数据队列
** 输　入: Buf      ：为队列分配的存储空间地址
**         SizeOfBuf：为队列分配的存储空间大小（字节）
**         ReadEmpty：为队列读空时处理程序
**         WriteFull：为队列写满时处理程序
** 输　出: NOT_OK  :参数错误
**         QUEUE_OK:成功
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/
extern int QueueCreate(void * QueueAddr,
               u32 SizeOfBuf,
               u32 BlockSize,
               u8 (* ReadEmpty)(),
               u8 (* WriteFull)()
              );

/*********************************************************************************************************
** 函数名称: QueueRead
** 功能描述: 获取队列中的数据
** 输　入: Ret:存储返回的消息的地址
**         Buf:指向队列的指针
** 输　出: NOT_OK     ：参数错误
**         QUEUE_OK   ：收到消息
**         QUEUE_EMPTY：队列空
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/
extern int QueueRead(void *QueueAddr,QUEUE_DATA_TYPE *pDataOut);


/*********************************************************************************************************
** 函数名称: QueueWrite
** 功能描述: FIFO方式发送数据
** 输　入: Buf :指向队列的指针
**         Data:发送的数据
** 输　出: NOT_OK   ：参数错误
**         QUEUE_FULL:队列满
**         QUEUE_OK  :发送成功
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/
extern int QueueWrite(void *QueueAddr, QUEUE_DATA_TYPE *pDataIn);




/*********************************************************************************************************
** 函数名称: QueueWriteFront
** 功能描述: LIFO方式发送数据
** 输　入: Buf:指向队列的指针
**         Data:消息数据
** 输　出: QUEUE_FULL:队列满
**         QUEUE_OK:发送成功
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/
extern int QueueWriteFront(void *QueueAddr, QUEUE_DATA_TYPE *pDataIn);


/*********************************************************************************************************
** 函数名称: QueueNData
** 功能描述: 取得队列中数据数
** 输　入: Buf:指向队列的指针
** 输　出: 消息数
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/
extern int QueueNData(void *QueueAddr);


/*********************************************************************************************************
** 函数名称: QueueSize
** 功能描述: 取得队列总容量
** 输　入: Buf:指向队列的指针
** 输　出: 队列总容量
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/
extern int QueueSize(void *QueueAddr);


/*********************************************************************************************************
** 函数名称: OSQFlush
** 功能描述: 清空队列
** 输　入: Buf:指向队列的指针
** 输　出: 无
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/
extern void QueueFlush(void *QueueAddr);


/*********************************************************************************************************
** 函数名称: QueueDestroy
** 功能描述: 销毁队列
** 输　入: QueueAddr:指向队列的指针
** 输　出: 无
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/
extern void QueueDestroy(void *QueueAddr);

#endif /* _SYSTICK_H */

/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/


