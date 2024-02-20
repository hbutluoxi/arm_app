/**@file queue.c
 * @note 
 * @brief  测试代码                 简单环形队列实现
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

int MAXSUM = 6;//确定环形队列的最大长度
int Data[6] = {0};//环形队列存储数据的地方
int top = 0, rear = 0;//输入和输出的位置
void Rec_data(int data)
{
	Data[top] = data;
	top = (top + 1) % MAXSUM;//循环队列保存值
}
 
int Send_data()
{
	int value =0;
	value = rear;
	rear = (rear + 1) % MAXSUM;//循环出队列
	return (Data[value]);
}
 
 
int test2()
{
	int key_value = 0;
	Rec_data(1);
	LOG_CUSTOM("data[0] = %d]", Data[0]);
	Rec_data(2);
	LOG_CUSTOM("data[1] = %d]", Data[1]); 
	Rec_data(3);
	LOG_CUSTOM("data[2] = %d]", Data[2]);
	Rec_data(4);
	LOG_CUSTOM("data[3] = %d]", Data[3]);
	Rec_data(5);
	LOG_CUSTOM("data[4] = %d]", Data[4]);
	Rec_data(6);
	LOG_CUSTOM("data[5] = %d]", Data[5]);
	Rec_data(7);
	LOG_CUSTOM("data[0] = %d]", Data[0]);
	Rec_data(8);
	LOG_CUSTOM("data[1] = %d]", Data[1]);
	LOG_CUSTOM("data[2] = %d]", Data[2]);
	LOG_CUSTOM("data[3] = %d]", Data[3]);
	 
	key_value = Send_data();
	LOG_CUSTOM("key1 = %d]", key_value);
	key_value = Send_data();
	LOG_CUSTOM("key2 = %d]", key_value);
	key_value = Send_data();
	LOG_CUSTOM("key3 = %d]", key_value);
	key_value = Send_data();
	LOG_CUSTOM("key4 = %d]", key_value);
	 
	return 0;
}




