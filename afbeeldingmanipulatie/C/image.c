#include "stdio.h"
#include "image.h"
#include "stdlib.h"
#include "math.h"
#include "../leaker/leaker.h"

double mmin(double a, double b){
	return (a < b)?a:b;
}

double mmax(double a, double b){
	return (a > b)?a:b;
}

/* GEGEVEN IN OPGAVE */
double RGB_to_linear(double x) {
	return (x < 0.04045)?(x / 12.92):(pow((x+0.055) / 1.055, 2.4));
}

/* GEGEVEN IN OPGAVE */
double linear_to_RGB(double y) {
	return (y <= 0.0031308)?(12.92 * y):(1.055 * pow(y, 1/2.4) - 0.055);
}

void color_borders_black(image* im){
	/* Color borders black */
	for(int y = 0; y < 3; y++){
		for(int x = 0; x < im->width; x++){
			im->data[x][0][y] = (unsigned char) 0;
		}
		for(int x = 0; x < im->height; x++){
			im->data[0][x][y] = (unsigned char) 0;
		}
		for(int x = 0; x < im->width; x++){
			im->data[x][im->height-1][y] = (unsigned char) 0;
		}
		for(int x = 0; x < im->height; x++){
			im->data[im->width-1][x][y] = (unsigned char) 0;
		}
	}
}

/* GEGEVEN IN OPGAVE */
void RGB_to_gray(image* im){
	for(int x = 0; x < im->width; x++){
		for(int y = 0; y < im->height; y++){
			double R_linear = RGB_to_linear((double)(im->data[x][y][0])/255.0);
			double G_linear = RGB_to_linear((double)(im->data[x][y][1])/255.0);
			double B_linear = RGB_to_linear((double)(im->data[x][y][2])/255.0);
			double gray_linear = 0.299 * R_linear + 0.587 * G_linear + 0.114 * B_linear;
			int gray = (int)floor(linear_to_RGB(gray_linear)*255.0);

			im->data[x][y][0] = (unsigned char)gray;
			im->data[x][y][1] = (unsigned char)gray;
			im->data[x][y][2] = (unsigned char)gray;
		}
	}
}

/* GEGEVEN IN OPGAVE */
void load_image(image* im, char* file_name){
	int i,j;
	char kar[1];
	FILE * pFile;

	/* Open file */
	pFile = fopen(file_name, "rb");
	if (pFile == NULL) {
		printf("error opening file %s\n", file_name);
		exit(-1);
	}

	/* Skip first header line */
	*kar = 0x00;
	while (*kar != 0x0a) {
		fread(kar, 1, 1, pFile);
	}

	/* Read first char, if # skip comment line */
	fread(kar, 1, 1, pFile);
	while (*kar == 0x23 ) {
		fread(kar, 1, 1, pFile);
		while (*kar != 0x0a) {
			fread(kar, 1, 1, pFile);
		}
		fread(kar, 1, 1, pFile);
	}

	/* Skip 2nd header line */
	while (*kar != 0x0a) {
		fread(kar, 1, 1, pFile);
	}

	/* Skip 3rd header line */
	fread(kar, 1, 1, pFile);
	while (*kar != 0x0a) {
		fread(kar, 1, 1, pFile);
	}

	for (j = 0; j < im->height; j++) {
		for (i = 0; i < im->width; i++) {
			fread(im->data[i][j], 1, 3, pFile);
		}
	}

	fclose(pFile);
}

/* GEGEVEN IN OPGAVE */
void save_image(image* im, char* file_name){
	int i,j;
	FILE * pFile;


	/* Open file */
	pFile = fopen(file_name, "wb");
	if (pFile == NULL) {
		printf("error opening file %s\n", file_name);
		exit(-1);
	}

	/* Write header */
	fprintf(pFile, "P6\n# Created by IrfanView\n%d %d\n255\n", im->width, im->height);

	/* Write pixel data */
	for (j = 0; j < im->height; j++){
		for (i = 0; i < im->width; i++){
			fwrite(im->data[i][j], 1, 3, pFile);
		}
	}

	/* Close file */
	fclose(pFile);
}
void memory_null_check(void* data){
	if(data == NULL){
		printf(MEMORY_ERROR_MSG);
		exit(0);
	}
}

