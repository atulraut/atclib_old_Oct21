/*
* Aim : Simple Queue
* Date : Friday, Oct 21 2016
* San Diego, CA
* By : Atul R. Raut
* Q->[FIFO] : First In First Out
***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 2

typedef struct _q {
  int rear;
  int front;
  int *buf;
} queue;

queue *m_init (void *_ptr, int size) {
  queue *q = (queue *)_ptr;
  if(NULL == q) {
	printf ("memset needs valid pointer \n");
	exit(1);
  }
  memset((void *)q, 0, sizeof(queue));
  q->rear = -1;
  q->front= -1;
  q->buf = (int *) malloc (size * sizeof(int));
  if (NULL == q->buf)
    return;
  else
    return q;
}


int is_Empty(void *_ptr) {
  queue *q = (queue *)_ptr;
  if (q->front == -1) {
    printf ("[m_remove] Empty \n");
    return 1;
  } else
      return -1;
}

int is_Full(void *_ptr) {
  queue *q = (queue *)_ptr;
  if (q->rear == MAX-1)
    return 1;
  else
    return -1;
}

int m_insert (void *_ptr, int val) {
  queue *q = (queue *)_ptr;
  if (q->rear == MAX-1) {
    printf ("[m_insert] Quque is FULL \n");
    return -1;
  }
  if (q->front == -1 && q->rear == -1) {
    q->front = q->rear = 0;
  } else {
    q->rear = q->rear + 1;
  }
  printf ("[m_insert] val=%d added at q->rear=%d \n", val, q->rear);
  q->buf[q->rear] = val;
}

int m_remove (void *_ptr) {
  int val;
  queue *q = (queue *)_ptr;
  if (q->front == -1 || q->front > q->rear)
    printf ("[m_remove] Empty \n");
  else {
    val = q->buf[q->front];
    printf ("[m_remvoe] val = %d at q->front = %d\n",val, q->front);
    q->front = q->front + 1;
    return val;
  }
}

int m_display (void *_ptr) {
  int i;
  queue *q = (queue *)_ptr;
  printf ("[m_display] q->rear = %d  q->front =%d\n", q->rear, q->front);
  if (q->front == -1 || q->front > q->rear) {
    printf ("[m_remove] Empty \n");
    return;
  }
  for (i=q->front; i<q->rear+1; i++) {
    printf ("[m_display] q->buf[%d] = %d \n",i, q->buf[i]);
  }
}

int main () {
  int i, j;
  j = 0;
  queue q, *qptr;
  qptr  = m_init(&q, MAX);
  if (NULL == qptr)
    return -1;
  printf ("[q_main] rear=%d, front=%d\n", qptr->rear, qptr->front);
  for (i=0; i<MAX; i++) {
    j = i + 1;
    m_insert(qptr, j);
  }
  m_display(qptr);
  j =  m_remove(qptr);
  printf ("[m_main] remove val = %d \n", j);
  m_display(qptr);
  j =  m_remove(qptr);
  printf ("[m_main] remove val = %d \n", j);
  m_display(qptr);
  m_insert(qptr, j);
  m_display(qptr);
}

/**
   => ./a.out
   [q_main] rear=-1, front=-1
   [m_insert] val=1 added at q->rear=0
   [m_insert] val=2 added at q->rear=1
   [m_display] q->rear = 1  q->front =0
   [m_display] q->buf[0] = 1
   [m_display] q->buf[1] = 2
   [m_remvoe] val = 1 at q->front = 0
   [m_main] remove val = 1
   [m_display] q->rear = 1  q->front =1
   [m_display] q->buf[1] = 2
   [m_remvoe] val = 2 at q->front = 1
   [m_main] remove val = 2
   [m_display] q->rear = 1  q->front =2
   [m_remove] Empty
   [m_insert] Quque is FULL
   [m_display] q->rear = 1  q->front =2
   [m_remove] Empty
**/
