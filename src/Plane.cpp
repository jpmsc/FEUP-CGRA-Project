#include "Plane.h"
#include <GL/GLU.h>


Plane::Plane(void)
{
	_numDivisions = 1;
}

Plane::Plane(int n)
{
	_numDivisions = n;
}


Plane::~Plane(void)
{
}

void Plane::draw()
{
	glPushMatrix();
		glRotatef(180.0,1,0,0);
		glTranslatef(-0.5,0.0,-0.5);
		glScalef(1.0/(double) _numDivisions, 1 ,1.0/(double) _numDivisions);
		glNormal3f(0,-1,0);

		for (int bx = 0; bx<_numDivisions; bx++)
		{
			glBegin(GL_TRIANGLE_STRIP);

				glTexCoord2f(bx * 1.0/_numDivisions, 0.0);
				glVertex3f(bx, 0, 0);

				for (int bz = 0; bz<_numDivisions; bz++)
				{
					glTexCoord2f((bx+1) * 1.0/_numDivisions, bz * 1.0/_numDivisions);
					glVertex3f(bx + 1, 0, bz);

					glTexCoord2f((bx+1) * 1.0/_numDivisions, (bz+1) * 1.0/_numDivisions); 
					glVertex3f(bx, 0, bz + 1);
				}
				glTexCoord2f((bx+1) * 1.0/_numDivisions, 1.0);
				glVertex3d(bx+1, 0, _numDivisions);				
			
			glEnd();
		}
	glPopMatrix();

}

void Plane::draw2(double xScale, double zScale, double xOffset, double zOffset)
{
	glPushMatrix();
		glRotatef(180.0,1,0,0);
		glTranslatef(-0.5,0.0,-0.5);
		glScalef(1.0/(double) _numDivisions, 1 ,1.0/(double) _numDivisions);
		glNormal3f(0,-1,0);

		for (int bx = 0; bx<_numDivisions; bx++)
		{
			glBegin(GL_TRIANGLE_STRIP);

				
				glTexCoord2f((bx * xScale/_numDivisions)-xOffset, 0.0-zOffset);
				
				glVertex3f(bx, 0, 0);

				for (int bz = 0; bz<_numDivisions; bz++)
				{
					
					glTexCoord2f(((bx+1) * xScale/_numDivisions)-xOffset, (bz * zScale/_numDivisions)-zOffset);
					
					glVertex3f(bx + 1, 0, bz);

				
					glTexCoord2f(((bx+1) * xScale/_numDivisions)-xOffset, ((bz+1) * zScale/_numDivisions)-zOffset);
					
					glVertex3f(bx, 0, bz + 1);
					
				}

				
				glTexCoord2f(((bx+1) * xScale/_numDivisions)-xOffset, zScale-zOffset);
				
				glVertex3d(bx+1, 0, _numDivisions);				

			glEnd();
		}
	glPopMatrix();

}

void Plane::draw3(double xScale, double zScale, double xOffset, double zOffset)
{
	double tex = 1/_numDivisions;
	glPushMatrix();
		glRotatef(180.0,1,0,0);
		glTranslatef(-0.5,0.0,-0.5);
		glScalef(1.0/(double) _numDivisions, 1 ,1.0/(double) _numDivisions);
		glNormal3f(0,-1,0);

		int lLimx = 74;
		int uLimx = 125;
		int lLimz = 60;
		int uLimz = 135;

		glBegin(GL_QUAD_STRIP);
		for(int i = 0; i < _numDivisions; i++) //x
		{
			for(int k = 0; k < _numDivisions; k++) //z
			{
				if(i >= lLimx && i <= uLimx && k >= lLimz && k <= uLimz)
				{
					if(k==lLimz)
						glEnd();
					if(k==uLimz)
						glBegin(GL_QUAD_STRIP);
				}

				glTexCoord2d((i*xScale/_numDivisions)-xOffset,((k+1)*zScale/_numDivisions)-zOffset);
				glVertex3d(i, 0.0, k+1); //4

				glTexCoord2d((i*xScale/_numDivisions)-xOffset,(k*zScale/_numDivisions)-zOffset);
				glVertex3d(i, 0.0, k); //1

				glTexCoord2d(((i+1)*xScale/_numDivisions)-xOffset,((k+1)*zScale/_numDivisions)-zOffset);
				glVertex3d(i+1, 0.0, k+1); //3

				glTexCoord2d(((i+1)*xScale/_numDivisions)-xOffset,(k*zScale/_numDivisions)-zOffset);
				glVertex3d(i+1, 0.0, k); //2
			}
		}

		glEnd();
	glPopMatrix();

}
