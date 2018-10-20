#include "include/textures.h"


GLuint bg_tex_ptr;
GLuint side_tex_ptr[SIDES_N];


Image *image_init(int width, int height)
{
	/* Exiting in case of error */
	if (width < 0 || height < 0) {
		perror("Error orrured while initializing image structure");
		exit(EXIT_FAILURE);
	}

	/* Allocating memory for struct elements */
	Image *image = (Image *) malloc(sizeof(Image));
	if (image == NULL) {
		perror("Texture structure memory allocation failed");
		exit(EXIT_FAILURE);
	}

	/* Initializing struct elements */
	image->width = width;
	image->height = height;
	if (width == 0 || height == 0)
		image->pixels = NULL;
	else {
		image->pixels = (char *)malloc(3 * width * height * sizeof(char));
		if (image->pixels == NULL) {
			perror("Texture pixel memory allocation failed");
			exit(EXIT_FAILURE);
		}
	}

	return image;
}

void image_free(Image *image)
{
	if (image != NULL && image->pixels != NULL)
		free(image->pixels);
	if (image != NULL)
		free(image);
}

void image_read(Image *image, char *filename)
{
	FILE *file;
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	unsigned int i;
	unsigned char r, g, b, a;

	/* Deleting previous pixel content */
	free(image->pixels);
	image->pixels = NULL;

	/* Opening new binary file */
	if ((file = fopen(filename, "rb")) == NULL) {
		fprintf(stderr, "Failed opening texture: \"%s\"\n", filename);
		fprintf(stderr, "Make sure all textures are in 'tex' folder!\n");
		exit(EXIT_FAILURE);
	}

	/* Reading first header data */
	fread(&bfh.type, 2, 1, file);
	fread(&bfh.size, 4, 1, file);
	fread(&bfh.reserved1, 2, 1, file);
	fread(&bfh.reserved2, 2, 1, file);
	fread(&bfh.offsetbits, 4, 1, file);

	/* Reading second header data */
	fread(&bih.size, 4, 1, file);
	fread(&bih.width, 4, 1, file);
	fread(&bih.height, 4, 1, file);
	fread(&bih.planes, 2, 1, file);
	fread(&bih.bitcount, 2, 1, file);
	fread(&bih.compression, 4, 1, file);
	fread(&bih.sizeimage, 4, 1, file);
	fread(&bih.xpelspermeter, 4, 1, file);
	fread(&bih.ypelspermeter, 4, 1, file);
	fread(&bih.colorsused, 4, 1, file);
	fread(&bih.colorsimportant, 4, 1, file);

	/* From second header data, we use only image size information */
	image->width = bih.width;
	image->height = bih.height;

	/* Depending on how many bits of information are read for each pixel
	   (RGB or RGBA), we allocate accordingly */
	if (bih.bitcount == 24)
		image->pixels = (char *)malloc(3 * bih.width * bih.height * sizeof(char));
	else if (bih.bitcount == 32)
		image->pixels = (char *)malloc(4 * bih.width * bih.height * sizeof(char));
	else {
		fprintf(stderr, "Only supported textures are those which use 24 or 32 bits per pixel!\n");
		exit(EXIT_FAILURE);
	}

	if (image->pixels == NULL) {
		perror("Texture pixel memory allocation failed");
		exit(EXIT_FAILURE);
	}

	/* Reading pixel data and moving it to the allocated array */
	if (bih.bitcount == 24)
		/* If there are 24 bits per pixel, assume those 3 bytes represent RGB */
		for (i = 0; i < bih.width * bih.height; i++) {
			/* bmp specification states that colors are in reverse order -> BGR */
			fread(&b, sizeof(char), 1, file);
			fread(&g, sizeof(char), 1, file);
			fread(&r, sizeof(char), 1, file);

			image->pixels[3 * i] = r;
			image->pixels[3 * i + 1] = g;
			image->pixels[3 * i + 2] = b;
		}
	else if (bih.bitcount == 32)
		/* If there are 24 bits per pixel, assume those 3 bytes represent RGBA */
		for (i = 0; i < bih.width * bih.height; i++) {
			fread(&b, sizeof(char), 1, file);
			fread(&g, sizeof(char), 1, file);
			fread(&r, sizeof(char), 1, file);
			fread(&a, sizeof(char), 1, file);

			image->pixels[4 * i] = r;
			image->pixels[4 * i + 1] = g;
			image->pixels[4 * i + 2] = b;
			image->pixels[4 * i + 3] = a;
		}

	fclose(file);
}

void load_background_texture(char *filename)
{
	/* Background texture isn't affected by scene lighting */
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	/* Initializing image structure elements */
	Image *image = image_init(0, 0);

	/* Reading texture from file */
	image_read(image, filename);

	/* Binding texture to pointer and setting texture parameters */
	glGenTextures(1, &bg_tex_ptr);
	glBindTexture(GL_TEXTURE_2D, bg_tex_ptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
				 image->width, image->height, 0,
				 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	glBindTexture(GL_TEXTURE_2D, 0);

	/* Freeing resources */
	image_free(image);
}

void load_unit_texture(void)
{
	/* Locations of our unit cube textures */
	char *files[] = {
		"tex/pieces/white.bmp",
		"tex/pieces/red.bmp",
		"tex/pieces/green.bmp",
		"tex/pieces/blue.bmp",
		"tex/pieces/yellow.bmp",
		"tex/pieces/orange.bmp"
	};

	/* Initializing image structure elements */
	Image *image = image_init(0, 0);

	/* Generating 6 textures for each side */
	glGenTextures(SIDES_N, side_tex_ptr);

	int i;
	for (i = 0; i < SIDES_N; i++) {
		/* Reading image from file */
		image_read(image, files[i]);

		/* Binding texture to pointer and setting texture parameters */
		glBindTexture(GL_TEXTURE_2D, side_tex_ptr[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
					 image->width, image->height, 0,
					 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	/* Freeing resources */
	image_free(image);
}
