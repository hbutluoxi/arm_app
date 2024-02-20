/**@file libfuncso.h
 * @note 
 * @brief  
 * 
 * @author   luoxi
 * @date    20230701
 * @version  1.0
 * 
 * @note
 * @note History:        
 * @note     <author>   <time>    <version >   <desc>
 * @note  
 * @warning  
 */

#ifndef _LIBFUNCSO_H_
#define _LIBFUNCSO_H_

typedef void (*ptrFunction)(char *buff,int len);
int Register_module(ptrFunction fun);
void my_function(void);


#endif

