#include "main.h"
#include "glSquare.h"

void glSquare_draw(Square *square, GLuint* textureId) {
	
	//Dessin du sol de base
	glBindTexture(GL_TEXTURE_2D, textureId[GROUND]);
	glPushMatrix();
		glTranslatef(square->col, square->row, 0.0);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex2f(0.0f, 0.0f);
			glTexCoord2f(1.0, 0.0);
			glVertex2f(1.0f, 0.0f);
			glTexCoord2f(1.0, 1.0);
			glVertex2f(1.0f, 1.0f);
			glTexCoord2f(0.0, 1.0);
			glVertex2f(0.0f, 1.0f);
		glEnd();
	glPopMatrix();
	
	//Si le type du Square n'est pas GROUND on dessine le Square particulier
	if (square->type != GROUND) {

		glBindTexture(GL_TEXTURE_2D, textureId[square->type]);
		glPushMatrix();
			glTranslatef(square->col, square->row, 0.0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);
				glVertex2f(0.0f, 0.0f);
				glTexCoord2f(1.0, 0.0);
				glVertex2f(1.0f, 0.0f);
				glTexCoord2f(1.0, 1.0);
				glVertex2f(1.0f, 1.0f);
				glTexCoord2f(0.0, 1.0);
				glVertex2f(0.0f, 1.0f);
			glEnd();
			glDisable(GL_BLEND);
		glPopMatrix();
	}

	//Si lemming sur le Square -> dessin du lemming
	if(square->lemming != NULL) {
		
        glBindTexture(GL_TEXTURE_2D, textureId[RABBIT]);
        glPushMatrix();
			glTranslatef(square->col, square->row, 0.0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0);
                glVertex2f(0.0, 0.0);
                glTexCoord2f(1.0, 0.0);
                glVertex2f(1.0, 0.0);
                glTexCoord2f(1.0, 1.0);
                glVertex2f(1.0, 1.0);
                glTexCoord2f(0.0, 1.0);
                glVertex2f(0.0, 1.0);
            glEnd();
			glDisable(GL_BLEND);
		glPopMatrix();
    }
}

void glSquare_draw_menu(Square *square, GLuint* textureId) {
	
	glBindTexture(GL_TEXTURE_2D, textureId[square->type]);
	glPushMatrix();
		glTranslatef(square->col, square->row, 0.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex2f(0.0, 0.0);
			glTexCoord2f(1.0, 0.0);
			glVertex2f(0.7, 0.0);
			glTexCoord2f(1.0, 1.0);
			glVertex2f(0.7, 1.0);
			glTexCoord2f(0.0, 1.0);
			glVertex2f(0.0, 1.0);
		glEnd();
		glDisable(GL_BLEND);
	glPopMatrix();
}

//Ecriture de texte dans un square
void glSquare_write(Square *square, char *text) {	

	int i;
	int len = (int) strlen(text);
	
	glPushMatrix();
		glRasterPos2f( square->col + 0.1, square->row + 0.8 );
		
		for (i = 0; i < len; i++){
			
			glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, text[i] );
		}
    glPopMatrix();
}