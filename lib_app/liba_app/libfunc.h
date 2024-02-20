/**@file libfunc.h
 * @note 
 * @brief  
 * 
 * @author   luoxi
 * @date     20230107
 * @version  1.0
 * 
 * @note
 * @note History:        
 * @note     <author>   <time>    <version >   <desc>
 * @note  
 * @warning  
 */

#ifndef _LIBFUNC_H_
#define _LIBFUNC_H_

typedef unsigned char  	    u8;	/**< UNSIGNED 8-bit data type */
typedef unsigned short 	    u16;/**< UNSIGNED 16-bit data type */
typedef unsigned int   	   u32;	/**< UNSIGNED 32-bit data type */
typedef unsigned long long u64; /**< UNSIGNED 64-bit data type */
typedef signed char         s8;	/**< SIGNED 8-bit data type */
typedef signed short       s16;	/**< SIGNED 16-bit data type */
typedef signed int         s32;	/**< SIGNED 32-bit data type */
typedef signed long long   s64; /**< SIGNED 64-bit data type */


/** @fn :      Crc16_get
 * @brief :    CRC16校验
 * @param ：   *pbyData : 要校验的数据
 * @param ：   byLen : 校验数据的长度
 * @return :   校验后返回的结果 16位
 */
u16 Crc16_get(u8 *pbyData ,u16 byLen);

/** @fn :      str_len
 * @brief :    求字符串长度
 * @param ：   str : 字符串
 * @param ：   
 * @return :   返回字符串长度
 */
int str_len(char str[]);

/** @fn :      sort_maopao
 * @brief :    冒泡排序
 * @param ：   srt_num : 数组
 * @param ：   len 长度
 * @return :   null
 */
void sort_maopao(char srt_num[],int len);

/** @fn :      sort_xuanze
 * @brief :    选择排序
 * @param ：   srt_num : 数组
 * @param ：   len 长度
 * @return :   null
 */
void sort_xuanze(char srt_num[],int len);

/** @fn :      sort_charu
 * @brief :    插入排序
 * @param ：   srt_num : 数组
 * @param ：   len 长度
 * @return :   null
 */
void sort_charu(char srt_num[],int len);

/** @fn :      recusion_digui
 * @brief :    递归函数
 * @param ：   value : 加数上限
 * @param ：   
 * @return :   累加的和
 */
int recusion_digui(int value);


#endif



