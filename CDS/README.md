# CDS

Use C programming language to write some sample code about Data Structure.

## list

### queue

首先是关于常量宏`QUEUE_MAXN`，我想在下面关于结构体`queue`的代码中很清晰地体现它的意思。为了简单起见，队列中的元素类型直接使用`int`，队列中的数据皆放在结构体`queue`的数组成员`data`中。结构体`queue`中成员`head`和`tail`的意义也是明显的。
```c
struct queue {
	int data[QUEUE_MAXN];
	int head, tail;
};
```
下面是针对队列的操作，这些函数的意义都是较为明显的，实现也是较为简单的，具体去阅读相应的代码，不在此处赘述了。
```c
struct queue *initQueue();
int sizeQueue(struct queue *q);
void pushQueue(struct queue *q, int e);
void popQueue(struct queue *q);
int frontQueue(struct queue *q);
int backQueue(struct queue *q);
void destroyQueue(struct queue *q);
```


### stack

stack和queue的实现方式基本相似，故不赘述。