/**@file moduleA.h
 * @note 
 * @brief  
 * 
 * @author   luoxi
 * @date    20230106
 * @version  1.0
 * 
 * @note 
 * @note History:        
 * @note     <author>   <time>    <version >   <desc>
 * @note  
 * @warning  
 */

#ifndef _MODULEA_
#define _MODULEA_

typedef int (*ptrFunc)(int a);

typedef struct device
{
	int index;
	ptrFunc function;
}device_st;


int Register_callback(device_st *registed_fun);

int my_test(int b);

void test_callback(void);


#endif



