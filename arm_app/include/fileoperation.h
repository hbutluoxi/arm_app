/**@file fileoperation.h
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

#ifndef _FILE_OPERATION_H_
#define _FILE_OPERATION_H_ 

#define FILE_PATH "stu_list.txt"

void read_file(void);

enum str_type
{
	NAME =0,
	SEX,
	AGE,
	TEL,
	ID,
};

#endif




