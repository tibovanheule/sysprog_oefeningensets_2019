#ifndef _IMAGE
#define _IMAGE

#define EDGE_THRESHOLD 50

#define PI 3.14
#define MEMORY_ERROR_MSG "memory error\n"

/* Image data: 3D data: width*height*3. */
typedef struct {
	int width;
	int height;
	unsigned char*** data;
} image;

/* Check if data is null */
void memory_null_check(void* data);

/* Calculate min/max. */
double mmax(double a, double b);
double mmin(double a, double b);

/* Blur picture. */
void blur_picture(image* im, int radius);

/* Color borders black. */
void color_borders_black(image* im);

/* Convert between RGB and grayscale. */
double RGB_to_linear(double x);
double linear_to_RGB(double y);

/* Convert image to grayscale. */
void RGB_to_gray(image* im);

/* Free image memory. */
void free_image(image* im);

/* Edge detection: run Sobel operator in image. */
void sobel_operator(image* im);

/* Initialize image data. */
void init_image(image* im, int width, int height);

/* Load image from file ppm file. */
void load_image(image* im, char* file_name);

/* Save image to ppm file. */
void save_image(image* im, char* file_name);

#endif