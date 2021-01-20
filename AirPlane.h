#pragma once
#ifndef AIRPLANE
#define AIRPLANE 1

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <cmath>
using namespace std;


typedef struct Node
{
	int x;
	int y;
	int speed;
	Node *next;
}Node;

typedef struct Linklist
{
	Node *head;
	Node *rear;         
}LL;

//��������,�����������г�ʼ���ڵ㣬������ֻ��һ���ڵ�
Node* linklist_init(int x,int y,int speed)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	assert(temp);
	temp->x = x;
	temp->y = y;
	temp->speed = speed;
	temp->next = NULL;
	return temp;
}

//�ڵ��������
//β�巨
void linklist_insert(LL* linklist , int x ,int y ,int speed)
{
	assert(linklist);
	
	if (NULL == linklist->head)
	{
		linklist->head = linklist_init(x, y, speed);
		linklist->rear = linklist->head;
	}
	else
	{
		linklist->rear->next = linklist_init(x, y, speed);
		linklist->rear = linklist->rear->next;
	}
}

//����ڵ�ɾ������
void linklist_delete(LL* linklist, Node* p)
{
	assert(linklist || linklist->head);
	if (p == linklist->head)
	{
		linklist->head = p->next;
		free(p);
		p = NULL;
	}
	else
	{
		for (Node* temp = linklist->head; temp; temp = temp->next)
		{
			if (p == temp->next)
			{
				if (p == linklist->rear)
				{
					linklist->rear = temp;
					free(temp->next);
					temp->next = NULL;
					return;
				}
				else
				{
					temp->next = p->next;
					free(p);
					p = NULL;
					return;
				}
				
			}
		}
	}
}

//��������Ĵݻ�
void linklist_destroy(LL* linklist)
{
	assert(linklist);
	Node* temp1 = linklist->head;
	while (temp1)
	{
		Node* temp2 = temp1; 
		temp1 = temp1->next;
		free(temp2);
	}
	linklist->head = linklist->rear = NULL;
}


#endif // !AIRPLANE
