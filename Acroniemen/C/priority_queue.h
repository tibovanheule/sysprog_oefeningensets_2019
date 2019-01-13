#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

#define QUEUE_SIZE 1

typedef struct{
	char* acroniem;
	unsigned int priority;
} queue_item;

typedef struct{
	queue_item* items;
	unsigned int size;
	unsigned int max_size;
}priority_queue;

priority_queue* pq_create();
void pq_free(priority_queue* queue);
void pq_swap(queue_item* item1,queue_item* item2);
void pq_fixup(priority_queue* queue,queue_item* item, int index);
int pq_add(priority_queue* queue,char* acroniem,int priority);
void pq_print(priority_queue* queue);
char* pq_max(priority_queue* queue);

#endif