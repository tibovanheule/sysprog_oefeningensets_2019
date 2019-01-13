#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "../leaker/leaker.h"

void init_matrix(matrix* m, int num_rows, int num_cols) {
	m->num_cols =num_cols;
	m->num_rows =num_rows;
	m->data =(int**) malloc(sizeof(int*)*num_rows);
	if (m->data != NULL) {
		for (int i = 0; i < num_rows; i++) {
			m->data[i] = (int*)calloc(num_cols, sizeof(int));
		}
	}	else {
		printf("Allocation failed, insufficient memory?\n");
		exit(1);
	} 
}

void init_matrix_default(matrix* m){
	init_matrix(m,DEFAULT_MATRIX_NUM_ROWS,DEFAULT_MATRIX_NUM_COLS);
}

void init_identity_matrix(matrix* m, int dimension){
	init_matrix(m,dimension,dimension);
	for(int i = 0; i<dimension;i++){
		m->data[i][i]=1;
	}
}

void free_matrix(matrix* m){
	for(int i = 0; i<m->num_rows;i++){
		free(m->data[i]);
	}
	free(m->data);
}

void print_matrix(matrix* m){
	for(int i = 0; i<m->num_rows; i++){
		for(int j=0; j<m->num_cols; j++){
			printf("%3d ",m->data[i][j]);
		}
		printf("\n");
	}
}

void transpose_matrix_pa(matrix* m){
	for(int i = 0; i<m->num_rows; i++){
		for(int j=i; j<m->num_cols; j++){
			int tmp = *(*(m->data+i)+j);
			*(*(m->data+i)+j)= *(*(m->data+j)+i);
			*(*(m->data+j)+i) = tmp;
		}
	}
}

void transpose_matrix_sn(matrix* m){
	for(int i = 0; i<m->num_rows; i++){
		for(int j=i; j<m->num_cols; j++){
			int tmp = m->data[i][j];
			m->data[i][j]= m->data[j][i];
			m->data[j][i] = tmp;
		}
	}
}

void multiply_matrices(matrix* a, matrix* b, matrix* result){
	if(a->num_cols==b->num_rows){
		init_matrix(result, a->num_rows, b->num_cols); 
		for(int i = 0; i<result->num_rows; i++){
			for(int j=0; j<result->num_cols; j++){
				for(int k = 0; k<a->num_cols;k++){
					result->data[i][j] += a->data[i][k] * b->data[k][j];
				}
			}
		}
	}
}

void dynamic_expand(matrix* m, int new_num_rows, int new_num_cols){
	if(m->num_rows<new_num_rows&&m->num_cols<new_num_cols){
		m->data = (int**) realloc(m->data, new_num_rows*sizeof(int*));
		if (m->data != NULL) {
			for (int i = 0; i < m->num_rows; i++) {
				m->data[i] = (int*)realloc(m->data[i], new_num_cols*sizeof(int));
				for (int j = m->num_cols; j < new_num_cols; j++) {
					m->data[i][j] = 0;
				}
			}
			for (int i = m->num_rows; i < new_num_rows; i++) {
				m->data[i] = (int*)calloc(new_num_cols, sizeof(int));
				if (m->data[i] == NULL) {
					printf("Allocation faled\n");
					exit(1);
				}
			}

			m->num_cols = new_num_cols;
			m->num_rows = new_num_rows;
		}
		else {
			printf("reallocation faile\n");
			exit(1);
		}
	}
}
