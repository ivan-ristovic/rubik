#include "include/draw.h"

/* Material properties for each color: */
/* Red */
GLfloat ambient_coeffs_r[] 	= { 0.2,   0,   0, 1 };
GLfloat diffuse_coeffs_r[] 	= {   1,   0,   0, 1 };
/* Green */
GLfloat ambient_coeffs_g[] 	= {   0, 0.2,   0, 1 };
GLfloat diffuse_coeffs_g[] 	= {   0,   1,   0, 1 };
/* Blue */
GLfloat ambient_coeffs_b[] 	= {   0,   0, 0.2, 1 };
GLfloat diffuse_coeffs_b[] 	= {   0,   0,   1, 1 };
/* White */
GLfloat ambient_coeffs_w[] 	= { 0.2, 0.2, 0.2, 1 };
GLfloat diffuse_coeffs_w[] 	= {   1,   1,   1, 1 };
/* Orange */
GLfloat ambient_coeffs_o[] 	= { 0.2, .05,   0, 1 };
GLfloat diffuse_coeffs_o[] 	= {   1, 0.5,   0, 1 };
/* Yellow */
GLfloat ambient_coeffs_y[] 	= { 0.2, 0.2,   0, 1 };
GLfloat diffuse_coeffs_y[] 	= {   1,   1,   0, 1 };
/* Black */
GLfloat ambient_coeffs_bl[]	= {   0,   0,   0, 1 };
GLfloat diffuse_coeffs_bl[]	= {   0,   0,   0, 1 };


