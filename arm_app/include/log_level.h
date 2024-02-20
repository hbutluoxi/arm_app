/**@file log_level.h
 * @note 
 * @brief  
 * 
 * @author   luoxi
 * @date    20230106
 * @version  1.0
 * 
 * @note 设置日志打印等级
 * @note History:        
 * @note     <author>   <time>    <version >   <desc>
 * @note  
 * @warning  
 */
#ifndef _LOG_LEVEL_H_
#define _LOG_LEVEL_H_ 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h> 
#include <fcntl.h>
#include <stdlib.h>    
#include <stdarg.h>
#include <time.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdio.h>





#define __LOG_CN__ 1
#if __LOG_CN__

#define COLOR_END                       "\033[0m"
#define INFO_COLOR                      "\033[36m"
#define DEBUG_COLOR                     "\033[35m"
#define DEBUG_ARRAY_COLOR               "\033[35m"
#define WARNING_COLOR                   "\033[33m"
#define ERROR_COLOR                     "\033[31m"

#define LOG_LEVEL 1


typedef enum
{
    //用户可自定义打印格式
    LOG_LEVEL_CUSTOM = 0,
    //打印错误
    LOG_LEVEL_ERROR,
    //打印警告
    LOG_LEVEL_WARNING,
    //打印调试信息
    LOG_LEVEL_DEBUG,
    //打印数组信息
    LOG_LEVEL_DEBUG_ARRAY,
    //打印信息
    LOG_LEVEL_INFO,
}log_level_enum_t;

#define LOG_INFO(format,...)            do{\
                                            if (LOG_LEVEL >= LOG_LEVEL_INFO)\
                                            {\
                                                printf(INFO_COLOR"[INFO]:[FUNC]:%s, [LINE]:%04d:"format"\r\n"COLOR_END, __func__, __LINE__, ##__VA_ARGS__);\
                                            }\
                                        }while(0)

#define LOG_DEBUG(format,...)           do{\
                                            if (LOG_LEVEL >= LOG_LEVEL_DEBUG)\
                                            {\
                                                printf(DEBUG_COLOR"[DEBUG]:[FUNC]:%s, [LINE]:%04d:"format"\r\n"COLOR_END, __func__, __LINE__, ##__VA_ARGS__);\
                                            }\
                                        }while(0)

#define LOG_DEBUG_ARRAY(array, num)     do{\
                                            if (LOG_LEVEL >= LOG_LEVEL_DEBUG_ARRAY)\
                                            {\
                                                uint32_t i;\
                                                uint8_t *a = array;\
                                                printf(DEBUG_ARRAY_COLOR"[DEBUG_ARRAY]:[FUNC]:%s, [LINE]:%04d:\r\n"COLOR_END, __func__, __LINE__);\
                                                for (i = 0; i < num; i++)\
                                                {\
                                                    printf("%#X   ", a[i]);\
                                                    if ((i + 1 ) % 10 == 0)\
                                                    {\
                                                        printf("\r\n");\
                                                    }\
                                                }\
                                                printf("\r\n");\
                                            }\
                                        }while(0)

#define LOG_WARNING(format,...)           do{\
                                            if (LOG_LEVEL >= LOG_LEVEL_WARNING)\
                                            {\
                                                printf(WARNING_COLOR"[WARNING]:[FUNC]:%s, [LINE]:%04d:"format"\r\n"COLOR_END, __func__, __LINE__, ##__VA_ARGS__);\
                                            }\
                                        }while(0)

#define LOG_ERROR(format,...)           do{\
                                            if (LOG_LEVEL >= LOG_LEVEL_ERROR)\
                                            {\
                                                printf(ERROR_COLOR"[ERROR]:[FUNC]:%s, [LINE]:%04d:"format"\r\n"COLOR_END, __func__, __LINE__, ##__VA_ARGS__);\
                                            }\
                                        }while(0)

#define LOG_CUSTOM(format,...)          do{\
                                            if (LOG_LEVEL >= LOG_LEVEL_CUSTOM)\
                                            {\
                                                printf(format"\r\n", ##__VA_ARGS__);\
                                            }\
                                        }while(0)

#else

#define LOG_INFO(format,...)            do { } while (0)
#define LOG_DEBUG(format,...)           do { } while (0)
#define LOG_DEBUG_ARRAY(array, num)     do { } while (0)
#define LOG_WARNING(format,...)         do { } while (0)
#define LOG_ERROR(format,...)           do { } while (0)
#define LOG_CUSTOM(format,...)          do { } while (0)

#endif



#endif



