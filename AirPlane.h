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

//创建链表,就是在链表中初始化节点，链表中只有一个节点
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

//节点插入链表
//尾插法
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

//链表节点删除函数
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

//整条链表的摧毁
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
