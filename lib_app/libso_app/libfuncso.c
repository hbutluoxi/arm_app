/**@file libfuncso.c
 * @note 
 * @brief  测试代码
 * 
 * @author   luoxi
 * @date     20230107
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
#include <string.h>
#include <libfuncso.h>

ptrFunction testmy;


int Register_module(ptrFunction fun)
{
	testmy =fun;
	return 0;
}


void my_function()
{
	char buff1[10];
	testmy(buff1,10);

    int i=0;
	printf("buff1 ");
	for(i=0;i<9;i++)
	{
		printf("%d ",buff1[i]);
	}
	printf("\n");
}


