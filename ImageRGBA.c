#include "main.h"
#include "ImageRGBA.h"

Color *ImageRGBA_get_color(ImageRGBA *im, unsigned int row, unsigned int col) {
	
	Color *c = (Color*) malloc(sizeof(Color));
	
	if (row < im->height && col < im->width && c != NULL) {
		
		c->r = im->row[row][col * 4];
		c->g = im->row[row][col * 4 + 1];
		c->b = im->row[row][col * 4 + 2];
		c->a = im->row[row][col * 4 + 3];
	}
	
	return c;
}

int ImageRGBA_set_color(ImageRGBA *im, unsigned int row, unsigned int col, Color *c) {
	
	if (row < im->height && col < im->width) {
		
		im->row[row][col * 4] = c->r;
		im->row[row][col * 4 + 1] = c->g;
		im->row[row][col * 4 + 2] = c->b;
		im->row[row][col * 4 + 3] = c->a;
		
		return 1;
	}
	
	return 0;
}

ImageRGBA *ImageRGBA_load(char *filePath, char *maskPath) {
	
	FILE *mHandler;
	FILE *fHandler;
	int type, bytes, width, height;
	ImageRGBA *im = NULL;
	unsigned char r, g, b;
	Color *mColor = NULL;
	Color *fColor = NULL;
	unsigned int row, col;
	
	mHandler = fopen(maskPath, "rb");
	fHandler = fopen(filePath, "rb");
	
	if (mHandler && fHandler) {
		
		//Lecture du type
		fscanf(mHandler, "P%d\n", &type);
		fscanf(fHandler, "P%d\n", &type);
		
		if (type == 6) {
			
			//Récupération des dimensions
			fscanf(mHandler, "%d %d\n", &width, &height);
			fscanf(fHandler, "%d %d\n", &width, &height);
			
			if (width > 0 && height > 0) {
				
				//Récupération des bits de codage
				fscanf(mHandler, "%d\n", &(bytes));
				fscanf(fHandler, "%d\n", &(bytes));
				
				//Allocation de l'image
				im = ImageRGBA_alloc(width, height);
				
				if (im != NULL) {
					
					for (row = 0; row < im->height; row++) {
						for (col = 0; col < im->width; col++) {
							
							//Récupération des données de l'image
							fscanf(mHandler, "%c", &r);
							fscanf(mHandler, "%c", &g);
							fscanf(mHandler, "%c", &b);
							
							mColor = Color_create(r, g, b);
							
							fscanf(fHandler, "%c", &r);
							fscanf(fHandler, "%c", &g);
							fscanf(fHandler, "%c", &b);
							
							fColor = Color_create(r, g, b);
							fColor->a = mColor->a;
							
							ImageRGBA_set_color(im, row, col, fColor);
							
							Color_free(mColor);
							mColor = NULL;
							Color_free(fColor);
							fColor = NULL;
							
							//fread(im->data, sizeof(unsigned char), im->width * im->height * 3, fHandler);
						}
					}
				}
			}
		}
		
		fclose(mHandler);
		fclose(fHandler);
	}
	
	return im;
}

ImageRGBA *ImageRGBA_alloc(unsigned int width, unsigned int height) {
	
	unsigned int row;
	ImageRGBA *im = NULL;
	
	//Allocation de l'image
	im = (ImageRGBA*) malloc(sizeof(ImageRGBA));
	
	if (im != NULL) {
		
		//Allocation du tableau de données
		im->data = (unsigned char*) malloc(width * height * 4 * sizeof(unsigned char));
		
		if (im->data != NULL) {
			
			im->width = width;
			im->height = height;
			
			//Allocation du tableau de pointeurs de début de lignes
			im->row = (unsigned char**) malloc(im->height * sizeof(unsigned char*));
			
			if (im->row != NULL) {
				
				//Pointage de chaque début de ligne dans row
				for (row = 0; row < im->height; row++) {
					
					im->row[row] = &(im->data[row * 4 * im->width]);
				}
			} else {
				
				return NULL;
			}
		} else {
			
			return NULL;
		}
	}
	
	return im;
}

void ImageRGBA_free(ImageRGBA *im) {
	
	//dDésallocation du conteneur de données
	free(im->data);
	
	//Désallocation des pointeurs de début de ligne
	free(im->row);
	
	//Désallocation de la structure
	free(im);
}

void ImageRGBA_printf(ImageRGBA *im) {
	
	unsigned int row, col;
	Color *c = NULL;
	
	printf("ImageRGBA at %p : \n", im);
	printf("\t width : %d\n", im->width);
	printf("\theight : %d\n", im->height);
	printf("\t data at %p\n", im->data);
	printf("\t  row at %p\n", im->row);
	printf("\n");
	printf("--DATA\n");
	
	for (row = 0; row < im->height; row++) {
		for (col = 0; col < im->width; col++) {
			c = ImageRGBA_get_color(im, row, col);
			printf("%d\t", c->g);
			Color_free(c);
			c = NULL;
		}
		printf("\n");
	}
	printf("\n");
	printf("--ALPHA\n");
	
	for (row = 0; row < im->height; row++) {
		for (col = 0; col < im->width; col++) {
			c = ImageRGBA_get_color(im, row, col);
			printf("%d\t", c->a);
			Color_free(c);
			c = NULL;
		}
		printf("\n");
	}
	printf("------------------------------------------\n\n");
}