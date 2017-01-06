#include "MyRobot.h"
#include "math.h"
#include <iostream>

#define PI 3.14159265358979323846

using namespace std;

MyRobot::MyRobot(double slices, double stacks, double angle)
{
	this->slices = slices;
	this->stacks = stacks;
	this->angle = angle;
	this->xCoord = 0.0;
	this->zCoord = 0.0;
	calculatePoints();
	calculateTextures();
}
void MyRobot::draw()
{
	glPushMatrix();
		glTranslated(this->getX(), 0, this->getZ());
		glRotated(this->angle,0,1,0);
			glBegin(GL_POLYGON);
				glVertex3d(0.5,0.3,0.0);
				glVertex3d(-0.5,0.3,0.0);
				glVertex3d(0.0,0.3,2.0);
			glEnd();
	glPopMatrix();
}

void MyRobot::draw2(int wireMode)
{
	double beta = 45.0*PI/180.0;
	double alpha = 30.0*PI/180.0;
	double offset = 0.0*PI/180.0;

	glPushMatrix();
		glTranslated(this->getX(), 0, this->getZ());
		glRotated(this->angle,0,1,0);
		if(wireMode == 1)
			glBegin(GL_LINE_STRIP);
		else if(wireMode == 0)
	
		glBegin(GL_POLYGON);//base
			glVertex3d(-0.5,0.0,0.5);
			glVertex3d(-0.5,0.0,-0.5);
			glVertex3d(0.5,0.0,-0.5);
			glVertex3d(0.5,0.0,0.5);
		glEnd();
	
		for(int i = 0; i < 4; i++)
		{
			glRotated(90.0*i,0,1,0);
			this->quarter(wireMode, 90*i);
		}

		//ze TOP
		glTranslated(0,1.0,0); 
		glRotated(180,0,1,0);
		glBegin(GL_POLYGON);
		glTexCoord2d(0.5,0.5);
		for(int i = 0; i < 12.0; i++)
		{
			glTexCoord2d( (cos(-beta - i*alpha+offset)*0.25)+0.5, (sin(-beta - i*alpha+offset)*0.25)+0.5);
			glVertex3f( cos(-beta - i*alpha)*0.25, 0.0, sin(-beta - i*alpha)*0.25);
		}
		glEnd();
	glPopMatrix();

}



void MyRobot::quarter(int wireMode, int rotation)
{
	if(wireMode == 1)
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	else if(wireMode == 0)
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	glBegin(GL_QUAD_STRIP);
		for(int i = 0; i < vertexX.size()-4; i++)
		{
			if(rotation == 0)
			{
				glTexCoord2d(texture0X[i], texture0Y[i]);
			}
			else if(rotation == 90)
			{
				glTexCoord2d(texture90X[i], texture90Y[i]);
			}
			else if(rotation == 180)
			{
				glTexCoord2d(texture180X[i], texture180Y[i]);
			}
			else if(rotation == 270)
			{
				glTexCoord2d(texture270X[i], texture270Y[i]);
			}
			glNormal3d(normalX[i], normalY[i], normalZ[i]);
			glVertex3d(vertexX[i], vertexY[i], vertexZ[i]);
			if(rotation == 0)
			{
				glTexCoord2d(texture0X[i+4], texture0Y[i+4]);
			}
			else if(rotation == 90)
			{
				glTexCoord2d(texture90X[i+4], texture90Y[i+4]);
			}
			else if(rotation == 180)
			{
				glTexCoord2d(texture180X[i+4], texture180Y[i+4]);
			}
			else if(rotation == 270)
			{
				glTexCoord2d(texture270X[i+4], texture270Y[i+4]);
			}
			glNormal3d(normalX[i+4], normalY[i+4], normalZ[i+4]);
			glVertex3d(vertexX[i+4], vertexY[i+4], vertexZ[i+4]);
		}
	glEnd();
}
float MyRobot::getAngle()
{
	return this->angle;
}
double MyRobot::getX()
{
	return this->xCoord;
}
double MyRobot::getZ()
{
	return this->zCoord;
}
void MyRobot::rotate(float angle)
{
	if(this->getAngle() + angle == 360.0 || this->getAngle() + angle == -360.0)
		this->angle = 0;
	else 
		this->angle = this->getAngle() + angle;
}
void MyRobot::move(float distance)
{
	this->xCoord = this->getX() + distance * sin(this->getAngle()*PI/180);
	this->zCoord = this->getZ() + distance * cos(this->getAngle()*PI/180);
}

