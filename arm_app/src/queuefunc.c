/**@file queue_func.c
 * @note 
 * @brief  测试代码          队列实现
 * 
 * @author   luoxi
 * @date     20230106
 * @version  V1.0.0
 * 
 * @note ///Description here 
 * @note History:        
 * @note     <author>   <time>    <version >   <desc>
 * @note  
 * @warning  
 */


#include "queue_func.h"


DataQueue *by485DataQueue=NULL;


/*********************************************************************************************************
** 函数名称: QueueCreate
** 功能描述: 初始化数据队列
** 输　入: QueueAddr      ：为队列分配的存储空间地址
**         SizeOfBuf：为队列分配的存储空间大小（字节）
**         ReadEmpty：为队列读空时处理程序
**         WriteFull：为队列写满时处理程序
** 输　出: QUEUE_FAIL  :参数错误
**         QUEUE_OK:成功
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/

int QueueCreate(void * QueueAddr,
               uint32_t SizeOfBuf,
               uint32_t BlockSize,
               uint8_t (* ReadEmpty)(),
               uint8_t (* WriteFull)()
              )
{
    DataQueue *Queue;
    
    if (QueueAddr != NULL && SizeOfBuf >= (sizeof(DataQueue)))        					/* 判断参数是否有效 */
    {
        Queue = (DataQueue *)QueueAddr;
        Queue->DataBuf=(QUEUE_DATA_TYPE *)malloc(SizeOfBuf*sizeof(QUEUE_DATA_TYPE));  	//给队列数据空间分配内存   
			  if(Queue->DataBuf ==NULL)
					return QUEUE_FAIL;
				memset(Queue->DataBuf,0,SizeOfBuf*sizeof(QUEUE_DATA_TYPE));		
        Queue->BlockSize=BlockSize;
        Queue->MaxBlock = SizeOfBuf/BlockSize;    					   													/* 计算队列可以存储的数据数块数目 */
        Queue->End =Queue->DataBuf + Queue->MaxBlock*Queue->BlockSize;           				/* 计算数据缓冲的结束地址 */
        Queue->Out =Queue->DataBuf;
        Queue->In = Queue->DataBuf;
        Queue->NBlock = 0;
        Queue->ReadEmpty = ReadEmpty;
        Queue->WriteFull = WriteFull;
        return QUEUE_OK;
    }
    else
    {
        return QUEUE_FAIL;
    }
}


/*********************************************************************************************************
** 函数名称: QueueWrite
** 功能描述: FIFO方式写数据
** 输　入: QueueAddr :指向队列的指针
**         Data:发送的数据
** 输　出: QUEUE_FAIL   ：参数错误
**         QUEUE_FULL:队列满
**         QUEUE_OK  :发送成功
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/

#if EN_QUEUE_WRITE > 0

int QueueWrite(void *QueueAddr, QUEUE_DATA_TYPE *pDataIn)
{
    int Ret;
    DataQueue *Queue;

    Ret = QUEUE_FAIL;
    if ((QueueAddr != NULL)&&(pDataIn!=NULL))								/* 队列是否有效 */
    {
        Queue = (DataQueue *)QueueAddr;
       
        
        if (Queue->NBlock < Queue->MaxBlock)                            /* 队列是否满  */
        {    
			memcpy(Queue->In,pDataIn,Queue->BlockSize);                	/* 数据入队    */
            Queue->In+=Queue->BlockSize;                       					/* 调整入队指针*/
            if (Queue->In >= Queue->End)
            {
                Queue->In = Queue->DataBuf;                             //入队列的指针调整到开头
            }
            Queue->NBlock++;                                             /* 数据增加    */
            Ret = QUEUE_OK;
        }
        else
        {                                                               /* 满           */
            Ret = QUEUE_FULL;
            if (Queue->WriteFull != NULL)                               /* 调用用户处理函数 */
            {
                Ret = Queue->WriteFull(Queue, pDataIn, Q_WRITE_MODE);
            }
        }
        
        
    }
    return Ret;
}
#endif


/*********************************************************************************************************
** 函数名称: QueueRead
** 功能描述: 获取队列中的数据，先进先出
** 输　入: pAddress:存储返回的消息的地址
**         QueueAddr:指向队列的指针
** 输　出: QUEUE_FAIL     ：参数错误
**         QUEUE_OK   ：收到消息
**         QUEUE_EMPTY：队列空
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/
#if EN_QUEUE_READ>0

int QueueRead(void *QueueAddr,QUEUE_DATA_TYPE *pDataOut)
{
    int Ret;
    DataQueue *Queue;

    Ret = QUEUE_FAIL;
    if ((QueueAddr != NULL)&&(pDataOut!=NULL))                  /* 队列是否有效 */
    {                                                           /* 有效 */
        Queue = (DataQueue *)QueueAddr;
        
        
        if (Queue->NBlock > 0)                                   /* 队列是否为空 */
        {                                                       /* 不空         */
						memcpy(pDataOut,Queue->Out,Queue->BlockSize); 			/* 数据出队     */  							
            Queue->Out+=Queue->BlockSize;            						/* 调整出队指针 */
            if (Queue->Out >= Queue->End)
            {
                Queue->Out = Queue->DataBuf;									//调整出队指针到开头
            }
            Queue->NBlock--;                                     /* 数据减少      */
            Ret = QUEUE_OK;
        }
        else
        {                                                       /* 空              */
            Ret = QUEUE_EMPTY;
            if (Queue->ReadEmpty != NULL)                       /* 调用用户处理函数 */
            {
                Ret = Queue->ReadEmpty(pDataOut, Queue);
            }
        }
        
        
    }
    return Ret;
}