void draw_unit_cube(float x, float y, float z)
{
	/* Translating drawn unit cube to given position */
	glTranslatef(-x, -y, -z);

	/* Drawing red side */
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_r);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_r);
	glBindTexture(GL_TEXTURE_2D, side_tex_ptr[RED]);
	glBegin(GL_POLYGON);
		glNormal3f(0, 0, 1);
		glColor3f(0.9, 0.1, 0.1);
		glTexCoord2f(0, 0); glVertex3f(-UNIT_HALFSIZE, -UNIT_HALFSIZE,  UNIT_HALFSIZE);
		glTexCoord2f(1, 0); glVertex3f( UNIT_HALFSIZE, -UNIT_HALFSIZE,  UNIT_HALFSIZE);
		glTexCoord2f(1, 1); glVertex3f( UNIT_HALFSIZE,  UNIT_HALFSIZE,  UNIT_HALFSIZE);
		glTexCoord2f(0, 1); glVertex3f(-UNIT_HALFSIZE,  UNIT_HALFSIZE,  UNIT_HALFSIZE);
	glEnd();

	/* Drawing green side */
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_g);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_g);
	glBindTexture(GL_TEXTURE_2D, side_tex_ptr[GREEN]);
	glBegin(GL_POLYGON);
		glNormal3f(0, 0, -1);
		glColor3f(0, 0.9, 0);
		glTexCoord2f(0, 0); glVertex3f(-UNIT_HALFSIZE, -UNIT_HALFSIZE, -UNIT_HALFSIZE);
		glTexCoord2f(1, 0); glVertex3f( UNIT_HALFSIZE, -UNIT_HALFSIZE, -UNIT_HALFSIZE);
		glTexCoord2f(1, 1); glVertex3f( UNIT_HALFSIZE,  UNIT_HALFSIZE, -UNIT_HALFSIZE);
		glTexCoord2f(0, 1); glVertex3f(-UNIT_HALFSIZE,  UNIT_HALFSIZE, -UNIT_HALFSIZE);
	glEnd();

	/* Drawing blue side */
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_b);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_b);
	glBindTexture(GL_TEXTURE_2D, side_tex_ptr[BLUE]);
	glBegin(GL_POLYGON);
		glNormal3f(0, 1, 0);
		glColor3f(0, 0, 0.9);
		glTexCoord2f(0, 0); glVertex3f(-UNIT_HALFSIZE,  UNIT_HALFSIZE, -UNIT_HALFSIZE);
		glTexCoord2f(1, 0); glVertex3f( UNIT_HALFSIZE,  UNIT_HALFSIZE, -UNIT_HALFSIZE);
		glTexCoord2f(1, 1); glVertex3f( UNIT_HALFSIZE,  UNIT_HALFSIZE,  UNIT_HALFSIZE);
		glTexCoord2f(0, 1); glVertex3f(-UNIT_HALFSIZE,  UNIT_HALFSIZE,  UNIT_HALFSIZE);
	glEnd();

	/* Drawing white side */
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_w);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_w);
	glBindTexture(GL_TEXTURE_2D, side_tex_ptr[WHITE]);
	glBegin(GL_POLYGON);
		glNormal3f(0, -1, 0);
		glColor3f(0.9, 0.9, 0.9);
		glTexCoord2f(0, 0); glVertex3f(-UNIT_HALFSIZE, -UNIT_HALFSIZE, -UNIT_HALFSIZE);
		glTexCoord2f(1, 0); glVertex3f( UNIT_HALFSIZE, -UNIT_HALFSIZE, -UNIT_HALFSIZE);
		glTexCoord2f(1, 1); glVertex3f( UNIT_HALFSIZE, -UNIT_HALFSIZE,  UNIT_HALFSIZE);
		glTexCoord2f(0, 1); glVertex3f(-UNIT_HALFSIZE, -UNIT_HALFSIZE,  UNIT_HALFSIZE);
	glEnd();

	/* Drawing orange side */
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_o);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_o);
	glBindTexture(GL_TEXTURE_2D, side_tex_ptr[ORANGE]);
	glBegin(GL_POLYGON);
		glNormal3f(1, 0, 0);
		glColor3f(0.9, 0.5, 0);
		glTexCoord2f(0, 0); glVertex3f( UNIT_HALFSIZE, -UNIT_HALFSIZE, -UNIT_HALFSIZE);
		glTexCoord2f(1, 0); glVertex3f( UNIT_HALFSIZE,  UNIT_HALFSIZE, -UNIT_HALFSIZE);
		glTexCoord2f(1, 1); glVertex3f( UNIT_HALFSIZE,  UNIT_HALFSIZE,  UNIT_HALFSIZE);
		glTexCoord2f(0, 1); glVertex3f( UNIT_HALFSIZE, -UNIT_HALFSIZE,  UNIT_HALFSIZE);
	glEnd();

	/* Drawing yellow side */
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_y);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_y);
	glBindTexture(GL_TEXTURE_2D, side_tex_ptr[YELLOW]);
	glBegin(GL_POLYGON);
		glNormal3f(-1, 0, 0);
		glColor3f(0.9, 0.9, 0);
		glTexCoord2f(0, 0); glVertex3f(-UNIT_HALFSIZE, -UNIT_HALFSIZE, -UNIT_HALFSIZE);
		glTexCoord2f(1, 0); glVertex3f(-UNIT_HALFSIZE,  UNIT_HALFSIZE, -UNIT_HALFSIZE);
		glTexCoord2f(1, 1); glVertex3f(-UNIT_HALFSIZE,  UNIT_HALFSIZE,  UNIT_HALFSIZE);
		glTexCoord2f(0, 1); glVertex3f(-UNIT_HALFSIZE, -UNIT_HALFSIZE,  UNIT_HALFSIZE);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void draw_rubik_cube(float x, float y, float z)
{
	/* Current rotate_matrix array index */
	int unit_iter = 0;

	/* Looping through coordinates from (-1, -1, -1) to (1, 1, 1) */
	int i, j, k;
	for (i = -1; i <= 1; i += 1) {
		for (j = -1; j <= 1; j += 1) {
			for (k = -1; k <= 1; k += 1) {
				glPushMatrix();
					/* Applying rotation to drawn piece */
					glMultMatrixf(rotate_matrix[unit_iter]);
					/* Drawing cube piece */
					draw_unit_cube(x + k, y + j, z + i);
				glPopMatrix();
				unit_iter++;
			}
		}
	}
}

void draw_background(void)
{
	/* Background is not affected by scene lighting */
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	/* Binding loaded background texture */
	glBindTexture(GL_TEXTURE_2D, bg_tex_ptr);

	glPushMatrix();
		/* Rotating background canvas in front of camera */
		glRotatef(-23, 0, 1, 0);
		glRotatef( 20, 0, 0, 1);

		/* Drawing background canvas */
		glBegin(GL_POLYGON);
			glNormal3f(1, 0, 0);
			glTexCoord2f(0, 0);	glVertex3f(-15, -15,  15);
			glTexCoord2f(1, 0);	glVertex3f(-15, -15, -15);
			glTexCoord2f(1, 1);	glVertex3f(-15,  15, -15);
			glTexCoord2f(0, 1);	glVertex3f(-15,  15,  15);
		glEnd();
	glPopMatrix();

	/* Unbinding texture */
	glBindTexture(GL_TEXTURE_2D, 0);

	/* Putting back lighting effect for textures */
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}