void MyRobot::calculatePoints()
{
	double beta = 45.0*PI/180.0;
	double alpha = 30.0*PI/180.0;
	double third = 1.0/3.0;
	double angle = 0.0;

	for(int s = 0; s < stacks+1; s++)
	{
		for(int i = 0; i < 4; i++)
		{
			angle = 45.0 + i * 30.0;
			if(angle == 45.0)
			{
				normalX.push_back(0.0 + s * cos(beta) / stacks); normalY.push_back(0.0); normalZ.push_back(1.0 - s * ((1.0 - sin(beta))/stacks));

				vertexX.push_back(0.5-s*((0.5-(cos(beta)*0.25))/stacks)); vertexY.push_back(s / stacks); vertexZ.push_back(0.5-s*((0.5-(sin(beta)*0.25))/stacks));
			}
			else if(angle == 75.0)
			{
				normalX.push_back(0.0 + s * cos(beta+alpha) / stacks); normalY.push_back(0.0); normalZ.push_back(1.0 - s * ((1.0 - sin(beta+alpha))/stacks));
 
				vertexX.push_back((0.5-third)-s*(((0.5-third)-(cos(beta+alpha)*0.25))/stacks)); vertexY.push_back(s / stacks); 	vertexZ.push_back(0.5-s*((0.5-(sin(beta+alpha)*0.25))/stacks));
			}
			else if(angle == 105.0)
			{
				normalX.push_back(0.0 + s * cos(beta+2*alpha) / stacks); normalY.push_back(0.0); normalZ.push_back(1.0 - s * ((1.0 - sin(beta+2*alpha))/stacks));
 
				vertexX.push_back(-(0.5-third)-s*((-(0.5-third)-(cos(beta+2*alpha)*0.25))/stacks)); vertexY.push_back(s / stacks); 	vertexZ.push_back(0.5-s*((0.5-(sin(beta+2*alpha)*0.25))/stacks));
			}
			else if(angle == 135.0)
			{
				normalX.push_back(0.0 + s * cos(beta+3+alpha) / stacks); normalY.push_back(0.0); normalZ.push_back(1.0 - s * ((1.0 - sin(beta+3*alpha))/stacks));
 
				vertexX.push_back(-0.5-(s*((-0.5-(cos(beta+3*alpha)*0.25))/stacks))); vertexY.push_back(s / stacks); vertexZ.push_back(0.5-(s*((0.5-(sin(beta+3*alpha)*0.25))/stacks)));
			}
		}
	}
}

