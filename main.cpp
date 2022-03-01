#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<ctype.h>
#include"student.h"
#include"tool.h"
#include"interface.h"
#include"teacher.h"
#include"admin.h"
#include"getch.h"

 



//密码输入带*
void getpass(char password[T_PASS])
{
	char ch;
	int i=0;
	char s[T_PASS];
	while ((ch = getch()) != '\r')
	{
		if (ch != '\b')//不是回撤就录入
		{

			s[i] = ch;
			putchar('*');//并且输出*号
			i++;
		}
		else
		{
			putchar('\b');//这里是删除一个，通过输出回撤符 /b，回撤一格，
			putchar(' ');//再显示空格符把刚才的*给盖住，
			putchar('\b');//然后再 回撤一格等待录入。
			i--;
		}
	}
	s[i] = '\0';
	strcpy(password, s);

}


//密码合法性确认
int islegal_pass(char pass[T_PASS])
{
	int panduan=0;
	for (int i = 0; i < strlen(pass); i++)
		if (!isdigit(pass[i]))
			panduan++;
		if (panduan!=0||(strlen(pass) > 20))
			return 0;
		else
			return 1;

}

//学生信息合法性确认
int is_legalstu(struct Student a)
{
	int i = 0;
	if (a.sex != 'm'&&a.sex!='f')i++;
	if (!islegal_pass(a.number))i++;
	if (!islegal_pass(a.password))i++;
	if (i == 0)
		return 1;
	else
		return 0;
}
//任意键退出
void anykey_continue()
{
	system("pause");
}
//主界面选项
void interface_enum(void)
{
	printf("--------------主  界  面---------------\n\n");
	printf("          1.学   生   登   录                  \n\n");
	printf("          2.教   师   登   录                  \n\n");
	printf("          3.管  理  员 登  录                  \n\n");
	printf("          4.退   出   系   统                   \n\n");
	printf("---------- 桂铖 42003096 制作------------\n");
}

//学生登录选项
void student_enum(void)
{
	printf("-----------%s同学您好,欢迎登录学生信息管理系统----------\n\n",s.name);
	printf("                   1.查 询 成 绩                      \n\n");
	printf("                   2.修 改 密 码                      \n\n");
	printf("                   3.查看个人信息                      \n\n");
	printf("                   4.退出系统                        \n\n");
}

//学生登录
void student_in(void)
{
	int miscount = 0;
	s_count = 0;
	FILE* fwwp = fopen("student.txt", "r");
	if (NULL == fwwp)
	{
		printf("文件打开失败!!!");
		anykey_continue();
		return;
	}
	while (!feof(fwwp))
	{
		fscanf(fwwp, "%s %c %s %s %d %d %d %d %d\n", stu[s_count].name, &stu[s_count].sex, stu[s_count].number, stu[s_count].password, &stu[s_count].chinese, &stu[s_count].math, &stu[s_count].english, &stu[s_count].landing, &stu[s_count].Account_status);
		s_count++;
	}
	fclose(fwwp);
	char number[T_NUMBER];
	char password[T_PASS];
	printf("请输入你的学号:");
	scanf("%s", number);
	for (int i = 0; i < S_COUNT; i++)
	{
		if (strcmp(stu[i].number, number) == 0 && stu[i].sex != 0)
		{
			if (stu[i].Account_status == 0)
			{
				printf("账号已锁定，请联系老师解锁!!");
				anykey_continue();
				return;
			}
			while (true)
			{
				printf("请输入你的密码:");
				getpass(password);
				if (strcmp(password, stu[i].password) == 0)
				{
					printf("登录成功!!!!");
					s = stu[i];
					s.sum = s.chinese + s.math + s.english;
					s_position = i;
					anykey_continue();
					if (s.landing == 0)
					{
						printf("\n第一次登录请更改你的密码:");
						while (true)
						{
							getpass(password);
							if (islegal_pass(password))
							{
								strcpy(s.password, password);
								printf("修改成功!!");
								s.landing = 1;
								anykey_continue();
								break;
							}
							else
							{
								printf("输入有误请重新输入!!!\n");
								anykey_continue();
							}
						}
					}
					student_show();
					return;
				}
				else
				{
					miscount++;
					if (miscount >= 3)
					{
						stu[i].Account_status = 0;
						printf("密码错误超过３次，账号已锁定，请联系教师解锁!!");
						FILE* fwp = fopen("student.txt", "w");
						if (NULL == fwp)
						{
							printf("文件打开失败!!!");
							anykey_continue();
							return;
						}
						for (int i = 0; i < S_COUNT; i++)
						{
							if (stu[i].sex != 0)
							{
								fprintf(fwp, "%s %c %s %s %d %d %d %d %d\n", stu[i].name, stu[i].sex, stu[i].number, stu[i].password, stu[i].chinese, stu[i].math, stu[i].english, stu[i].landing, stu[i].Account_status);
							}
						}
						fclose(fwp);
						anykey_continue();
						return;
					}
				}
			}
		}
	}
}

