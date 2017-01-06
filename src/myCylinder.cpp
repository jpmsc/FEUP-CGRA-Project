#include "myCylinder.h"
#include <math.h>

#define PI 3.14159265358979323846

myCylinder::myCylinder(double slices, double stacks, bool smooth)
{
	this->slices = slices;
	this->stacks = stacks;
	this->smooth = smooth;
}

void myCylinder::draw()
{
	double alpha = 2.0 * PI / slices;
	double height = 1.0;
	//double sideLenght = sqrt(pow(cos(alpha)-1,2) + pow(sin(alpha),2));
	double stackHeight = 1.0/this->stacks;
	
	glPushMatrix();
		//glTranslated(0,0,0);
		glRotated(-180,1,0,0);
		glNormal3f(0,0,1);
		glBegin(GL_POLYGON);
				for(int i = 0; i < slices; i++)
				{
					glVertex3f( cos(i * 2.0 * PI / slices), sin(i * PI * 2.0 / slices), 0.0);
				}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslated(0,0,1);
		glNormal3f(0,0,1);
		glBegin(GL_POLYGON);
				for(int i = 0; i < slices; i++)
				{
					glVertex3f( cos(i * 2.0 * PI / slices), sin(i * PI * 2.0 / slices), 0.0);
				}
		glEnd();
	glPopMatrix();
	
	
	glPushMatrix();
		glTranslated(0,0,0);
		glBegin(GL_QUADS);
				for(int i = 0; i < slices; i++)
				{
					if(this->smooth)
					{
						for(int j = 0; j < this->stacks; j++)
						{
							glNormal3f(cos((i+1) * 2.0 * PI / slices), sin((i+1) * PI * 2.0 / slices), 0.0); //0.0
							glVertex3d(cos((i+1) * 2.0 * PI / slices), sin((i+1) * PI * 2.0 / slices), stackHeight*j); //0.0
							
							glNormal3f(cos((i+1) * 2.0 * PI / slices), sin((i+1) * PI * 2.0 / slices), 0.0); //height
							glVertex3d(cos((i+1) * 2.0 * PI / slices), sin((i+1) * PI * 2.0 / slices), stackHeight*(j+1)); //height
							
							glNormal3f(cos(i * 2.0 * PI / slices), sin(i * PI * 2.0 / slices), 0.0); //height
							glVertex3d(cos(i * 2.0 * PI / slices), sin(i * PI * 2.0 / slices), stackHeight*(j+1));// height
							
							glNormal3f(cos(i * 2.0 * PI / slices), sin(i * PI * 2.0 / slices), 0.0); //0.0
							glVertex3d(cos(i * 2.0 * PI / slices), sin(i * PI * 2.0 / slices), stackHeight*j); //0.0
						}
					}
						if(!this->smooth)
						{
							//double angle = alpha;
							for(int j = 0; j < this->stacks; j++)
							{
								glNormal3f(cos(alpha/2 + alpha*i), sin(alpha/2 + alpha*i), 0.0); //0.0
								//glNormal3f(cos(alpha/2 + alpha*j), sin(alpha/2 + alpha*j), stackHeight*(j+1)); //height

								glVertex3d(cos((i+1) * 2.0 * PI / slices), sin((i+1) * PI * 2.0 / slices), stackHeight*j); //0.0
								glVertex3d(cos((i+1) * 2.0 * PI / slices), sin((i+1) * PI * 2.0 / slices), stackHeight*(j+1)); //height
								glVertex3d(cos(i * 2.0 * PI / slices), sin(i * PI * 2.0 / slices), stackHeight*(j+1));// height
								glVertex3d(cos(i * 2.0 * PI / slices), sin(i * PI * 2.0 / slices), stackHeight*j); //0.0
							}
						}
				}
		glEnd();	
	glPopMatrix();
}