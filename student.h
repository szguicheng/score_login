#ifndef STUDENT_H
#define STUDENT_H

#define S_NAME 20    //ѧ����������
#define S_NUMBER 20   //ѧ��ѧ�ų���
#define S_PASS 20  //���볤��
#define S_COUNT 1000//ѧ������

typedef struct Student  //ѧ���ṹ��
{
	char name[S_NAME];  //����
	char sex; //�Ա�
	char number[S_NUMBER]; //ѧ��
	char password[S_PASS]; //���� ���֡���ĸ����������š�����20���ڣ�
	int chinese; //���� �ж�����
	int math; //��ѧ �ж�����
	int english; //Ӣ��
	int sum;//�ܷ�
	int landing; //��½�Ĵ��� ��һ��ǿ��Ҫ���޸�����
	int Account_status;//�˺�״̬ 1���� 0����
}Student;

extern Student stu[S_COUNT];
extern Student s;

extern int s_count;

extern int s_position;

void sorce(void);//�ɼ�

void Pass(void);//��������

void Allmessage(void);//��ʾ��Ϣ

#endif //STUDENT_H