//学生操作
void student_show(void)
{
	system("cls");
	while (true)
	{
		system("cls");
		student_enum();
		switch (getch())
		{
		case '1':sorce();
			break;
		case '2':Pass();
			break;
		case '3':Allmessage();
			break;
		case '4':
		{
			stu[s_position] = s;
			FILE* fwp = fopen("student.txt", "w");
			if (NULL == fwp)
			{
				printf("文件打开失败!!!");
				anykey_continue();
				return;
			}
			for (int i = 0; i < S_COUNT; i++)
			{
				if (stu[i].sex != 0)
					fprintf(fwp, "%s %c %s %s %d %d %d %d %d\n", stu[i].name, stu[i].sex, stu[i].number, stu[i].password, stu[i].chinese, stu[i].math, stu[i].english, stu[i].landing, stu[i].Account_status);
			}
			fclose(fwp);
			return;
		}
		default:printf("输入有误，请重新输入!!!");
			break;
		}
	}
}

//教师登录选项
void teacher_enum(void)
{
	printf("----------尊敬的%s学院的%s老师,欢迎登录学生管理系统----------- \n\n",t.school,t.name);
	printf("                     1.添 加 学 生                      \n\n");
	printf("                     2.删 除 学 生                      \n\n");
	printf("                     3.查 找 学 生                      \n\n");
	printf("                     4.修改学生信息                     \n\n");
	printf("                     5.录入学生成绩                     \n\n");
	printf("                     6.重置学生密码                     \n\n");
	printf("                     7.显示所有在校学生信息             \n\n");
	printf("                     8.显示所有退学学生信息             \n\n");
	printf("                     9.给学生解锁                      \n\n");
	printf("                     0.退出系统                      \n\n");
}

//教师登录
void teacher_in(void)
{
	int miscount = 0;
	s_count = 0;
	t_count = 0;
	FILE* frp = fopen("teacher.txt", "r");
	if (NULL == frp)
	{
		printf("文件打开失败!!!");
		anykey_continue();
		return;
	}
	while (!feof(frp))
	{
		fscanf(frp,"%s %c %s %s %s %d %d\n", tea[t_count].name, &tea[t_count].sex, tea[t_count].number,
			tea[t_count].password, tea[t_count].school,&tea[t_count].landing, &tea[t_count].Account_status);
		t_count++;
	}
	fclose(frp);

	FILE* fwwp = fopen("student.txt", "r");
	if (NULL == fwwp)
	{
		printf("文件打开失败!!!");
		anykey_continue();
		return;
	}
	while (!feof(fwwp))
	{
		fscanf(fwwp, "%s %c %s %s %s %d %d %d %d %d\n", stu[s_count].name, &stu[s_count].sex, stu[s_count].number, stu[s_count].password,
			&stu[s_count].chinese, &stu[s_count].math, &stu[s_count].english, &stu[s_count].landing, &stu[s_count].Account_status);
		s_count++;
	}
	fclose(fwwp);
	char number[T_NUMBER];
	char password[T_PASS];
	printf("请输入你的工号:");
	scanf("%s", number);
	for (int i = 0; i < T_COUNT; i++)
	{
		if (strcmp(tea[i].number, number) == 0 && tea[i].sex != 0)
		{
			if (tea[i].Account_status == 0)
			{
				printf("账号已锁定，请联系管理员解锁!!");
				anykey_continue();
				return;
			}
			while (true)
			{
				printf("请输入你的密码:");
				getpass(password);
				if (strcmp(password, tea[i].password) == 0)
				{
					printf("登录成功!!!!");
					t = tea[i];
					t_position = i;
					anykey_continue();
					if (t.landing == 0)
					{
						printf("\n第一次登录请更改你的密码:");
						while (true)
						{
							getpass(password);
							if (islegal_pass(password))
							{
								strcpy(t.password, password);
								printf("修改成功!!");
								t.landing = 1;
								anykey_continue();
								break;
							}
							else
							{
								printf("输入有误请重新输入!!!\n");
								anykey_continue();
							}
						}
					}
					teacher_show();
					return;
				}
				else
				{
					miscount++;
					if (miscount >= 3)
					{
						tea[i].Account_status = 0;
						printf("密码错误超过３次，账号已锁定，请联系管理员解锁!!");
						FILE* fwp = fopen("teacher.txt", "w");
						if (NULL == fwp)
						{
							printf("文件打开失败!!!");
							anykey_continue();
							return;
						}
						for (int i = 0; i < T_COUNT; i++)
						{
							if (tea[i].sex != 0)
							{
								fprintf(fwp, "%s %c %s %s %s %d %d\n", tea[i].name, tea[i].sex, tea[i].number, 
									tea[i].password,tea[i].school, tea[i].landing, tea[i].Account_status);
							}
						}
						fclose(fwp);
						anykey_continue();
						return;
					}
				}
			}
		}
	}
}

