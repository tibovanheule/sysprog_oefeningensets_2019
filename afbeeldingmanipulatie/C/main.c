#include "stdio.h"
#include "image.h"
#include "matrix.h"
#include "../leaker/leaker.h"

void fill_matrix_a(matrix* m){
	m->data[0][0] = 1;
	m->data[0][1] = 0;
	m->data[0][2] = 2;
	m->data[1][0] = 0;
	m->data[1][1] = 3;
	m->data[1][2] = 1;
}

void fill_matrix_b(matrix* m){
	m->data[0][0] = 0;
	m->data[0][1] = 3;
	m->data[1][0] = 2;
	m->data[1][1] = 1;
	m->data[2][0] = 0;
	m->data[2][1] = 4;
}

/* GEGEVEN IN OPGAVE */
void ex_1_matrix_operations(){
	matrix a,b,c;

	/* init a(2,3) and fill with elements */
	init_matrix(&a,2,3);
	fill_matrix_a(&a);

	/* init b (default) and fill with elements */
	init_matrix_default(&b);
	fill_matrix_b(&b);

	/* c = a * b */
	multiply_matrices(&a, &b, &c);

	/* c = c' */
	transpose_matrix_pa(&c);

	/* free matrix a and b for reuse */
	free_matrix(&a);
	free_matrix(&b);

	/* create unity matrix */
	init_identity_matrix(&a,2);

	/* b = c * a */
	multiply_matrices(&c, &a, &b);

	/* expand b to (3,4) */
	dynamic_expand(&b,3,4);

	/* print result b */
	print_matrix(&b);

	/* free all resources */
	free_matrix(&a);
	free_matrix(&b);
	free_matrix(&c);
}

void edge_detection(void){
	//TODO
}

void gaussian_blur(void){
	//TODO
}

/* GEGEVEN IN OPGAVE */
int main(void){
	/* ex1: blur */
	gaussian_blur();

	/* ex2: edge detection */
	edge_detection();

	printf("done\n");
	return 0;
}
