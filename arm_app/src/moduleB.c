/**@file moduleB.c
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

ptrFunc set_valve;


int Register_callback(device_st *registed_fun)
{
	if(1 != registed_fun->index)
	{
     LOG_CUSTOM("Register_callback error");
	 return -1;
	}
	set_valve = registed_fun->function;
	return 0;
}

int my_test(int b)
{
	return 	set_valve(b);
}