void MyRobot::calculateTextures()
{
	double beta = 45.0*PI/180.0;
	double alpha = 30.0*PI/180.0;
	double third = 1.0/3.0;
	double angle = 0.0;

	for(int s = 0; s < stacks+1; s++)
	{
		for(int i = 0; i < 4; i++)
		{
			angle = 45.0 + i * 30.0;
			if(angle == 45.0)
			{
					//rotation 0
					texture0X.push_back(1.0 - (s * (1.0-(cos(beta)*0.25+0.5))/stacks));   texture0Y.push_back( 0.0 + (s * (((sin(-beta)*0.25)+0.5)/stacks)));

					//rotation 90
					texture90X.push_back(1.0 - (s * (1.0-(cos(beta)*0.25+0.5))/stacks)); texture90Y.push_back(1.0 - (s * (1.0-(sin(beta)*0.25+0.5))/stacks));

					//rotation 180
					texture180X.push_back(0.0 + (s * (((cos(-beta-3*alpha)*0.25)+0.5)/stacks))); texture180Y.push_back(0.0 + (s * (((sin(-beta-3*alpha)*0.25)+0.5)/stacks)));

					//rotation 270
					texture270X.push_back(0.0 + (s * (cos(3*beta)*0.25+0.5)/stacks)); texture270Y.push_back(1.0 - (s * (1.0-(sin(beta)*0.25+0.5))/stacks));
				
			}
			else if(angle == 75.0)
			{
					//rotation 0
					texture0X.push_back((2*third) - (s * ((2*third)-(cos(-beta-alpha)*0.25+0.5))/stacks));   texture0Y.push_back( 0.0 + (s * (((sin(-beta-alpha)*0.25)+0.5)/stacks)));
		
					//rotation 90
					texture90X.push_back(1.0 - (s * (1.0-((cos(beta-alpha)*0.25)+0.5))/stacks));   texture90Y.push_back((2*third) - (s * ((2*third)-((sin(beta-alpha)*0.25)+0.5))/stacks));
				
					//rotation 180
					texture180X.push_back(0.0 + (s * (((cos(5*beta-alpha)*0.25)+0.5)/stacks)));   texture180Y.push_back(third + (s * ((((sin(5*beta-alpha)*0.25)+0.5)-third)/stacks)));
			
					//rotation 270
					texture270X.push_back(third + (s * ((((cos(3*beta-alpha)*0.25)+0.5)-third)/stacks)));   texture270Y.push_back(1.0 - (s * (1.0-(sin(beta+alpha)*0.25+0.5))/stacks));	
			}
			else if(angle == 105.0)
			{
					//rotation 0
					texture0X.push_back(third + (s * ((((cos(-beta-2*alpha)*0.25)+0.5)-third)/stacks)));   texture0Y.push_back( 0.0 + (s * (((sin(-beta-2*alpha)*0.25)+0.5)/stacks)));
					
					//rotation 90
					texture90X.push_back(1.0 - (s * (1.0-((cos(beta-2*alpha)*0.25)+0.5))/stacks));   texture90Y.push_back(third + (s * ((((sin(beta-2*alpha)*0.25)+0.5)-third)/stacks)));
					
					//rotation 180
					texture180X.push_back(0.0 + (s * (((cos(5*beta-2*alpha)*0.25)+0.5)/stacks)));   texture180Y.push_back((2*third) - (s * ((2*third)-(sin(5*beta-2*alpha)*0.25+0.5))/stacks));
					
					//rotation 270
					texture270X.push_back((2*third) - (s * ((2*third)-(cos(3*beta-2*alpha)*0.25+0.5))/stacks));   texture270Y.push_back(1.0 - (s * (1.0-(sin(beta+2*alpha)*0.25+0.5))/stacks));
			}
					
			else if(angle == 135.0)
			{
					//rotation 0
					texture0X.push_back(0.0 + (s * (((cos(-beta-3*alpha)*0.25)+0.5)/stacks)));   texture0Y.push_back(0.0 + (s * (((sin(-beta-3*alpha)*0.25)+0.5)/stacks)));
		
					//rotation 90
					texture90X.push_back(1.0 - (s * (1.0-(cos(beta)*0.25+0.5))/stacks));   texture90Y.push_back(0.0 + (s * (((sin(-beta)*0.25)+0.5)/stacks)));			
					
					//rotation 180
					texture180X.push_back(0.0 + (s * (cos(3*beta)*0.25+0.5)/stacks));   texture180Y.push_back(1.0 - (s * (1.0-(sin(beta)*0.25+0.5))/stacks));
		
					//rotation 270
					texture270X.push_back(1.0 - (s * (1.0-(cos(beta)*0.25+0.5))/stacks));   texture270Y.push_back(1.0 - (s * (1.0-(sin(beta)*0.25+0.5))/stacks));	
			}
		}
	}
}