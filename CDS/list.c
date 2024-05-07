#include <stdio.h>

#include <stdlib.h>
#include <assert.h>

/* 例程：用数组实现的（循环）队列，数组必须要浪费一个元素。程序仅作参考。 */
#define QUEUE_MAXN 6 /* user-defined */
struct queue {
	int data[QUEUE_MAXN];
	int head, tail;
};
struct queue *initQueue() {
	struct queue *q = (struct queue *)malloc(sizeof(struct queue));
	assert(q != NULL);
	q->head = 0;
	q->tail = 0;
	return q;
}
int sizeQueue(struct queue *q) {
	return (q->tail - q->head + QUEUE_MAXN) % QUEUE_MAXN;
}
void pushQueue(struct queue *q, int e) {
	assert(sizeQueue(q) != QUEUE_MAXN - 1); /* not full */
	q->data[q->tail] = e;
	q->tail = (q->tail + 1) % QUEUE_MAXN;
}
void popQueue(struct queue *q) {
	assert(q->tail != q->head); /* not empty */
	q->head = (q->head + 1) % QUEUE_MAXN;
}
int frontQueue(struct queue *q) {
	assert(q->tail != q->head);
	return q->data[q->head];
}
int backQueue(struct queue *q) {
	assert(q->tail != q->head);
	return (q->tail!=0) ? q->data[q->tail-1] : q->data[QUEUE_MAXN-1];
}
void destroyQueue(struct queue *q) { free(q); q = NULL; }


/* 例程：用数组实现的栈。程序仅作参考。 */
#define STACK_MAXN 6 /* user-defined */
struct stack {
	int data[QUEUE_MAXN];
	int top;
};
struct stack *initStack() {
	struct stack *s = (struct stack *)malloc(sizeof(struct stack));
	assert(s != NULL);
	s->top = -1;
	return s;
}
int sizeStack(struct stack *s) { return s->top + 1; }
void pushStack(struct stack *s, int e) {
	assert(s->top + 1 != STACK_MAXN);
	s->top++;
	s->data[s->top] = e;
}
int topStack(struct stack *s) {
	assert(s->top != -1);
	return s->data[s->top];
}
void popStack(struct stack *s) {
	assert(s->top != -1);
	s->top--;
}
void destroyStack(struct stack *s) { free(s); s = NULL; }

/* 例程 */
#define INIT_NUM 58 /* user-defined */
struct vector {
	int *data;
	int length, capacity;
};
struct vector *initVector() {
	struct vector *v = (struct vector *)malloc(sizeof(struct vector));
	assert(v != NULL);
	v->data = (int *)malloc(sizeof(int) * INIT_NUM);
	assert(v->data != NULL);
	v->length = 0;
	v->capacity = INIT_NUM;
	return v;
}
void pushbackVector(struct vector *v, int data) {
	if (v->capacity - v->length < INIT_NUM / 2) {
		// grow
	}
	*(v->data + v->length) = data;
	v->length++;
}
void popbackVector(struct vector *v) { v->length--; }
int atVector(struct vector *v, int idx) {
	assert(idx >= 0 && idx < v->length);
	return *(v->data + idx);
}
void insertVector(struct vector *v, int e, int idx) {
	if (v->capacity - v->length < INIT_NUM / 2) {
		// grow
	}
	int ptr1 = v->length;
	int ptr2 = ptr1 - 1;
	while (ptr2 >= idx) {
		*(v->data + ptr1) = *(v->data + ptr2);
		ptr1--; ptr2--;
	}
	*(v->data + ptr1) = e;
	v->length++;
}
void eraseVector(struct vector *v, int idx) {
	int ptr1 = idx;
	int ptr2 = ptr1 + 1;
	while (ptr2 < v->length) {
		*(v->data + ptr1) = *(v->data + ptr2);
		ptr1++; ptr2++;
	}
	v->length--;
}
void destroyVector(struct vector *v) {
	free(v->data); v->data = NULL;
	free(v); v = NULL;
}

int main() {
	struct queue *q = initQueue();
	pushQueue(q, 99);
	printf("%d %d %d\n", sizeQueue(q), frontQueue(q), backQueue(q));
	popQueue(q);
	printf("%d\n", sizeQueue(q));
	destroyQueue(q);

	struct stack *s = initStack();
	pushStack(s, 77);
	printf("%d %d\n", sizeStack(s), topStack(s));
	popStack(s);
	printf("%d\n", sizeStack(s));
	destroyStack(s);
}