void init_image(image* im, int width, int height){
	im->width = width;
	im->height = height;
	im->data = (unsigned char ***) malloc(sizeof(unsigned char**)*width);
	memory_null_check(im->data);
	for(int i =0; i<width;i++){
		im->data[i] = malloc(sizeof(unsigned char **)*height);
		memory_null_check(im->data[i]);
		for(int j = 0; j< height;i++){
			im->data[i][j] = malloc(sizeof(unsigned char*)*3);
			memory_null_check(im->data[i][j]);
		}
	}
}
void free_image(image* im){
	for(int i =0; i<im->width;i++){
		for(int j = 0; j< im->height;i++){
						free(im->data[i][j]);
		}
			free(im->data[i]);
	}
		free(im->data);

}

int*** alloc_data(int width, int height){
	int x,y;
	/* Init aid structure to copy gradients into. */
	int*** data2 = (int***) malloc(sizeof(int**)*(width));
	memory_null_check(data2);
	for(x = 0; x < (width); x++){
		data2[x] = (int**) malloc(sizeof(int*)*(height));
		memory_null_check(data2[x]);
		for(y = 0; y < (height); y++){
			data2[x][y] = (int*) malloc(sizeof(int)*3);
			memory_null_check(data2[x][y]);
		}
	}
	return data2;
}

void free_data(int*** data, int width, int height){
	int x,y;
	/* Free aid structure. */
	for(x = 0; x < width; x++){
		for(y = 0; y < height; y++){
			free(data[x][y]);
		}
		free(data[x]);
	}
	free(data);
}

void sobel_operator(image* im){
	int Gmax = 0;

	/*  Sobel operators. */
	const int sobel_x[3][3] = 
	{{ 1,   0,  -1},
	{ 2,   0,  -2},
	{ 1,   0,  -1}};
	const int sobel_y[3][3] = 
	{{ 1,   2,   1},
	{ 0,   0,   0},
	{-1,  -2,  -1}};

	int*** data2 = alloc_data(im->width, im->height);

	for(int x = 1; x < im->width-1; x++){
		for(int y = 1; y < im->height-1; y++){
			int Gx = 0,Gy = 0,G;
			for(int i = -1; i <= 1; i++){
				for(int j = -1; j <= 1; j++){
					Gx += ((int)im->data[x+i][y+j][0]) * sobel_x[i+1][j+1];
					Gy += ((int)im->data[x+i][y+j][0]) * sobel_y[i+1][j+1];
				}
			}

			G = (int) floor(sqrt((Gx*Gx + Gy*Gy)*1.0));
			if(G > Gmax){
				Gmax = G;
			}

			data2[x][y][0] = G;
			data2[x][y][1] = G;
			data2[x][y][2] = G;
		}
	}

	/* Copy aid structure data into image. */
	for(int x = 1; x < im->width-1; x++){
		for(int y = 1; y < im->height-1; y++){
			int G = data2[x][y][0];
			G = (int) floor(G*255.0/Gmax);
			if(G < EDGE_THRESHOLD){
				G = 0;
			}
			im->data[x][y][0] = (unsigned char) G;
			im->data[x][y][1] = (unsigned char) G;
			im->data[x][y][2] = (unsigned char) G;
		}
	}

	/* Free aid data structure. */
	free_data(data2, im->width, im->height);

	/* Color image borders black. */
	color_borders_black(im);

}

void blur_picture(image* im, int radius){
	/* Alloc aid data structure. */
	int*** data2 = alloc_data(im->width, im->height);

	double d = sqrt(PI*2);
	double sigma = radius*radius;

	for(int x = 0; x < im->width; x++){
		for(int y = 0; y < im->height; y++){
			double val[3] = {0,0,0};
			double wsum = 0;
			for(int i = -radius; i <= radius; i++){
				for(int j = -radius; j <= radius; j++){
					int k = (int) mmin(im->width-1, mmax(0, i+x));
					int l = (int) mmin(im->height-1, mmax(0, j+y));
					double m = i*i + j*j;
					double w = exp(-m / (2*sigma)) / (d*sigma);
					val[0] += im->data[k][l][0] * w;
					val[1] += im->data[k][l][1] * w;
					val[2] += im->data[k][l][2] * w;
					wsum += w;
				}
			}
			data2[x][y][0] = (int) floor(val[0]/wsum);
			data2[x][y][1] = (int) floor(val[1]/wsum);
			data2[x][y][2] = (int) floor(val[2]/wsum);

		}
	}

	for(int x = 0; x < im->width; x++){
		for( int y = 0; y < im->height; y++){
			im->data[x][y][0] = (unsigned char) data2[x][y][0];
			im->data[x][y][1] = (unsigned char) data2[x][y][1];
			im->data[x][y][2] = (unsigned char) data2[x][y][2];
		}
	}

	free_data(data2, im->width, im->height);

}