//教师操作
void teacher_show(void)
{
	system("cls");
	while (true)
	{
		system("cls");
		teacher_enum();
		switch (getch())
		{
		case '1':t_add_stu();
			anykey_continue();
			break;
		case '2':t_delete_stu();
			anykey_continue();
			break;
		case '3':t_psearch_stu();
			anykey_continue();
			break;
		case '4':t_modify_stu();
			anykey_continue();
			break;
		case '5':t_import_stu_score();
			anykey_continue();
			break;
		case '6':t_reset_stu_pass();
			anykey_continue();
			break;
		case '7':t_show_stu();
			anykey_continue();
			break;
		case '8':t_show_drop_stu();
			anykey_continue();
			break;
		case '9':t_unlock();
			break;
		case '0':
		{
			tea[t_position] = t;
			FILE* fwp = fopen("student.txt", "w");
			if (NULL == fwp)
			{
				printf("文件打开失败!!!");
				anykey_continue();
				return;
			}
			FILE* fw = fopen("teacher.txt", "w");
			if (NULL == fw)
			{
				printf("文件打开失败!!!");
				anykey_continue();
				return;
			}
			for (int i = 0; i < T_COUNT; i++)
			{
				if (tea[i].sex != 0)
					fprintf(fw, "%s %c %s %s %d %d\n", tea[i].name, tea[i].sex, tea[i].number, tea[i].password, tea[i].landing, tea[i].Account_status);
			}
			for (int i = 0; i < S_COUNT; i++)
			{
				if (stu[i].sex != 0)
					fprintf(fwp, "%s %c %s %s %d %d %d %d %d\n", stu[i].name, stu[i].sex, stu[i].number, stu[i].password, stu[i].chinese, stu[i].math, stu[i].english, stu[i].landing, stu[i].Account_status);
			}
			fclose(fwp);
			fclose(fw);
			return;
			break;
		}
		default:printf("输入有误，请重新输入!!!");
			break;
		}
	}
}

//管理员登录选项
void admin_enum(void)
{
	printf("--------------尊敬的管理员欢迎登录学生管理系统----------- \n\n");
	printf("                     1.添 加 教 师                     \n\n");
	printf("                     2.删 除 教 师                     \n\n");
	printf("                     3.修改教师密码                     \n\n");
	printf("                     4.修改管理员密码                     \n\n");
	printf("                     5.显示所有在职教师                  \n\n");
	printf("                     6.显示所有离职教师                   \n\n");
	printf("                     7.给教师解锁                       \n\n");
	printf("                     8.退出系统                       \n\n");
}

//管理员登录
void admin_in(void)
{
	int a_count = 0;
	FILE* fsp = fopen("admin.txt", "r");//打开管理员txt
	if (NULL == fsp)
	{
		printf("文件打开失败！！");
		anykey_continue();
		return;
	}
	while (!feof(fsp))
	{
		fscanf(fsp, "%s %s %d\n", adm[a_count].number, adm[a_count].password, &adm[a_count].landing);
		a_count++;
	}

	FILE* frp = fopen("teacher.txt", "r");//打开教师txt
	if (NULL == frp)
	{
		printf("文件打开失败!!!");
		anykey_continue();
		return;
	}
	while (!feof(frp))
	{
		fscanf(frp, "%s %c %s %s %s %d %d\n", tea[t_count].name, &tea[t_count].sex, tea[t_count].number,
			tea[t_count].password, tea[t_count].school, &tea[t_count].landing, &tea[t_count].Account_status);
		t_count++;
	}
	fclose(frp);

	//构建输入信息
	char number[A_NUMBER];
	char password[A_PASS];
	printf("请输入你的账号:");
	scanf("%s", number);
	for (int i = 0; i < T_COUNT; i++)
	{
		if (strcmp(adm[i].number, number) == 0)
		{

			char passwordr[A_PASS];
			while(true)
			{
				printf("请输入您的密码：");
				getpass(passwordr);
				if (strcmp(passwordr, adm[i].password) == 0)
				{
					printf("登录成功!!!!");
				}
				FILE* frp = fopen("teacher.txt", "r");
				if (NULL == frp)
				{
					printf("文件打开失败!!!");
					anykey_continue();
					return;
				}
				while (!feof(frp))
				{
					fscanf(frp, "%s %c %s %s %d %d\n", tea[t_count].name, &tea[t_count].sex, tea[t_count].number, tea[t_count].password, &tea[t_count].landing, &tea[t_count].Account_status);
					t_count++;
				}
				fclose(frp);
				anykey_continue();
				if (adm[i].landing == 0)
				{
					printf("\n第一次登录请更改你的密码:");
					while (true)
					{
						getpass(password);
						if (islegal_pass(password))
						{
							strcpy(adm[i].password, password);
							printf("修改成功!!");
							adm[i].landing = 1;
							anykey_continue();
							break;
						}
						else
						{
							printf("输入有误请重新输入!!!");
						}
					}
				}
				admin_show();
				return;
			}
		}
		printf("密码或者账号错误!!!!");
		anykey_continue();
		return;
	}
}

