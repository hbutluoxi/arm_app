/**@file fileoperation.c
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

#include <stdio.h>
#include <stdlib.h>
#include <log_level.h>

#include <fileoperation.h>
#include <list.h>


void read_file()
{
	FILE *fp = NULL;
	Student stu1;

	list head = creat_head();

	
	char buff[100] = {0};
	int type_num = 0;
	memset(buff, 0, sizeof(buff));
	fp = fopen(FILE_PATH, "r");
	if(fp != NULL)
	{
		while(fgets(buff, sizeof(buff), fp)!=NULL)
		{
		    LOG_CUSTOM("buff is %s",buff);
			char* str1 = strtok(buff, " ,");
			LOG_CUSTOM("%s", str1);
			while (str1 != NULL)
			{
			   switch(type_num)
				{
					case NAME:
						sprintf(stu1.name, "%s", str1);
						break;
					case SEX:
						sprintf(stu1.name, "%s", str1);
						break;
				    case AGE:
						sprintf(stu1.name, "%s", str1);
						break;
				    case TEL:
						sprintf(stu1.name, "%s", str1);
						break;
			        case ID:
						sprintf(stu1.name, "%s", str1);
						break;

					default:
						break;

				 }
			     type_num ++;
				 str1 = strtok(NULL, " ,");

			}	
            //读取完一个数据，在链表中创建一个节点
			add_node(head, stu1);

#if 0
			//使用sscanf()实现固定格式的读取。正则表达式读取
			//函数原型：int sscanf (char *str, char * format [, argument, ...]);
			//与scanf()区别，scanf的输入是在键盘输入的，而sscanf()是在用户定义的缓冲区获取的固定格式的数据。
			char str[] = "894529306@qq.com";
			int b;
			char c[10];
			int n=sscanf(str, "%d@%[a-z]", &b, c);
			printf("用户名%d\n", b);
			printf("邮箱类型%s\n", c);
			printf("返回值%d\n", n);//返回值为成功读取的参数个数，失败为-1
#endif

		}
	
        fclose(fp);
	}
	else
	{
	 LOG_ERROR("open  file fail in %s",FILE_PATH);
	}


}





