#include "main.h"
#include "glMap.h"

void glMap_load_texture() {

	ImageRGBA* texture;
	int i;
	
	glEnable(GL_TEXTURE_2D);
    glGenTextures(NB_TEXTURES, textureId);

	char *path = (char*) malloc(sizeof(char) * sizeAbsolutePath);
	char *mask = (char*) malloc(sizeof(char) * sizeAbsolutePath);
	
	for (i = 0; i < NB_TEXTURES; i++) {
		strncpy(path, absolutePath, sizeAbsolutePath);
		strncpy(mask, absolutePath, sizeAbsolutePath);

		strncat(path, "textures/", sizeAbsolutePath);
		strncat(mask, "textures/", sizeAbsolutePath);
		
		strncat(path, texturePaths[i][0], sizeAbsolutePath);
		strncat(mask, texturePaths[i][1], sizeAbsolutePath);

		texture = ImageRGBA_load(path, mask);
		
		glBindTexture(GL_TEXTURE_2D, textureId[i]);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
		
		ImageRGBA_free(texture);
		texture = NULL;
	}
	
	free(path);
	path = NULL;
	free(mask);
	mask = NULL;
}
