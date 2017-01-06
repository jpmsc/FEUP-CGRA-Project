#include "myClock.h"
#include <math.h>

#define PI 3.14159265358979323846

myClock::myClock(double slices, double stacks, bool smooth)
{
	this->slices = slices;
	this->stacks = stacks;
	this->smooth = smooth;
}

void myClock::draw()
{
	double alpha = 2.0 * PI / slices;
	double height = 1.0;
	double stackHeight = 1.0/this->stacks;
	/*
	glPushMatrix();
		glTranslated(0,0,1);
		draw_circle(1,this->slices);
	glPopMatrix();
	*/
	
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
		glTranslated(0,0,1);
		glNormal3f(0,0,1);
		glBegin(GL_POLYGON);
				for(int i = 0; i < slices; i++)
				{
					glTexCoord2d(cos(i * 2.0 * PI / slices)*0.5+0.5, sin(i * PI * 2.0 / slices)*0.5+0.5);
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
				}
		glEnd();	
	glPopMatrix();
}

void myClock::draw_circle(double radius, double num_vertex)
{
  glPushMatrix();
	glTranslated(0.5,0.5,0);
	glNormal3f(0,0,1);
glPopMatrix();

  GLfloat vertex[4]; 
  GLfloat texcoord[2];
 
  const GLfloat delta_angle = 2.0*PI/num_vertex;
 
  glBegin(GL_TRIANGLE_FAN);
 
  //draw the vertex at the center of the circle
  texcoord[0] = 0.5;
  texcoord[1] = 0.5;
  glTexCoord2fv(texcoord);
 
  vertex[0] = vertex[1] = vertex[2] = 0.0;
  vertex[3] = 1.0;        
  glVertex4fv(vertex);
 
  for(int i = 0; i < num_vertex ; i++)
  {
	glNormal3f(0,0,1);
    texcoord[0] = (cos(delta_angle*i) + 1.0)*0.5;
    texcoord[1] = (sin(delta_angle*i) + 1.0)*0.5;
    glTexCoord2fv(texcoord);
 
    vertex[0] = cos(delta_angle*i) * radius;
    vertex[1] = sin(delta_angle*i) * radius;
    vertex[2] = 0.0;
    vertex[3] = 1.0;
    glVertex4fv(vertex);
  }
 
  texcoord[0] = (1.0 + 1.0)*0.5;
  texcoord[1] = (0.0 + 1.0)*0.5;
  glTexCoord2fv(texcoord);
 
  vertex[0] = 1.0 * radius;
  vertex[1] = 0.0 * radius;
  vertex[2] = 0.0;
  vertex[3] = 1.0;
  glVertex4fv(vertex);

  glEnd();
 
}