//管理员操作
void admin_show(void)
{
	
	system("cls");
	while (true)
	{
		system("cls");
		admin_enum();
		switch (getch())
		{
		case '1':a_add_teacher();
			break;
		case '2':a_delete_teacher();
			break;
		case '3':a_reset_password_teacher();
			break;
		case '4':a_change_password_myself();
			break;
		case '5':a_show_in_teacher();
			break;
		case '6':a_show_down_teacher();
			break;
		case '7':a_unlock();
			break;
		case '8':
		{
			FILE* fwp = fopen("teacher.txt", "w");
			if (NULL == fwp)
			{
				printf("文件打开失败!!!");
				anykey_continue();
				return;
			}
			FILE* fw = fopen("admin.txt", "w");
			if (NULL == fw)
			{
				printf("文件打开失败!!!");
				anykey_continue();
				return;
			}
			for (int i = 0; i < T_COUNT; i++)
			{
				if (tea[i].sex != 0)
					fprintf(fwp, "%s %c %s %s %d %d\n", tea[i].name, tea[i].sex, tea[i].number, tea[i].password, tea[i].landing, tea[i].Account_status);
			}
			for (int i = 0; i < A_COUNT; i++)
			{
				if (adm[i].sex != 0)
					fprintf(fw, "%s\n", adm[i].name);
			}
			fclose(fwp);
			fclose(fw);
			return;
			break;
		}
		default:printf("输入有误，请重新输入!!!");
			break;
		}
	}
}


//**********************************学生操作代码实现*****************************************************//
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"student.h"
#include"tool.h"
#include"getch.h"

Student stu[S_COUNT];
Student s;

int s_position = 0;

int s_count = 0;

void sorce(void)
{
	int ranking = 1;
	Student a;
	int max = -1, min = 1000;
	for (int i = 0; i < S_COUNT; i++)
	{
		if (stu[i].sex != 0)
		{
			stu[i].sum = stu[i].math + stu[i].chinese + stu[i].english;
		}
	}
	for (int i = 0; i < S_COUNT; i++)
	{
		if (stu[i].sex != 0)
		{
			if (stu[i].sum > max) max = stu[i].sum;
			if (stu[i].sum < min) min = stu[i].sum;
			if (s.sum < stu[i].sum) ranking++;
		}
	}
	printf("1.排名 2.平均分 3.最高分 4.最低分");
	switch (getch())
	{
	case '1':printf("\n你的排名为:%d", ranking);
		anykey_continue();
		break;
	case '2':printf("\n你的平均分为:%d", s.sum / 3);
		anykey_continue();
		break;
	case '3':printf("\n最高分为:%d", max);
		anykey_continue();
		break;
	case '4':printf("\n最低分为:%d", min);
		anykey_continue();
		break;
	}
}

void Pass(void)//更改密码
{
	char pass1[S_PASS], pass2[S_PASS], pass3[S_PASS];
	for (;;)
	{
		printf("输入原密码:\n");
		getpass(pass1);
		if (strcmp(pass1, s.password) == 0)
		{
			printf("输入要更改的密码:\n");
			scanf("%s", pass2);
		}
		else
		{
			printf("原密码错误重新输入:\n");
			continue;
		}
		if (islegal_pass(pass2))
		{
			printf("再次输入密码:\n");
			scanf("%s", pass3);
		}
		else
		{
			printf("输入不合法");
			continue;
		}
		if (strcmp(pass3, pass2) == 0)
		{
			strcpy(s.password, pass3);
			for (int i = 0; i < S_COUNT; i++)
			{
				if (strcmp(s.number, stu[i].number) == 0)
				{
					stu[i] = s;
					stu[i].landing = 1;
				}
			}
			printf("修改成功\n");
			anykey_continue();
			return;
		}
		else
		{
			printf("修改失败,请重新输入\n");
			anykey_continue();
			continue;
		}
	}
}

