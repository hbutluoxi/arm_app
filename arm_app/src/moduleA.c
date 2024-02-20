/**@file moduleA.c
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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <log_level.h>
#include <stdbool.h>
#include <moduleA.h>
#include <main.h>


// 我们调用其他模块的函数，并把回调函数传给其他模块，其他模块中的函数调用我们写的回调函数

//回调函数 函数功能
int func_value(int a)
{
	if(a>5)
	{
		a = rand() % 100;//生成一个随机数在0-100之间
		return a;
	}
	else
		return 0;
}



void test_callback()
{
	device_st pt_func;
	pt_func.index = 1;
	pt_func.function = func_value;

	/* 注册回调函数 注册回调函数的过程可以理解为让函数指针指向哪一个回调函数，同类型的函数都可以在这里注册 */
	/* 回调函数允许用户将一个方法的指针传到另外一个函数，以便该函数在处理类似事件时可以调用不同的函数 */
	if(0 != Register_callback(&pt_func))
	{
		LOG_ERROR("Registe_callback error");
		return;
	}

	int ret = 20;
	int value = 0;
	LOG_CUSTOM("please put num .....");

	FOREVER
	{
		scanf("%d", &value);
		//通过直接赋值调用也可以，但是就不能体现回调的优点了
		//ret =pt_func.function(value);
		//LOG_CUSTOM("ret = %d",ret);

	    //回调使用，调用后返回一个数
		ret = my_test(value);
		LOG_CUSTOM("ret = %d", ret);

		usleep(100*1000);

	}

}



