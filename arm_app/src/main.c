/**@file main.c
 * @note 
 * @brief  测试代码
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
 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <log_level.h>
#include <stdbool.h>
#include <fileoperation.h>
#include <main.h>
#include <pthread.h>
#include <moduleA.h>
#include <moduleB.h>
#include <libfunc.h>
#include <libfuncso.h>

#include <sqlite3.h>

pthread_t  tids[3] = {0};

int pthreadSpawn(int pid_num, pthread_attr_t attr_AT, size_t nStacksize, void (*func)(), int priority);
void rand_value(char *buff, int len);

static int check_coreprocess_is_running(void);
static int create_pidfile(void);

/*******************************************************************************
**函数名称：main
**功能描述：应用入口函数
**入口参数：参数个数 参数区分
**输出：无
*******************************************************************************/
int main(int argc, char **argv)
{
    int pid = getpid();
	LOG_CUSTOM("pid is %d", pid);

    int dwret = check_coreprocess_is_running();
    if(dwret)
    {
		LOG_ERROR("have running ...");
	}
	else
	{
     dwret = create_pidfile();
	 if(OK != dwret)
	 {
   		LOG_ERROR("create file failed ...");
	 }

	}

    /*起一个新的进程*/
    if((pid = vfork()) < 0) 
    {
      	LOG_ERROR("Can not fork, exit now");
    }
      
    if( pid == 0)
    {
		LOG_CUSTOM("vfork is success");
		exit(0);

    }

    pid = getpid();
	LOG_CUSTOM("pid is %d", pid);


	/*递归函数*/
	int sum = recusion_digui(100);
	LOG_CUSTOM("1-100 = %d", sum);

   /*回调函数测试 这种是比较复杂的使用方法*/
	ptrFunction myfu;
	myfu = rand_value;
	Register_module(myfu);
	my_function(); 

	/*排序算法*/
    char len1[10] = {5, 2, 21, 23, 98, 12, 30, 35, 20, 10};
	//sort_maopao(len1, 10);
	//sort_xuanze(len1, 10);
	sort_charu(len1, 10);

	/*计算字符串长度*/
	char str1[] = "helloworld";
	int len = str_len(str1);
    LOG_CUSTOM("len = %d", len);


	/*CRC校验*/
	u16 result = 0x0;
	u8 buff[10] = {0x01, 0x21, 0x31, 0x41, 0x51, 0x61, 0x71, 0x81, 0x1, 0x01};
	result = Crc16_get(buff, 10);
	LOG_CUSTOM("result = %x", result);


	sqlite3 *db = NULL;
    int resultdb;
    result = sqlite3_open("./test.db", &db);
    if(result != SQLITE_OK)
    {
        LOG_CUSTOM("Create/Open test.db error!");
        return -1;
    }
    LOG_CUSTOM("Create/Open test.db success!");


	int ret = -1;
	pthread_attr_t attr_call;
	if((ret = pthreadSpawn(INIT_CALLBACK, attr_call, STACK_SIZE*2, (void *)test_callback, START_FILE)) != OK)
	{
	   LOG_ERROR("<main>: pthread_create read_file err, ret = %d", ret);
	}

	read_file();

	FOREVER
	{
	  usleep(100*1000);
	}

	return OK;
}

/*******************************************************************************
**函数名称：pthreadSpawn
**功能描述：创建线程函数
**入口参数：int pid_num 线程pid号 
**入口参数：pthread_attr_t attr_AT 线程创建资源
**入口参数：size_t nStacksize 线程堆栈大小
**入口参数：void (*func)() 线程执行函数
**入口参数：int priority 线程优先级
**输出：0 创建成功         -1 创建失败
*******************************************************************************/
int pthreadSpawn(int pid_num, pthread_attr_t attr_AT, size_t nStacksize, void (*func)(),  int priority)
{
	int ret = -1;
	struct sched_param    params;

	if(NULL == func)
	{
	  LOG_ERROR("ARGS IS ERROR");
      return ERROR;
	}

	/* 启动线程 */
	//pthread_t MSG;
	//pthread_attr_t attr_AT;
	
	ret = pthread_attr_init(&attr_AT);  //初始化线程
	if (ret != OK)
	{
	    LOG_ERROR("pthread_attr_init err, ret = %d", ret);
		pthread_attr_destroy(&attr_AT);
		return ret;
	}

	ret = pthread_attr_setschedpolicy(&attr_AT, SCHED_RR);//设置线程调度策略 SCHED_OTHER SCHED_FIFO SCHED_RR
	if (ret != OK)
	{
	    LOG_ERROR("pthread_attr_setschedpolicy err, ret = %d", ret);
		pthread_attr_destroy(&attr_AT);
		return ret;
	}
	
	ret = pthread_attr_setdetachstate (&attr_AT, PTHREAD_CREATE_DETACHED);	//设置线程分离属性，防止内存泄露
	if (ret != OK)
	{
	    LOG_ERROR("pthread_attr_setdetachstate err, ret = %d", ret);
		pthread_attr_destroy(&attr_AT);
		return ret;
	}

	ret = pthread_attr_getschedparam(&attr_AT, &params);  //得到线程优先级参数等
	if (ret != OK)
	{
	    LOG_ERROR("pthread_attr_getschedparam err, ret = %d", ret);
		pthread_attr_destroy(&attr_AT);
		return ret;
	}
	
	params.sched_priority = priority;

	ret = pthread_attr_setschedparam(&attr_AT, &params);  //设置线程优先级参数
	if (ret != OK)
	{
	    LOG_ERROR("pthread_attr_setschedparam err, ret = %d", ret);
		pthread_attr_destroy(&attr_AT);
		return ret;
	}
	
	ret = pthread_attr_setstacksize(&attr_AT, nStacksize);  //设置线程堆栈大小
	if (ret != OK)
	{
	    LOG_ERROR("pthread_attr_setstacksize err, ret = %d", ret);
		pthread_attr_destroy(&attr_AT);
		return ret;
	}	

	if ((ret = pthread_create(&tids[pid_num], &attr_AT,(void *)func, NULL)) != OK)  //创建线程
	{
		LOG_ERROR("pthread_create err, ret = %d", ret);
	}
	else
	{
		LOG_CUSTOM("create thread is succ!");

	}
    return ret;

}


/*******************************************************************************
**函数名称：rand_value
**功能描述：生成 1 - 100之间的随机数
**入口参数：char *buff 数据保存区 
**入口参数：int len 数据长度
**输出：无
*******************************************************************************/
void rand_value(char *buff, int len)
{
	int i = 0;
	for(i = 0; i < len - 1; i++)
	{
		*buff = rand() % 100;
		buff++;
	}
}

/*******************************************************************************
**函数名称：check_coreprocess_is_running
**功能描述：检查是否有同名线程在运行
**入口参数：无
**输出：0 没有       1 有
*******************************************************************************/
static int check_coreprocess_is_running(void)
{
	int ret =0;
	ret = access(PID_FILE, F_OK);
	if(0 == ret)
	{
		LOG_CUSTOM("have one process running");
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*******************************************************************************
**函数名称：create_pidfile
**功能描述：创建一个进程文件
**入口参数：无
**输出：-1 创建失败         0 创建成功
*******************************************************************************/
static int create_pidfile(void)
{
    int fd = 0;
    fd = open(PID_FILE, O_RDWR | O_CREAT | O_EXCL, 0);
    if (fd < 0)
    {
        LOG_ERROR("file %s create failed", PID_FILE);
        return ERROR;
    }
    else
    {
        close(fd);
        return OK;
    }
}