void Allmessage(void)
{
	for (int i = 0; i < S_COUNT; i++)
	{
		if (strcmp(s.number, stu[i].number) == 0)
		{
			printf("姓名:%s 性别:%c 学号:%s 语文:%d 数学:%d 英语:%d\n", stu[i].name, stu[i].sex, 
				stu[i].number, stu[i].chinese, stu[i].math, stu[i].english);
			anykey_continue();
		}
	}
}

//*****************************************教师操作代码实现*****************************************************//

#include<stdio.h>
#include<stdbool.h>
#include"tool.h"
#include"teacher.h"
#include"student.h"
Teacher tea[T_COUNT];
Teacher t;

int t_position = 0;
int t_count = 0;
int index_stu = 0;

//添加学生
bool t_add_stu()
{

	if (s_count >= S_COUNT)
		return false;
	printf("请选择你要添加的方式\n");
	printf("1、单个添加\n");
	printf("2、批量导入\n");
	printf("3、退出添加\n");
	int ch;
	do
	{
		scanf("%d", &ch);
		if (1 != ch && 2 != ch && 3 != ch)
		{
			printf("输入错误请重新输入\n");
		}
		fflush(stdout);
	} while (1 != ch && 2 != ch && 3 != ch);

	if (1 == ch)
	{


		int i = 0;
		while (0 != stu[i].sex)i++;
		Student s;
		do
		{
			printf("请输入你要添加的学生的姓名\n");
			scanf("%s", &s.name);
			printf("请输入你要添加的学生的性别\n");
			scanf(" %c", &s.sex);
			printf("请输入你要添加的学生的学号\n");
			scanf("%s", &s.number);
			if (!islegal_pass(s.number))
			{
				printf("学生学号非法，请重新输入\n");
				continue;
			}
			printf("请输入你要添加的学生的密码\n");
			getpass(s.password);
			if (!islegal_pass(s.password))
			{
				printf("学生密码非法，请重新输入\n");
				continue;
			}
			if (!is_legalstu(s))
				printf("学生信息有误，请重新输入\n");
		} while (!is_legalstu(s));
		s.chinese = 0;
		s.math = 0;
		s.english = 0;
		s.landing = 0;
		s.Account_status = 1;
		stu[i] = s;
	}
	else if (2 == ch)
	{
		printf("请输入你要添加的文件的路径\n");
		char path[20];
		scanf("%s", path);
		int cnt = 0;
		FILE* f = fopen(path, "a");//导入文件
		if (NULL == f)
		{
			printf("文件路径错误\n");
			return false;
		}
		int i = 0;
		while (!feof(f)) //读数据
		{
			fscanf(f, "%s%c%s%s%d%d%d%d%d", stu[i].name,
				&stu[i].sex, stu[i].number, stu[i].password,
				&stu[i].chinese, &stu[i].math, &stu[i].english,
				&stu[i].landing, &stu[i].Account_status);
			i++;
			if (i >= s_count)
				s_count++;

		}
	}
	else if (3 == ch)
	{
		printf("正在退出\n");
		fflush(stdout);
		Sleep(1);
		return false;
	}
	printf("添加成功\n");
	return true;
}

//查找学生,返回false 失败,返回true成功
bool t_search_stu()
{
	printf("请选择你要查找的方式\n");
	printf("1、姓名查找\n");
	printf("2、学号查找\n");
	printf("3、退出查找\n");
	int  ch;
	do
	{
		scanf("%d", &ch);
		if (1 != ch && 2 != ch && 3 != ch)
		{
			printf("输入错误请重新输入\n");
		}
	} while (1 != ch && 2 != ch && 3 != ch);

	if (1 == ch)//按照姓名查找
	{
		printf("请输入你要查找的学生的姓名\n");
		char name[20];
		scanf("%s", name);
		for (int i = 0; i < S_COUNT; i++)
		{
			if (0 == strcmp(name, stu[i].name) && stu[i].sex != 0)
			{
				index_stu = i; //保存查找到的学生的下标
				printf("查找成功\n");
				return true;
			}
		}
	}
	else if (2 == ch)//按学号查找
	{

		char number[20];
		do
		{
			printf("请输入你要查找的学生的学号\n");
			scanf("%s", number);
			if (!islegal_pass(number))
				printf("输入错误请重新输入\n");
		} while (!islegal_pass(number));

		for (int i = 0; i < S_COUNT; i++)
		{
			if (0 == strcmp(number, stu[i].number) && stu[i].sex != 0)
			{
				index_stu = i;
				printf("查找成功\n");
				return true;
			}
		}
	}
	else if (3 == ch)
	{
		printf("正在退出\n");
		fflush(stdout);
		Sleep(1);
		return false;
	}
	printf("查找失败\n");
	return false;
}

