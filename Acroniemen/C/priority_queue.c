#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../leaker/leaker.h"
#include "priority_queue.h"

int memory_null_check(void* toCheck){
	if (toCheck==NULL)
		return 1;
	return 0;
}

priority_queue* pq_create(){
	priority_queue *queue =(priority_queue *)malloc(sizeof(priority_queue));
	if(memory_null_check(queue)){
		printf("Something went wrong while trying to make a queue");
		exit(1);
	}
	queue->size=0;
	queue->max_size=QUEUE_SIZE;
	queue->items = malloc(QUEUE_SIZE*sizeof(queue_item));
	if(memory_null_check(queue->items)){
		printf("Something went wrong while trying to make a queue-items");
		exit(1);
	}
	return queue;
}

void pq_free_item(queue_item item){
	char* acro = item.acroniem;
	if(acro!=NULL)
		free(acro);
}

void pq_free(priority_queue* queue){
	for(int i=0; i < queue->size;i++)
		pq_free_item(queue->items[i]);
	free(queue->items);
	free(queue);
}

void pq_swap(queue_item* item1,queue_item* item2){
	queue_item temp = *item1;
	*item1 = *item2;
	*item2 = temp;
}

void pq_fixup(priority_queue* queue,queue_item* item, int index){
	if(index>0){
		queue_item* parent = queue->items+(index+1)/2-1;
		if(item->priority>parent->priority){
			pq_swap(parent,item);
			pq_fixup(queue,parent,index/2);
		}
	}
}

int pq_add(priority_queue* queue,char* acroniem,int priority){
	int unique=1;
	if(queue->size==queue->max_size){
		//uitbreiden
		queue->max_size*=2;
		queue->items = (queue_item*)realloc(queue->items, sizeof(queue_item)*queue->max_size);
		if(memory_null_check(queue->items)){
			printf("Something went wrong realocating the items, sorry");
			exit(1);
		}
	}
	for(unsigned int i=0;i<queue->size;i++)
		if(!strcmp(acroniem,queue->items[i].acroniem)){
			unique=0;
			break;
		}
	if(unique){
		queue_item it;
		it.acroniem=acroniem;
		it.priority=priority;
		queue->items[queue->size] = it;
		pq_fixup(queue,&(queue->items[queue->size]),queue->size);
		queue->size++;
	}
	return unique;
}


void pq_print(priority_queue* queue){
	for(unsigned int i=0;i<queue->size;i++){
		printf(" %4s : %u \n",queue->items[i].acroniem,queue->items[i].priority); //%4s format string tuned to this solution, remove the 4 for generic solution
	}
}

char* pq_max(priority_queue* queue){
	char* retVal = NULL;
	if(queue->size>0){

	}
	return retVal;
}
