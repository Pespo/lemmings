#ifndef __IMAGERGB_H__
#define __IMAGERGB_H__

typedef struct imagergb {
	unsigned int width;
	unsigned int height;
	unsigned char **row;
	unsigned char *data;
} ImageRGB;

Color *ImageRGB_get_color(ImageRGB *im, unsigned int row, unsigned int col);
int ImageRGB_set_color(ImageRGB *im, unsigned int row, unsigned int col, Color *c);

ImageRGB *ImageRGB_load(char *filePath);
ImageRGB *ImageRGB_alloc(unsigned int width, unsigned int height);
void ImageRGB_free(ImageRGB *im);
void ImageRGB_printf(ImageRGB *im);

#endif
