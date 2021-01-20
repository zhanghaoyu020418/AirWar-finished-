#pragma once

#include "graphics.h"
#include <iostream>
#include "AirPlane.h"
#include <stdlib.h>
#include <time.h>
#include <conio.h>   
#include <Windows.h>
#pragma comment (lib,"winmm.lib")
using namespace std;
IMAGE img[5];//IMAGE��ר�Ŵ��ͼƬ������

Node MyPlane;                   //�ҷ��ɻ��Ľڵ㴴��
LL EnemyPlane;                  //�з��ɻ���������
LL Bullet;                      //�ӵ�����Ĵ���

int num = 0;                    //��¼�л����������
int isfail = 0;                  //�ж���Ϸ�Ƿ����

//�ú궨�����涨ͼƬ�Ĵ�С
#define BGWIDTH 400               //�������
#define BGHEIGHT 600              //�����߶�
#define MyPlaneWIDYH 60           //�ҷ��ɻ����
#define MyPlaneHEIGHT 80		  //�ҷ��ɻ��߶�
#define EnemyPlaneWIDYH 50        //�з��ɻ����
#define EnemyPlaneHEIGHT 40       //�з��ɻ��߶�
#define BulletWIDYH 16            //�ӵ����
#define BulletHEIGHT 25           //�ӵ��߶�


//�ϴ�ͼƬ
void init()
{
	srand((unsigned)time(NULL));   //�����������
	//��ͼƬ�ϴ�
	loadimage(&img[0], "res\\����.jpg", BGWIDTH, BGHEIGHT);
	loadimage(&img[1], "res\\�ɻ�.jpg", MyPlaneWIDYH, MyPlaneHEIGHT);
	loadimage(&img[2], "res\\�л�.jpg",EnemyPlaneWIDYH, EnemyPlaneHEIGHT);
	loadimage(&img[3], "res\\�ӵ�.jpg", BulletWIDYH, BulletHEIGHT);

	MyPlane.x = BGWIDTH / 2 - MyPlaneWIDYH / 2;
	MyPlane.y = BGHEIGHT - MyPlaneHEIGHT - 30;
	MyPlane.speed = 10;
	MyPlane.next = NULL;

	Bullet.head = NULL;
	Bullet.head = NULL;

	EnemyPlane.head = NULL;
	EnemyPlane.rear = NULL;

	mciSendString("open res\\JustBlue.mp3", 0, 0, 0);
	mciSendString("play res\\JustBlue.mp3", 0, 0, 0);

}

//��ʼ�����溯��
void DrawMap()
{
	BeginBatchDraw();              //��ʼ��������ͼƬ

	putimage(0, 0, &img[0]);       //�ڴ��ڻ���ͼƬ
	putimage(MyPlane.x, MyPlane.y, &img[1]);

	for (Node* temp1 = EnemyPlane.head; temp1; temp1 = temp1->next)
	{
		putimage(temp1->x, temp1->y, &img[2]);
	}


	for (Node* temp2 = Bullet.head; temp2; temp2 = temp2->next)
	{
		putimage(temp2->x, temp2->y, &img[3]);
		//���������ӵ�����
	}

	TCHAR str1[50];
	sprintf(str1, "��ǰ�÷�Ϊ��%d", num);
	outtextxy(0, 0, str1);
	setbkcolor(0xffffff);
	settextcolor(RED);
	EndBatchDraw();                 //������������ͼƬ
}

//�ӵ����ɺ���
void createbullet()
{
	linklist_insert(&Bullet,
		MyPlane.x + MyPlaneWIDYH / 2 - BulletWIDYH / 2,
		MyPlane.y - BulletHEIGHT,
		10);
}

//�ӵ��ƶ�����
void move_Bullet()
{
	for (Node* temp = Bullet.head; temp; temp = temp->next)
	{
		temp->y -= temp->speed;     //���������ӵ���������ÿ���ӵ��ڵ���ƶ�λ��+speed
	}
}

//�ӵ������ٺ���
void Bullet_delete()
{
	for (Node* temp = Bullet.head; temp; temp = temp->next)
	{
		if (temp->y <= -BulletHEIGHT)
		{                            //���������ӵ���������ͷŵ�
			linklist_delete(&Bullet, temp);
			return;                  //�������Ҫreturn����Ϊtemp�Ѿ����ͷŵ��ˣ�û��ָ����      
		}
	}
}

//�ӵ����ƶ�������
void complex2()
{
	move_Bullet();              //ʵ���ӵ����ƶ�
	Bullet_delete();            //ʵ���ӵ����ͷ�   
}

//�л������ɺ���
void EnemyPlane_create()
{
	//int num = 0;
	//num = rand() % 1000;
	//if (num % 125 == 0)

	static int interval = 0;
	if (interval > 35)
	{
		linklist_insert(&EnemyPlane,
			rand() % (BGWIDTH - EnemyPlaneWIDYH) + 1,
			-EnemyPlaneHEIGHT,
			rand() % 6 +2);
		interval = 0;
	}
	interval++;
		
}

//�л����ƶ�����
void move_EnemyPlane()
{
	for (Node* temp = EnemyPlane.head; temp; temp = temp->next)
	{
		temp->y += temp->speed;
	}
}

