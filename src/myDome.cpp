#include "myDome.h"
#include <math.h>

#define PI 3.14159265358979323846

myDome::myDome(double slices, double stacks, bool smooth)
{
	this->slices = slices;
	this->stacks = stacks;
	this->smooth = smooth;
}

void myDome::draw()
{
	double alpha = 2.0 * PI / slices;
	double beta = PI/2.0/stacks;
	double stackHeight = 1.0/this->stacks;
	double R1, R2;

	glPushMatrix();
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
		glBegin(GL_QUADS);
		for(int i = 0; i < this->stacks; i++)
		{
			if(i != this->stacks-1)
			{
				R1 = cos(i * beta);
				R2 = cos((i+1) * beta);
				for(int j = 0; j < this->slices; j++)
				{
					glNormal3d(R1 * cos(j * alpha), R1 * sin(j * alpha), stackHeight*i);
					glVertex3d(R1 * cos(j * alpha), R1 * sin(j * alpha), stackHeight*i);

					glNormal3d(R1 * cos((j+1) * alpha), R1 * sin((j+1) * alpha), stackHeight*i);
					glVertex3d(R1 * cos((j+1) * alpha), R1 * sin((j+1) * alpha), stackHeight*i);
				
					glNormal3d(R2 * cos((j+1) * alpha), R2 * sin((j+1) * alpha), stackHeight*(i+1));
					glVertex3d(R2 * cos((j+1) * alpha), R2 * sin((j+1) * alpha), stackHeight*(i+1));
				
					glNormal3d(R2 * cos(j * alpha), R2 * sin(j * alpha), stackHeight*(i+1));
					glVertex3d(R2 * cos(j * alpha), R2 * sin(j * alpha), stackHeight*(i+1));	
				}
			}
		}
		glEnd();
	glPopMatrix();
}