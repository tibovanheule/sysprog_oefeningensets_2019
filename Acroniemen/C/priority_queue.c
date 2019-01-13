#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../leaker/leaker.h"
#include "priority_queue.h"

priority_queue* pq_create(){
	priority_queue* queue = (priority_queue*) malloc(sizeof(priority_queue));
	if(queue==NULL){
		printf("error creating priority queque");
		exit(1);
	}
	queue->items = (queue_item*) malloc(QUEUE_SIZE*sizeof(queue_item));
	if(queue==NULL){
		printf("error creating priority queque items");
		exit(1);
	}
	queue->max_size = QUEUE_SIZE;
	queue->size = 0;
	return queue;
}

void pq_free_item(queue_item item){
	char* acroniem=item.acroniem;
	if(acroniem!=NULL){
		free(acroniem);
	}
}

void pq_free(priority_queue* queue){
	for(unsigned int i=0;i<queue->size;i++){
		pq_free_item(queue->items[i]);
	}
	free(queue->items);
	free(queue);
}

void pq_swap(queue_item* item1,queue_item* item2){
	int priority1 = item1->priority;
	char* acroniem1 = (char*) malloc(strlen(item1->acroniem)+1);
	strcpy(acroniem1,item1->acroniem);
	item1->acroniem = item2->acroniem;
	item1->priority = item2->priority;
	item2->acroniem =acroniem1;
	item2->priority = priority1;
	free(acroniem1);
	/* shorter is possible
	 queue_item copy = *item2;
	*item2=*item1;
	*item1=copy;
	*/
}

void pq_fixup(priority_queue* queue,queue_item* item, int index){
	if(index>0){
		int priority = item->priority;
		queue_item* voorvader = &queue->items[index/2];
		if(voorvader->priority<priority){
			pq_swap(item,voorvader);
			pq_fixup(queue,voorvader,index/2);
		}
	}
}

int pq_add(priority_queue* queue,char* acroniem,int priority){
	
	if(queue->size==queue->max_size){
		int length = queue->max_size*2*sizeof(queue_item);
		queue->max_size = length;
		queue->items = realloc(queue->items,length);
	} 
	if(queue->items==NULL){
		printf("error: couldn't accollate items queque");
		exit(1);
	}
	int uniq =1;
	for(int i =0; i< queue->size;i++){
		if (queue->items[i].acroniem == acroniem){
				uniq =0;
		}
	}
	if(uniq){
		queue->size++;
		queue_item item;
		item.acroniem =acroniem;
		item.priority = priority; 
		queue->items[queue->size-1]= item;
		pq_fixup(queue,&queue->items[queue->size-1],queue->size-1);
		return 1;
	}
	return 0;
}


void pq_print(priority_queue* queue){

	for(unsigned int i=0;i<queue->size;i++){
		printf(" %4s : %u \n",queue->items[i].acroniem,queue->items[i].priority); //%4s format string tuned to this solution, remove the 4 for generic solution
	}
}

char* pq_max(priority_queue* queue){
	if(0<queue->size){
		return queue->items[0].acroniem;
	}
		return NULL;
	
}
