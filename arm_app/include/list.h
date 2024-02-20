/**@file list.h
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
#ifndef _LIST_H_
#define _LIST_H_

#include <stdbool.h>


/* 定义好对象数据结构体 */
typedef struct class{

  char name[16];           //姓名
  int sex;                 //性别 0 男 1 女
  int age;                 //年龄
  char phone_num[16];      //电话号码
  char idenfinty_num[32];  //身份证
}Student;

/* 定义好链表结构体 */
typedef struct NODE{

	Student  stu;
	struct NODE * next;
	struct NODE * front;
}node, *list;



list creat_head(void);
bool add_node(list head, Student st);
bool del_node(list head, int age);



#endif