//显示查找到的学生
void t_psearch_stu()
{
	if (!t_search_stu())
		return;
	printf("姓名:%s 性别:%c 学号:%s 语文:%3d 英语:%3d 数学:%3d\n", stu[index_stu].name,
		stu[index_stu].sex, stu[index_stu].number,
		stu[index_stu].chinese, stu[index_stu].english,
		stu[index_stu].math);
}

//删除学生 ，返回false 失败,返回true成功
bool t_delete_stu()
{
	printf("查找你要删除的学生的信息\n");
	if (!t_search_stu())
	{
		printf("删除失败\n");
		return false;
	}
	int cnt = 1;
	char numbers[20];
	while (cnt <= 2)
	{
		printf("请输入学号加以确认,第%d次: \n", cnt);
		scanf("%s", numbers);
		cnt++;
		if (0 != strcmp(numbers, stu[index_stu].number))
			cnt--;
	}

	FILE* ds = fopen("downstudent.txt", "a");
	if (NULL == ds)
	{
		perror("fopen:");
		return false;
	}

	fprintf(ds, "%s %c %s\n", stu[index_stu].name,
		stu[index_stu].sex, stu[index_stu].number);
	fclose(ds);
	stu[index_stu].sex = 0;
	//更新两张表

	printf("删除成功\n");
	//fflush(stdout);
	//usleep(1000);
	return true;
}

//重置学生密码，返回false 失败,返回true成功
bool t_reset_stu_pass()
{
	printf("请选择你要重置密码的学生\n");
	if (!t_search_stu())
	{
		printf("重置密码失败\n");
		return false;
	}
	strcpy(stu[index_stu].password, "123456");
	printf("重置为:%s\n", "123456");
	printf("重置成功\n");
	return true;
}

//显示所有在校学生
void t_show_stu()
{
	for (int i = 0; i < S_COUNT; i++)
	{
		if (0 != stu[i].sex)
		{
			printf("姓名:%s 性别:%s 学号:%s 语文:%d 数学:%d 英语:%d\n", stu[i].name, stu[i].sex == 'w' ? "女" : "男", stu[i].number, stu[i].chinese, stu[i].math, stu[i].english);
		}
	}
}

//录入学生成绩，返回false 失败,返回true成功
bool t_import_stu_score()
{
	printf("请选择你要添加的方式\n");
	printf("1、单个录入\n");
	printf("2、退出录入\n");
	int  ch;
	do
	{
		scanf("%d", &ch);
		if (1 != ch && 2 != ch)
		{
			printf("输入错误请重新输入\n");
		}
	} while (1 != ch && 2 != ch);
	if (1 == ch)
	{
		printf("请选择你要录入成绩的对象\n");
		if (!t_search_stu())
		{
			printf("录入失败\n");
			return false;
		}
		int flag = 1;
		do
		{
			flag = 0;
			printf("输入学生的语文成绩\n");
			scanf("%d", &stu[index_stu].chinese);
			if (0 > stu[index_stu].chinese ||
				stu[index_stu].chinese > 100)
			{
				printf("语文成绩非法\n");
				flag = 1;
				continue;
			}

			printf("输入学生的英语成绩\n");
			scanf("%d", &stu[index_stu].english);

			if (0 > stu[index_stu].english ||
				stu[index_stu].english > 100)
			{
				printf("英语成绩非法\n");
				flag = 1;
				continue;
			}

			printf("输入学生的数学成绩\n");
			scanf("%d", &stu[index_stu].math);

			if (0 > stu[index_stu].math ||
				stu[index_stu].math > 100)
			{
				printf("数学成绩非法\n");
				flag = 1;
				continue;
			}
		} while (flag);
		printf("录入成功\n");
		return true;
	}
	else if (2 == ch)
	{
		printf("正在退出\n");
		fflush(stdout);
		//usleep(1000);
		return false;
	}
	return false;

}

//显示退出学生
void t_show_drop_stu()
{
	Student s;
	FILE* f = fopen("downstudent.txt", "r");
	while (!feof(f))
	{
		fscanf(f, "%s %c %s\n", s.name,
			&s.sex, s.number);
		printf("姓名:%s 性别:%s 学号:%s\n", s.name, s.sex == 'w' ? "女" : "男", s.number);
	}
	fclose(f);
}

