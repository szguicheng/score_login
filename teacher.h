#ifndef TEACHER_H
#define TEACHER_H
#define T_COUNT 300
#define T_NAME 20//教师姓名长度
#define T_NUMBER 20 //教师工号长度
#define T_PASS 20 //密码长度
typedef struct Teacher
{
	char name[T_NAME];  //姓名  
	char sex;            //性别
	char number[T_NUMBER];//工号
	char password[T_PASS];//密码
	char school[T_PASS];  //学院
	int landing;          //登陆次数
	int Account_status;   //登陆状态
}Teacher;

extern Teacher tea[T_COUNT];
extern Teacher t;

extern int t_count;

extern int t_position;

bool t_add_stu(); //添加学生,返回false失败，返回true成功 

bool t_delete_stu();//删除学生 ，返回false 失败,返回true成功

bool t_search_stu();//查找学生,返回false 失败,返回true成功

bool t_modify_stu();//修改学生信息，返回false 失败,返回true成功

bool t_import_stu_score();//录入学生成绩，返回false 失败,返回true成功

bool t_reset_stu_pass();//重置学生密码，返回false 失败,返回true成功

void t_psearch_stu();//显示查找到的学生

void t_show_stu();//显示所有在校学生

void t_show_drop_stu();//显示退出学生

//void t_show_menu(); //显示教师菜单

void t_unlock(void);//给学生解锁


#endif//TEACHER_H
