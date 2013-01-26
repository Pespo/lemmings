#include "main.h"
#include "ImageRGB.h"

Color *ImageRGB_get_color(ImageRGB *im, unsigned int row, unsigned int col) {
	
	Color *c = (Color*) malloc(sizeof(Color));
	
	if (row < im->height && col < im->width && c != NULL) {
			
		c->r = im->row[row][col * 3];
		c->g = im->row[row][col * 3 + 1];
		c->b = im->row[row][col * 3 + 2];
	}
	
	return c;
}

int ImageRGB_set_color(ImageRGB *im, unsigned int row, unsigned int col, Color *c) {
		
	if (row < im->height && col < im->width) {
		
		im->row[row][col * 3] = c->r;
		im->row[row][col * 3 + 1] = c->g;
		im->row[row][col * 3 + 2] = c->b;
	
		return 1;
	}
	
	return 0;
}

ImageRGB *ImageRGB_load(char *filePath) {
	
	FILE *fHandler;
	int type, bytes, width, height;
	ImageRGB *im = NULL;
	unsigned char r, g, b;
	Color *color = NULL;
	unsigned int row, col;
	
	fHandler = fopen(filePath, "rb");
	
	if (fHandler) {
		
		//Lecture du type
		fscanf(fHandler, "P%d\n", &type);
		
		if (type == 6) {
			
			//Récupération des dimensions
			fscanf(fHandler, "%d %d\n", &width, &height);
			
			if (width > 0 && height > 0) {
				
				//Récupération des bits de codage
				fscanf(fHandler, "%d\n", &(bytes));
				
				//Allocation de l'image
				im = ImageRGB_alloc(width, height);
				
				if (im != NULL) {
					
					for (row = 0; row < im->height; row++) {
						for (col = 0; col < im->width; col++) {
							//Récupération des données de l'image
							fscanf(fHandler, "%c", &r);
							fscanf(fHandler, "%c", &g);
							fscanf(fHandler, "%c", &b);
							
							color = Color_create(r, g, b);
							
							ImageRGB_set_color(im, row, col, color);
							
							Color_free(color);
							color = NULL;
						}
					}
				}
			}
		}
		
		fclose(fHandler);
	}
	
	return im;
}

ImageRGB *ImageRGB_alloc(unsigned int width, unsigned int height) {
	
	unsigned int row;
	ImageRGB *im = NULL;
	
	//Allocation de l'image
	im = (ImageRGB*) malloc(sizeof(ImageRGB));
	
	if (im != NULL) {
		
		//Allocation du tableau de données
		im->data = (unsigned char*) malloc(width * height * 3 * sizeof(unsigned char));
		
		if (im->data != NULL) {
			
			im->width = width;
			im->height = height;
			
			//Allocation du tableau de pointeurs de début de lignes
			im->row = (unsigned char**) malloc(im->height * sizeof(unsigned char*));
			
			if (im->row != NULL) {
				
				//Pointage de chaque début de ligne dans row
				for (row = 0; row < im->height; row++) {
					
					im->row[row] = &(im->data[row * 3 * im->width]);
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

void ImageRGB_free(ImageRGB *im) {
	
	//Désallocation du conteneur de données
	free(im->data);
	
	//Désallocation des pointeurs de début de ligne
	free(im->row);
	
	//Désallocation de la structure
	free(im);
}

void ImageRGB_printf(ImageRGB *im) {
	
	unsigned int row, col;
	Color *c = NULL;
	
	printf("ImageRGB at %p : \n", im);
	printf("\t width : %d\n", im->width);
	printf("\theight : %d\n", im->height);
	printf("\t data at %p\n", im->data);
	printf("\t  row at %p\n", im->row);
	printf("\n");
	printf("--DATA\n");

	for (row = 0; row < im->height; row++) {
		for (col = 0; col < im->width; col++) {
			c = ImageRGB_get_color(im, row, col);
			printf("%d\t", c->g);
			Color_free(c);
			c = NULL;
		}
		printf("\n");
	}
	printf("------------------------------------------\n\n");
}