//修改学生信息，返回false 失败,返回true成功
bool t_modify_stu()
{
	printf("请输入你要修改的学生信息\n");
	if (!t_search_stu())
	{
		printf("修改失败\n");
		return false;
	}
	printf("请选择你要修改信息\n");
	printf("1、学生基础信息修改\n");
	printf("2、学生成绩修改\n");
	printf("3、退出修改\n");
	int  ch;
	do
	{
		scanf("%d", &ch);
		if (1 != ch && 2 != ch && 3 != ch)
		{
			printf("输入错误请重新输入\n");
		}
	} while (1 != ch && 2 != ch && 3 != ch);


	if (1 == ch)
	{

		do
		{
			printf("请输入你要修改的学生的姓名\n");
			scanf("%s", stu[index_stu].name);
			printf("请输入你要修改的学生的性别\n");
			scanf(" %c", &stu[index_stu].sex);
			printf("请输入你要修改的学生的学号\n");
			scanf("%s", stu[index_stu].number);
			if (!islegal_pass(stu[index_stu].number))
			{
				printf("学生学号错误\n");
				continue;
			}
			printf("请输入你要修改的学生的密码\n");
			scanf("%s", stu[index_stu].password);
			if (!islegal_pass(stu[index_stu].password))
			{
				printf("学生密码错误\n");
				continue;
			}
			if (!is_legalstu(stu[index_stu]))
				printf("学生信息有误,请重新输入\n");
		} while (!is_legalstu(stu[index_stu]));
		printf("修改成功\n");
	}
	else if (2 == ch)
	{
		int flag = 1;
		do
		{
			flag = 0;
			printf("输入学生的语文成绩\n");
			scanf("%d", &stu[index_stu].chinese);
			if (0 > stu[index_stu].chinese ||
				stu[index_stu].chinese > 100)
			{
				printf("语文成绩非法\n");
				flag = 1;
				continue;
			}

			printf("输入学生的英语成绩\n");
			scanf("%d", &stu[index_stu].english);

			if (0 > stu[index_stu].english ||
				stu[index_stu].english > 100)
			{
				printf("英语成绩非法\n");
				flag = 1;
				continue;
			}

			printf("输入学生的数学成绩\n");
			scanf("%d", &stu[index_stu].math);

			if (0 > stu[index_stu].math ||
				stu[index_stu].math > 100)
			{
				printf("数学成绩非法\n");
				flag = 1;
				continue;
			}
		} while (flag);
		printf("修改成功\n");
	}
	else if (3 == ch)
	{
		printf("正在退出\n");
		fflush(stdout);
		Sleep(1);
		return false;
	}
	return false;

}

//给学生解锁
void t_unlock(void)
{
	char number[S_NUMBER];
	printf("请输入要解锁的学生学号:");
	scanf("%s", number);
	while (true)
	{
		for (int i = 0; i < S_COUNT; i++)
		{
			if (strcmp(stu[i].number, number) == 0)
			{
				if (stu[i].Account_status == 0)
				{
					stu[i].Account_status = 1;
					printf("解锁成功!!");
					anykey_continue();
					return;
				}
				else
				{
					printf("你输入的学生状态为未锁定请重新确认！！");
					anykey_continue();
					return;
				}
			}
		}
		printf("你找到学号不存在!!!");
		anykey_continue();
		return;
	}
}



//**********************************管理员操作代码实现*************************************//

#include"admin.h"
#include"tool.h"
#include"teacher.h"
#include"admin.h"

Admin adm[A_COUNT];
int a_count = 0;
//修改自己的密码
void a_change_password_myself(void)
{
	char newpass[A_PASS];
	while (true)
	{
		printf("请输入新的密码：");
		getpass(newpass);
		if (islegal_pass(newpass))
		{
			strcpy(adm[a_count].password, newpass);
			printf("修改成功!!");
			anykey_continue();
			return;
		}
		else
		{
			printf("密码不合法，重新输入!!!");
			anykey_continue();
		}
	}
}

//重置自己的密码
void a_reset_password_myself(void)
{
	printf("是否确定重置密码!!!!(y/n)");
	char temp = getchar();
	if (temp == 'Y' || temp == 'y')
	{
		strcpy(adm[a_count].password, "123456");
		printf("初始化成功!!初始密码为123456");
		anykey_continue();
		return;
	}
}

//重置教师密码
void a_reset_password_teacher(void)
{
	char number[T_NUMBER];
	char newpass[T_PASS];
	printf("请输入要修改的教师的工号：");
	scanf("%s", number);
	for (int i = 0; i < T_COUNT; i++)
	{
		if (strcmp(tea[i].number, number) == 0 && tea[i].sex != 0)
		{
			while (true)
			{
				printf("\n请输入修改后该教师的密码:");
				scanf("%s", newpass);
				if (islegal_pass(newpass))
				{
					strcpy(tea[i].password, newpass);
					printf("修改成功！！！");
					anykey_continue();
					return;
				}
				else
				{
					printf("密码不合法，请重新输入！！！");
					anykey_continue();
				}
			}
		}
	}
	printf("未找到该教师，请重新确认后再进行修改！！！");
	anykey_continue();
	return;
}

