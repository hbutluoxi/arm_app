/**@file callback.c
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
#include <log_level.h>
#include <callback.h>



/* 回调函数，生成一个随机数 */
int getsome_value(int a)
{
    if(a > 5)
    {
        a = rand() % 100;//生成一个随机数在0-100之间
        return a;
    }
    else
        return 0;
}
 
//注册回调函数,这里面一个是调用回调函数，一个是返回调用函数后生成的数据，这个才是回调函数在
/*实际应用中会用到的情况，加入这个callback是库中的函数，那么库中可能会需要调用getsome_value()这个方法， 
*也有可能会返回一些数据，比如数据流，视频流等。
*这个函数一般是封在库中的函数，我们在使用时只需要进行传参就可以了
*/
void call_back(int *array, int size, int (*getnext)(int), int value)
{
	int i = 0;

    for(i = 0; i < size; i++)
    {
        array[i] = getnext(value);//调用回调函数并赋值
    }
}
 
 
int fun_callback_test()
{
 int j = 0;
 int arr[ARR_SIZE] = {0};
 
 call_back(arr, ARR_SIZE, getsome_value, 7);//注册回调函数，注册一次，调用一次
 for(j = 0; j < ARR_SIZE; j++)
  {
       LOG_CUSTOM("arr[%d] = %d", j, arr[j]);
  }
 return 0; 
}


