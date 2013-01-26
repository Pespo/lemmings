#ifndef __IMAGERGBA_H__
#define __IMAGERGBA_H__

typedef struct ImageRGBA {
	unsigned int width;
	unsigned int height;
	unsigned char **row;
	unsigned char *data;
} ImageRGBA;

Color *ImageRGBA_get_color(ImageRGBA *im, unsigned int row, unsigned int col);
int ImageRGBA_set_color(ImageRGBA *im, unsigned int row, unsigned int col, Color *c);

ImageRGBA *ImageRGBA_load(char *filePath, char *maskPath);
ImageRGBA *ImageRGBA_alloc(unsigned int width, unsigned int height);
void ImageRGBA_free(ImageRGBA *im);

void ImageRGBA_printf(ImageRGBA *im);

#endif
