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

### vector

同样存在一个常量宏`INIT_NUM`，它表示vector的初始大小。我们的结构体`vector`的代码如下。
```c
struct vector {
	int *data;
	int length, capacity;
};
```

对于函数`initVector`，第一次使用函数`malloc`是为结构体`vector`分配内存，第二次则是为其中的成员`data`，也就是指向实际的顺序表分配内存。这里，我们同样为了简便起见，在vector中使用`int`作为元素类型。完成`malloc`之后，设置结构体`vector`中的成员`length`和`capacity`，然后返回即可。
对于函数`pushbackVector`和`popbackVector`，其意思是明确的，就是在vector的尾部进行“增删”操作。对于顺序表而言，尾部的“增删”操作开销是很低的。在函数`pushbackVector`中，我们需要考虑当vector的容量不够时需对其进行扩容。扩容的条件是**容量与长度之差小于`INIT_NUM/2`**。扩容使用的是C语言的库函数`realloc`。
> 这里稍微值得关注函数`realloc`的语义。

函数`insertVector`和`eraseVector`都有一个参数`idx`，其表示插入和删除的位置。显然在顺序表中插入和删除需要挪动之后的元素。
函数`destroyVector`主要是调用函数`free`，意思也是很明确的。

### linked list

有两个结构体`LinkedListNode`和`LinkedList`，前者对应双向循环链表中的一个结点，后者对应整个双向循环链表。结构体`LinkedList`中的成员`size`表示链表中结点的个数，而成员`head`指向链表的队头。但是，当链表为空时，应该将`head`置为`NULL`，而`size`赋值为`0`。
由于链表不适合随机访问，所以不提供相关接口。