//�л������ٺ���
void EnemyPlane_delete()
{
	for (Node* temp = EnemyPlane.head; temp; temp = temp->next)
	{
		if (temp->y >= BGHEIGHT + EnemyPlaneHEIGHT)
		{
			linklist_delete(&EnemyPlane, temp);
			return;
		}
	}
}

//�л������ɣ��ƶ�������
void complex1()
{
	EnemyPlane_create();
	move_EnemyPlane();
	EnemyPlane_delete();
}

//����Ϸ����
void playgame()
{
	if (_kbhit())                   //�жϼ����Ƿ���       
									//����Ҫ������ж������Ͳ��ᱻ_getch()��ס
	{
		switch (_getch())           //��ȡһ���ַ������ǲ��ûس���Ҳ��������ַ�
		{
		case 'W':
		case 'w':
		case 72:
			if (MyPlane.y >= 0)
				MyPlane.y -= MyPlane.speed;
			break;                  //�ж�������ַ���ʾ���Ƽ���72���ϵļ���
		case 'S':
		case 's':
		case 80:
			if (MyPlane.y <= BGHEIGHT - MyPlaneHEIGHT + 20)
				MyPlane.y += MyPlane.speed;
			break;                  //�ж�������ַ���ʾ���Ƽ���80���ϵļ���
		case 'D':
		case 'd':
		case 77:
			if (MyPlane.x <= BGWIDTH - MyPlaneWIDYH - 5)
				MyPlane.x += MyPlane.speed;
			break;                  //�ж�������ַ���ʾ���Ƽ���77���ҵļ���
		case 'a':
		case 'A':
		case 75:
			if (MyPlane.x >= 5)
				MyPlane.x -= MyPlane.speed;
			break;                  //�ж�������ַ���ʾ���Ƽ���75����ļ���
		case ' ':
			createbullet();
		}
	}
}

//�ж��ӵ��͵л��Ƿ���ײ
bool iscollision1(Node* temp1, Node* temp2)
{
	int center2x = EnemyPlaneWIDYH / 2 + temp2->x;
	int center2y = EnemyPlaneHEIGHT / 2 + temp2->y;
	int center1x = BulletWIDYH / 2 + temp1->x;
	int center1y = BulletHEIGHT / 2 + temp1->y;

	if (abs(center1x - center2x) >= (EnemyPlaneWIDYH + BulletWIDYH) / 2
		|| abs(center1y - center2y) >= (EnemyPlaneHEIGHT + BulletHEIGHT) / 2)
	{
		return false;
	}
	else
	{
		return true;
	}
	
}


//�жϵл����ҷ��ɻ��Ƿ���ײ
bool iscollision2(Node* temp1, Node* temp2)
{
	int center2x = EnemyPlaneWIDYH / 2 + temp2->x;
	int center2y = EnemyPlaneHEIGHT / 2 + temp2->y;
	int center1x = MyPlaneWIDYH / 2 + temp1->x;
	int center1y = MyPlaneHEIGHT / 2 + temp1->y;

	if (abs(center1x - center2x) >= (EnemyPlaneWIDYH + MyPlaneWIDYH) / 2
		|| abs(center1y - center2y) >= (EnemyPlaneHEIGHT + MyPlaneHEIGHT) / 2)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//�ж�����ӵ����ел������ӵ��͵л�������
void hack1()
{
	//���Կ������������ε��ཻ����
	for (Node* temp1 = Bullet.head; temp1; temp1 = temp1->next)
	{
		for (Node* temp2 = EnemyPlane.head; temp2; temp2 = temp2->next)
		{
			if (iscollision1(temp1, temp2))
			{
				linklist_delete(&Bullet, temp1);
				linklist_delete(&EnemyPlane, temp2);
				num++;
				return;
			}
		}
	}
}

void hack2()
{
	for (Node* temp = EnemyPlane.head; temp; temp = temp->next)
	{
		if (iscollision2(&MyPlane, temp))
		{
			isfail = 1;
			return;
		}
	}
}
//��ʼ��Ϸ����
void start()
{
	initgraph(BGWIDTH, BGHEIGHT);   //��ʼ������
	init();                         //����ͼƬ���ɻ�����ĳ�ʼ��
	while (1)
	{

		DrawMap();                  //�ڴ�����ͼ�����õ�ͼ
		playgame();                 //�Ӽ����϶����ƶ���Ϣ����ʼ����Ϸ
		complex2();                 //�ӵ����ƶ�������
		complex1();                 //�л������ɣ��ƶ�������
		hack1();                    //�ӵ��͵л�����ײ       
		hack2();                    //�ҷ��ɻ��͵л�����ײ
		Sleep(20);
		if (isfail)
		{
			linklist_destroy(&Bullet);
			linklist_destroy(&EnemyPlane);
			mciSendString("close res\\JustBlue.mp3", 0, 0, 0);
			TCHAR str[50];
			sprintf(str, "GAME OVER�������ֵĵ÷�Ϊ��> %d \n\t�Ƿ����¿�ʼ��Ϸ", num);
			int temp = MessageBox(GetForegroundWindow(), str, "                     ��Ϸʧ��", MB_YESNO);
			if (6 == temp)
			{
				continue;
			}
			else if (7 == temp)
			{
				break;
			}
			
		}
	}

	//	getchar();                       //ʹ����ͣ����
	closegraph();                    //�رմ���
	return;
}





