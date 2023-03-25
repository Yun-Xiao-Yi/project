#define _CRT_SECURE_NO_WARNINGS 1
#include "Queue.h"
#include"rank.h"
#include"user.h"
#include"stdbool.h"

void QueueInit(Queue* pq)
{
	assert(pq);
	pq->head = pq->tail = NULL;
	pq->size = 0;
}

void QueueDestroy(Queue* pq)
{
	assert(pq);
	QNode* cur = pq->head;
	while (cur)
	{
		QNode* del = cur;
		cur = cur->next;
		free(del);
	}

	pq->head = pq->tail = NULL;
}

void QueuePush(Queue* pq, QDataType x)
{
	assert(pq);

	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		exit(-1);
	}
	else
	{
		newnode->data = x;
		newnode->next = NULL;
	}

	if (pq->tail == NULL)
	{
		pq->head = pq->tail = newnode;
	}
	else
	{
		pq->tail->next = newnode;
		pq->tail = newnode;
	}

	pq->size++;
}

void QueuePop(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));

	if (pq->head->next == NULL)
	{
		free(pq->head);
		pq->head = pq->tail = NULL;
	}
	else
	{
		QNode* del = pq->head;
		pq->head = pq->head->next;

		free(del);
		del = NULL;
	}

	pq->size--;
}

QDataType QueueFront(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));

	return pq->head->data;
}

QDataType QueueBack(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));

	return pq->tail->data;
}

bool QueueEmpty(Queue* pq)
{
	assert(pq);

	return pq->head == NULL && pq->tail == NULL;
}

int QueueSize(Queue* pq)
{
	assert(pq);
	/*QNode* cur = pq->head;
	int n = 0;
	while (cur)
	{
		++n;
		cur = cur->next;
	}

	return n;*/
	return pq->size;
}