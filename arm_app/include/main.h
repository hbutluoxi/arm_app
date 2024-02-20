/**@file main.h
 * @note 
 * @brief  
 * 
 * @author   luoxi
 * @date    20230106
 * @version  1.0
 * 
 * @note 测试代码
 * @note History:        
 * @note     <author>   <time>    <version >   <desc>
 * @note  
 * @warning  
 */

#ifndef __MAIN_H__
#define __MAIN_H__

#ifndef IMPORT
#define IMPORT	extern
#endif

#ifndef LOCAL
#define LOCAL	static
#endif

#ifndef FOREVER
#define FOREVER for(;;)
#endif

#ifndef ERROR 
#define ERROR	-1
#endif

#ifndef OK
#define OK	0
#endif

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define	FALSE	0
#endif
	
/* types define */

#ifndef TYPE_ERR
#define TYPE_ERR
typedef unsigned int ERR;
#endif

#ifndef TYPE_VOID
#define TYPE_VOID
typedef void VOID;
#endif

#ifndef TYPE_BYTE
#define TYPE_BYTE
typedef unsigned char 	BYTE;
#endif

#ifndef TYPE_UCHAR
#define TYPE_UCHAR
typedef unsigned char	UCHAR;
#endif

#ifndef TYPE_UINT8
#define TYPE_UINT8
typedef unsigned char 	UINT8;
#endif

#ifndef TYPE_UINT16
#define TYPE_UINT16
typedef unsigned short	UINT16;
#endif

#ifndef TYPE_UINT32
#define TYPE_UINT32
typedef unsigned int 	UINT32;
#endif

#ifndef TYPE_UINT64
#define TYPE_UINT64
typedef unsigned long long 	UINT64;
#endif

#ifndef TYPE_INT8
#define TYPE_INT8
typedef char 	INT8;
#endif

#ifndef TYPE_INT16
#define TYPE_INT16
typedef short	INT16;
#endif

#ifndef TYPE_INT32
#define TYPE_INT32
typedef int	INT32;
#endif

#ifndef TYPE_INT64
#define TYPE_INT64
typedef long long 	INT64;
#endif

#ifndef TYPE_INT
#define TYPE_INT
typedef int	INT;
#endif

#ifndef TYPE_UINT
#define TYPE_UINT
typedef unsigned int	UINT;
#endif

#ifndef TYPE_ULONG
#define TYPE_ULONG
typedef unsigned long 	ULONG;
#endif

#ifndef TYPE_PUINT8
#define TYPE_PUINT8
typedef unsigned char*	PUINT8;
#endif

#ifndef TYPE_PUINT
#define TYPE_PUINT
typedef unsigned int*	PUINT;
#endif

#ifndef TYPE_PINT
#define TYPE_PINT
typedef int*	PINT;
#endif

#ifndef TYPE_PVOID
#define TYPE_PVOID
typedef void*	PVOID;
#endif

#ifndef TYPE_USHORT
#define TYPE_USHORT
typedef unsigned short USHORT;
#endif

#ifndef BOOL
#define BOOL int
#endif

#ifndef STATUS
#define STATUS int
#endif

/**********************************************************************************/
/* 为了解决代码中若包含ethtool.h,然后用365工具链编译代码编译出错的问题 */
typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
typedef unsigned long long u64;

/**********************************************************************************/


typedef enum
{
	INIT_FILE_THREAD = 0,
	INIT_CALLBACK,
	RECV_AT_THREAD,
	//SEND_SMS_THREAD,
	//REPORT_MSG_THREAD
}LTE4G_THREAD_NUM;


#define STACK_SIZE 1024*64

#define START_FILE 20

#define PID_FILE "pidfile"

#define F_OK 0


#endif





