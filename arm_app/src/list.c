/**@file list.c
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
 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <log_level.h>
#include <stdbool.h>

#include <list.h>


/*******************************************************************************
**函数名称：creat_stu
**功能描述：创建一个节点数据
**入口参数：无
**输出：节点结构体
*******************************************************************************/
Student creat_stu(void)
{
	Student new_stu;
	new_stu.age = 18;
	char *pname = "xiaohu";
	strcpy(new_stu.name, pname);

	return new_stu;
}

/*******************************************************************************
**函数名称：creat_head
**功能描述：创建一个链表头结点
**入口参数：无
**输出：头结点指针
*******************************************************************************/
list creat_head(void)
{
  list head = (list)malloc(sizeof(node));
  head->next = NULL;
  return head;
}

/*******************************************************************************
**函数名称：add_node
**功能描述：头插法新增一个节点
**入口参数：list head 头结点
**入口参数：Student st 新增的节点数据
**输出：插入成功 1 插入失败 0 
*******************************************************************************/
bool add_node(list head, Student st)
{
	 list new_node = (list)malloc(sizeof(node));

	 Student *st1 = NULL;
	 st1 = &st;
	 if(NULL != st1)
	 {
	  new_node->stu = st;
	  new_node->next = head->next;
	  head->next = new_node;
	  return 1;
	 }
	 else
	 {
      LOG_ERROR("add_new_node error!");
	  return 0;
	 }
}

/*******************************************************************************
**函数名称：del_node
**功能描述：删除一个固定的节点
**入口参数：list head 头结点
**入口参数：int age 删除年龄为age的成员
**输出：插入成功 1 插入失败 0 
*******************************************************************************/
bool del_node(list head, int age)
{
	list prev = head;    //定义一个节点一个人指向头节点
	list p = prev->next; //定义一个节点一个人指向头节点的下一个节点
	while(NULL != p)
	{
		if(p->stu.age >= age)
		{
			prev->next = p->next;
			free(p);
			if(NULL != p)
			{
			 p = NULL;
			}
			return 1;
		}
		prev = p;
		p = p->next;
	}
	LOG_ERROR("del_node failed");
	return 0;
}


/*******************************************************************************
**函数名称：list_test
**功能描述：链表测试函数
**入口参数：无
**输出：无
*******************************************************************************/
int list_test()
{
	Student stu = creat_stu();
	list head = creat_head();
	add_node(head, stu);
	//LOG_CUSTOM("head.name= %s head.age = %d head.class =%d",head->next->stu.name,head->next->stu.age,head->next->stu.class);
	add_node(head, stu);
	//LOG_CUSTOM("head.name= %s head.age = %d head.class =%d",head->next->stu.name,head->next->stu.age,head->next->stu.class);
	//LOG_CUSTOM("head.name= %s head.age = %d head.class =%d",head->next->next->stu.name,head->next->next->stu.age,head->next->next->stu.class);

	return 0;
}




