#ifndef TEACHER_H
#define TEACHER_H
#define T_COUNT 300
#define T_NAME 20//��ʦ��������
#define T_NUMBER 20 //��ʦ���ų���
#define T_PASS 20 //���볤��
typedef struct Teacher
{
	char name[T_NAME];  //����  
	char sex;            //�Ա�
	char number[T_NUMBER];//����
	char password[T_PASS];//����
	char school[T_PASS];  //ѧԺ
	int landing;          //��½����
	int Account_status;   //��½״̬
}Teacher;

extern Teacher tea[T_COUNT];
extern Teacher t;

extern int t_count;

extern int t_position;

bool t_add_stu(); //���ѧ��,����falseʧ�ܣ�����true�ɹ� 

bool t_delete_stu();//ɾ��ѧ�� ������false ʧ��,����true�ɹ�

bool t_search_stu();//����ѧ��,����false ʧ��,����true�ɹ�

bool t_modify_stu();//�޸�ѧ����Ϣ������false ʧ��,����true�ɹ�

bool t_import_stu_score();//¼��ѧ���ɼ�������false ʧ��,����true�ɹ�

bool t_reset_stu_pass();//����ѧ�����룬����false ʧ��,����true�ɹ�

void t_psearch_stu();//��ʾ���ҵ���ѧ��

void t_show_stu();//��ʾ������Уѧ��

void t_show_drop_stu();//��ʾ�˳�ѧ��

//void t_show_menu(); //��ʾ��ʦ�˵�

void t_unlock(void);//��ѧ������


#endif//TEACHER_H
