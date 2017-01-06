#include "myClockHand.h"
#include <math.h>

myClockHand::myClockHand(float angle, float lenght)
{
	this->angle = angle;
	this->lenght = lenght;
}

void myClockHand::setAngle(float angle)
{
	this->angle = angle;
}

float myClockHand::getAngle()
{
	return this->angle;
}

void myClockHand::draw()
{
	glPushMatrix();
		glRotated(-this->angle,0,0,1);
		glBegin(GL_POLYGON);
			glVertex3d(-0.015,0.0,0.0);
			glVertex3d(0.015,0.0,0.0);
			glVertex3d(0.015,this->lenght,0.0);
			glVertex3d(-0.015,this->lenght,0.0);
		glEnd();
	glPopMatrix();
}