#endif

/*********************************************************************************************************
** 函数名称: QueueWriteFront
** 功能描述: LIFO方式发送数据
** 输　入: QueueAddr:指向队列的指针
**         Data:消息数据
** 输　出: QUEUE_FULL:队列满
**         QUEUE_OK:发送成功
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/

#if EN_QUEUE_WRITE_FRONT > 0

int QueueWriteFront(void *QueueAddr, QUEUE_DATA_TYPE *pDataIn)
{
    int Ret;
    DataQueue *Queue;

    Ret = QUEUE_FAIL;
    if (QueueAddr != NULL)                                                    /* 队列是否有效 */
    {
        Queue = (DataQueue *)QueueAddr;
        
        if (Queue->NBlock < Queue->MaxBlock)                              /* 队列是否满  */
        {                                                               /* 不满 */
            Queue->Out-=Queue->BlockSize;                               /* 调整出队指针 */
            if (Queue->Out < Queue->DataBuf)
            {
                Queue->Out = Queue->End - 1;
            }
			memcpy(Queue->Out,pDataIn,Queue->BlockSize);                   /* 数据入队     */
            Queue->NBlock++;                                             /* 数据数目增加 */
            Ret = QUEUE_OK;
        }
        else
        {                                                               /* 满           */
            Ret = QUEUE_FULL;
            if (Queue->WriteFull != NULL)                               /* 调用用户处理函数 */
            {
                Ret = Queue->WriteFull(Queue, pDataIn, Q_WRITE_FRONT_MODE);
            }
        }
    }
    return Ret;
}

#endif


/*********************************************************************************************************
** 函数名称: QueueNData
** 功能描述: 取得队列中数据数
** 输　入: QueueAddr:指向队列的指针
** 输　出: 消息数
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/

#if EN_QUEUE_NDATA > 0

int QueueNData(void *QueueAddr)
{
    int temp;
    DataQueue *Queue;
    temp = 0;     /* 队列无效返回0 */
    if (QueueAddr != NULL)
    { 
    	Queue = (DataQueue *)QueueAddr;
        temp = Queue->NBlock;
    }
   
    
    return temp;
}

#endif

/*********************************************************************************************************
** 函数名称: QueueSize
** 功能描述: 取得队列总容量
** 输　入: QueueAddr:指向队列的指针
** 输　出: 队列总容量
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/

#if EN_QUEUE_SIZE > 0

int QueueSize(void *QueueAddr)
{
    int temp;
    DataQueue *Queue;
    temp = 0; /* 队列无效返回0 */	
    if (QueueAddr != NULL)
    {
    	Queue = (DataQueue *)QueueAddr;
        temp = Queue->MaxBlock;
    }
    return temp;
}

#endif


/*********************************************************************************************************
** 函数名称: OSQFlush
** 功能描述: 清空队列
** 输　入: QueueAddr:指向队列的指针
** 输　出: 无
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/

#if EN_QUEUE_FLUSH > 0

void QueueFlush(void *QueueAddr)
{
    DataQueue *Queue;
    
    if (QueueAddr != NULL) /* 队列是否有效 */
    {                 /* 有效         */
        Queue = (DataQueue *)QueueAddr;
				memset(Queue->DataBuf,0,Queue->MaxBlock*Queue->BlockSize);
        Queue->Out = Queue->DataBuf;
        Queue->In = Queue->DataBuf;
        Queue->NBlock = 0;  /* 数据数目为0 */
    }
}
#endif


/*********************************************************************************************************
** 函数名称: QueueDestroy
** 功能描述: 销毁队列
** 输　入: QueueAddr:指向队列的指针
** 输　出: 无
** 全局变量: 无
** 调用模块: OS_ENTER_CRITICAL,OS_EXIT_CRITICAL
********************************************************************************************************/

#if EN_QUEUE_DESTROY > 0
#define DATA_485_BLOCK 					(300)

void QueueDestroy(void *QueueAddr)
{
    DataQueue *Queue;
    /* 先将队列中数据清空 */
    if (QueueAddr != NULL) /* 队列是否有效 */
    {      
        Queue = (DataQueue *)QueueAddr; 
		Queue->Out = NULL;
        Queue->In =NULL;
        Queue->NBlock = 0; 
		Queue->BlockSize = 0; 
		Queue->MaxBlock = 0;
		
		memset(Queue->DataBuf,0,Queue->MaxBlock*Queue->BlockSize);
		free(Queue->DataBuf);   //释放内存
		Queue->DataBuf=NULL;
    }
	/*再将队列本身的结构释放*/
	memset(QueueAddr,0,sizeof(DataQueue));
	free(QueueAddr);
	QueueAddr=NULL;
}
#endif




void QUEUE_TEST(void)
{
	if(QUEUE_OK!=QueueCreate(by485DataQueue,2048,DATA_485_BLOCK,NULL,NULL))//创建一个队列用于485数据接收和处理
	{
			printf("QueueCreate fail!!\r\n");
	}
	else
	{		
			QueueFlush(by485DataQueue); //清空队列
			printf("QUEUE_DEBUG: nblock:%d	blocksize:%d \r\n",by485DataQueue->NBlock,by485DataQueue->BlockSize);
	}
}