//添加教师
void a_add_teacher(void)
{
	if (t_count > T_COUNT)
	{
		printf("ｖｉｐ可享受更多存储空间!!!");
		return;
	}
	int the_number = 0;
	for (int i = 0; i < T_COUNT; i++)
	{
		if (tea[i].sex == 0)
		{
			the_number = i;
			break;
		}
	}
	char name[T_NAME];
	char sex;
	char number[T_NUMBER];
	printf("请输入教师姓名：");
	scanf("%s", name);
	strcpy(tea[the_number].name, name);
	printf("请输入教师性别: ");
	while (true)
	{
		scanf(" %c", &sex);
		if ('f' == sex || 'm' == sex)
		{
			tea[the_number].sex = sex;
			break;
		}
		printf("输入有误请重新输入!!!\n");
	}
	printf("请输入教师的工号:");
	while (true)
	{
		int f = 0;
		scanf("%s", number);
		for (int i = 0; i < t_count; i++)
		{
			if (strcmp(tea[i].number, number) == 0)
			{
				printf("该工号已存在,请重新输入!!!\n");
				f = 1;
				break;
			}
		}
		if (f == 0)
		{
			strcpy(tea[the_number].number, number);
			break;
		}
	}
	printf("请输入教师的密码：");
	while (true)
	{
		char password[T_PASS];
		getpass(password);
		if (islegal_pass(password))
		{
			strcpy(tea[the_number].password, password);
			break;
		}
		else
		{
			printf("密码不合法请重新输入!!!\n");
			anykey_continue();
		}
	}
	tea[the_number].landing = 0;
	tea[the_number].Account_status = 1;
	printf("录入成功");
	t_count++;
	anykey_continue();
}

//删除教师
void a_delete_teacher(void)
{
	char number[T_NUMBER];
	printf("请输入要删除的教师的工号：");
	scanf("%s", number);
	for (int i = 0; i < T_COUNT; i++)
	{
		if (strcmp(tea[i].number, number) == 0 && tea[i].sex != 0)
		{
			//文件存储离职教师的信息
			//删除离职老师的信息
			FILE* fwp = fopen("downteacher.txt", "a");
			if (NULL == fwp)
			{
				printf("文件打开失败！！");
				anykey_continue();
				return;
			}
			fprintf(fwp, "%s %c %s", tea[i].name, tea[i].sex, tea[i].number);
			fclose(fwp);
			tea[i].sex = 0;
			t_count--;
			printf("删除成功！！！");
			anykey_continue();
			return;
		}
	}
	printf("未找到该老师的工号！！");
	anykey_continue();
}

//显示所有在职教师
void a_show_in_teacher(void)
{
	for (int i = 0; i < T_COUNT; i++)
	{
		if (tea[i].sex != 0)
		{
			printf("姓名:%s 性别:%s 编号:%s\n", tea[i].name, tea[i].sex == 'f' ? "女" : "男", tea[i].number);
		}
	}
	anykey_continue();
}

//显示所有离职教师
void a_show_down_teacher(void)
{
	char name[T_NAME];
	char sex;
	char number[T_NUMBER];
	FILE* frp = fopen("downteacher.txt", "r");
	if (NULL == frp)
	{
		printf("文件打开失败!!");
		anykey_continue();
		return;
	}
	while (!feof(frp))
	{
		fscanf(frp, "%s %c %s", name, &sex, number);
		printf("姓名:%s 性别:%s 编号:%s\n", name, sex == 'f' ? "女" : "男", number);
		anykey_continue();
	}
	fclose(frp);
}

//给教师解锁
void a_unlock(void)
{
	char number[T_NUMBER];
	printf("请输入要解锁的教师工号:");
	scanf("%s", number);
	while (true)
	{
		for (int i = 0; i < T_COUNT; i++)
		{
			if (strcmp(tea[i].number, number) == 0)
			{
				if (tea[i].Account_status == 0)
				{
					tea[i].Account_status = 1;
					printf("解锁成功!!");
					anykey_continue();
					return;
				}
				else
				{
					printf("你输入的教师状态为未锁定请重新确认！！");
					anykey_continue();
					return;
				}
			}
		}
		printf("你找到工号不存在!!!");
		anykey_continue();
		return;
	}
}




//**********************运行主程序**************************//
int main()
{
	interface_enum();
	int choice1,choice2;
	scanf("%d", &choice1);
	switch (choice1) 
	{
	case 1:student_in();break;
	case 2:teacher_in(); break;
	case 3:admin_in(); break;
	case 4:exit(0); break;
	}

}
