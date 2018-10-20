/*
	Original Image structure and bitmap handling functions created by Ivan Cukic.
	I translated it to English and adapted it for my program.
*/

#ifndef _H_TEXTURES_H_
#define _H_TEXTURES_H_

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>


/* Structs representing bitmap headers */
typedef struct {
	unsigned short	type;
	unsigned int	size;
	unsigned short	reserved1;
	unsigned short	reserved2;
	unsigned int	offsetbits;
} BITMAPFILEHEADER;

typedef struct {
	int         	xpelspermeter;
	int         	ypelspermeter;
	unsigned int	size;
	unsigned int	width;
	unsigned int	height;
	unsigned int	compression;
	unsigned int	sizeimage;
	unsigned int	colorsused;
	unsigned int	colorsimportant;
	unsigned short	planes;
	unsigned short	bitcount;
} BITMAPINFOHEADER;

/* Image data struct */
typedef struct Image {
	int 	width, height;
	char	*pixels;
} Image;


/* There are 6 sides of unit cube */
#define SIDES_N	6

/* Positions of unit cube textures in texture array */
#define WHITE	0
#define RED 	1
#define GREEN	2
#define BLUE	3
#define YELLOW	4
#define ORANGE	5


/* Saving background texture pointer here */
extern GLuint bg_tex_ptr;

/* Saving unit cube side texture pointers here */
extern GLuint side_tex_ptr[SIDES_N];


/* Initializes Image structure and returns pointer to it */
Image *image_init(int width, int height);

/* Frees space pointed to by image */
void image_free(Image *image);

/* Loads image data from file */
void image_read(Image *image, char *filename);

/* Loads background texture from file */
void load_background_texture(char *filename);

/* Loads unit cube textures */
void load_unit_texture(void);


#endif
