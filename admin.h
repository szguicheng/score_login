#ifndef ADMIN_H

#define ADMIN_H

#define A_COUNT 20

#define A_NAME 20  //����Ա��������

#define A_NUMBER 20 //����Աѧ�ų���

#define A_PASS 20//����Ա���볤��

//#define A_COUNT 10//����Ա����



typedef struct Admin  //����Ա�ṹ��

{

	char name[A_NAME];  //����

	char sex;    //�Ա�

	char number[A_NUMBER];  //����

	char password[A_PASS]; //���� ���֡���ĸ����������š�����20���ڣ�

	int landing;//��½�Ĵ��� ��һ��ǿ��Ҫ���޸�����

}Admin;



extern Admin adm[A_COUNT];
extern Admin a;



//�޸��Լ�������

void a_change_password_myself(void);



//�����Լ�������

//void a_reset_password_myself(void);



//���ý�ʦ����

void a_reset_password_teacher(void);



//��ӽ�ʦ

void a_add_teacher(void);



//ɾ����ʦ

void a_delete_teacher(void);



//��ʾ������ְ��ʦ

void a_show_in_teacher(void);



//��ʾ������ְ��ʦ

void a_show_down_teacher(void);



//����ʦ����

void a_unlock(void);



#endif//ADMIN_H#pragma once
