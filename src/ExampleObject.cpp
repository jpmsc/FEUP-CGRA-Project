#include "ExampleObject.h"

void ExampleObject::draw() 
{
	glBegin(GL_QUADS);
		glVertex3d(0,0,0);
		glVertex3d(4,0,0);
		glVertex3d(4,3,0);
		glVertex3d(0,3,0);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3d(-1,3,0);
		glVertex3d(5,3,0);
		glVertex3d(2,4,0);
	glEnd();
}

void myUnitCube::draw()
{
	//glEnable(GL_NORMALIZE);
	glPushMatrix(); //base
		glNormal3f(0,0,1);
		glTranslated(1,0,0);	
		glRotated(-180,0,1,0);
		glRectd(0,0,1,1);
	glPopMatrix();

	glPushMatrix(); //frente
		glNormal3f(0,0,1);
		glTranslated(0,0,1);
		glRectd(0,0,1,1);
	glPopMatrix();

	glPushMatrix(); //topo
		glNormal3f(0,0,1);
		glTranslated(0,1,1);
		glRotated(-90,1,0,0);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3d(0.0,0.0,0.0);

			glTexCoord2f(1.0, 0.0);
			glVertex3d(1.0,0.0,0.0);
			
			glTexCoord2f(1.0, 1.0); 
			glVertex3d(1.0,1.0,0.0);

			glTexCoord2f(0.0, 1.0); 
			glVertex3d(0.0,1.0,0.0);
		glEnd();
	glPopMatrix();
	
	glPushMatrix(); //baixo
		glNormal3f(0,0,1);
		glRotated(-270,1,0,0);
		glRectd(0,0,1,1);
	glPopMatrix();
	
	glPushMatrix(); //lado0
		glNormal3f(0,0,1);
		glRotated(-90,0,1,0);
		glRectd(0,0,1,1);
	glPopMatrix();

	glPushMatrix(); //lado1
		glNormal3f(0,0,1);
		glTranslated(1,0,1);
		glRotated(90,0,1,0);
		glRectd(0,0,1,1);
	glPopMatrix();
}

void myTable::drawTable()
{
	//tampo da mesa
	glPushMatrix();
		glTranslated(0, 3.5 ,0);
		glScaled(5, 0.3, 3);
		aCube.draw();
	glPopMatrix();
}

void myTable::drawLegs()
{
	//pernas
	glPushMatrix();
		glScaled(0.3, 3.5, 0.3);
		aCube.draw();
	glPopMatrix();
	
	glPushMatrix();	
		glTranslated(4.7 ,0 ,0);
		glScaled(0.3, 3.5, 0.3);
		aCube.draw();
	glPopMatrix();

	glPushMatrix();	
		glTranslated(0, 0, 2.7);
		glScaled(0.3, 3.5, 0.3);
		aCube.draw();
	glPopMatrix();

	glPushMatrix();	
		glTranslated(4.7, 0, 2.7);
		glScaled(0.3, 3.5, 0.3);
		aCube.draw();
	glPopMatrix();
}
		
void myFloor::draw()
{
	glPushMatrix();	
		glScaled(8, 0.1, 6);
		bCube.draw();
	glPopMatrix();
}

void myChair::draw()
{
	glPushMatrix();//tampo
		glTranslated(0,2.5,0);
		glScaled(2.5,0.2,2.5);
		cCube.draw();
	glPopMatrix();

	glPushMatrix();//costas
		glTranslated(0,2.7,0);
		glScaled(2.5,3,0.2);
		cCube.draw();
	glPopMatrix();

	glPushMatrix(); //perna base
		glScaled(0.2,2.5,0.2);
		cCube.draw();
	glPopMatrix();

	glPushMatrix();
		glTranslated(2.3,0,0);
		glScaled(0.2,2.5,0.2);
		cCube.draw();
	glPopMatrix();

	glPushMatrix();
		glTranslated(0,0,2.3);
		glScaled(0.2,2.5,0.2);
		cCube.draw();
	glPopMatrix();

	glPushMatrix();
		glTranslated(2.3,0,2.3);
		glScaled(0.2,2.5,0.2);
		cCube.draw();
	glPopMatrix();

}