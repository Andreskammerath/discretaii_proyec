#include <stdio.h>
#include <stdlib.h>

void init(Queue *q) {
	q->front = NULL;
	q->last = NULL;
	q->size = 0;
}
 
int front(Queue *q) {
	return q->front->data;
}
 
void pop(Queue *q) {
	if(!q->size)
	{
		q->size--;	 
		struct Node *tmp = q->front;
		q->front = q->front->next;
		free(tmp);
	}

}
u32 empty(Queue* q)
{
	return q->size;
}
void push(Queue *q, u32 data) {
	q->size++;
 
	if (q->front == NULL) {
		q->front = (struct Node *) malloc(sizeof(struct Node));
		q->front->data = data;
		q->front->next = NULL;
		q->last = q->front;
	} else {
		q->last->next = (struct Node *) malloc(sizeof(struct Node));
		q->last->next->data = data;
		q->last->next->next = NULL;
		q->last = q->last->next;
	}
}
/* 
// Driver code.
int main(void) {
	Queue q;
	init(&q);
	push(&q, 1);
	push(&q, 2);
	printf("%d\n", front(&q));
	pop(&q);
	printf("%d\n", front(&q));
}*/