#include "LightingScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "Plane.h"


#include <math.h>

float pi = acos(-1.0);
float deg2rad=pi/180.0;

#define BOARD_HEIGHT 6.0
#define BOARD_WIDTH 6.4

//Positions for the three lights
float light0_pos[4] = {4, 6.0, 1.0, 1.0};
float light1_pos[4] = {10.5, 6.0, 1.0, 1.0};
float light2_pos[4] = {-3.0, 5.0, 7.5, 1.0};

//float light3_pos[4] = {4, 6.0, 5.0, 1.0};

// Global ambient light
float globalAmbientLight[4]= {0.4,0.4,0.4,1.0};

// number of divisions
#define BOARD_A_DIVISIONS 150
#define BOARD_B_DIVISIONS 200

// Coefficients for material A
float ambA[3] = {0.2, 0.2, 0.2};
float difA[3] = {0.6, 0.6, 0.6};
float specA[3] = {0.8, 0.8, 0.8};
float shininessA = 120.f;

// Coefficients for material B
float ambB[3] = {0.2, 0.2, 0.2};
float difB[3] = {0.6, 0.6, 0.6};
float specB[3] = {0.8, 0.8, 0.8};
float shininessB = 120.f;

// Coefficients for material C
float ambC[3] = {0.523, 0.369, 0.259};
float difC[3] = {0.523, 0.369, 0.259};
float specC[3] = {0.223, 0.169, 0.159};
float shininessC = 120.f;

// Coefficients for material D
float ambD[3] = {0.625, 0.625, 0.625};
float difD[3] = {0.625, 0.625, 0.625};
float specD[3] = {0.725, 0.725, 0.725};
float shininessD = 300.f;

// Coefficients for material E
float ambE[3] = {0.47, 0.322, 0.129};
float difE[3] = {0.87, 0.722, 0.529};
float specE[3] = {1, 1, 1};
float shininessE = 500.f;

//Coefficients for the floor
float ambFloor[3] = {0.5, 0.5, 0.5};
float difFloor[3] = {0.87, 0.722, 0.529};
float specFloor[3] = {0.0, 0.0, 0.0};
float shininessFloor = 10.f;

float ambientNull[4]={0,0,0,1};
float yellow[4]={1,1,0,1};

void LightingScene::toggleClock()
{
	if(this->clockRunning == 1)
		this->clockRunning = 0;
	else if(this->clockRunning == 0)
		this->clockRunning = 1;
}

void LightingScene::toggleLights()
{
	if(this->light0Check == 1)
		this->light0->enable();
	else if(this->light0Check == 0)
		this->light0->disable();

	if(this->light1Check == 1)
		this->light1->enable();
	else if(this->light1Check == 0)
		this->light1->disable();

	if(this->light2Check == 1)
		this->light2->enable();
	else if(this->light2Check == 0)
		this->light2->disable();
}

void LightingScene::update(unsigned long upTime)
{
	unsigned long deltaTime = upTime - time;
	this->time = upTime;
	if(this->clockRunning == 1)
	{
		secondHand->setAngle(secondHand->getAngle() + (6.0*(deltaTime/1000.0)));
		minuteHand->setAngle(minuteHand->getAngle() + (6.0*(deltaTime/60000.0)));
		hourHand->setAngle(hourHand->getAngle() + (6.0*(deltaTime/3600000.0)));
	}
}

void LightingScene::chooseTexture(int id)
{
	switch(id)
	{
		case 0:
		{
			this->robotAppearance->setTexture("robot3.jpg");
			break;
		};
		case 1:
		{
			this->robotAppearance->setTexture("robot2.png");
			break;
		};
		case 2:
		{
			this->robotAppearance->setTexture("robot1.jpg");
			break;
		};
		case 3:
		{
			this->robotAppearance->setTexture("robot4.png");
			break;
		}

	}
}

void LightingScene::init() 
{
	// Enables lighting computations
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	// Sets up some lighting parameters
	// Computes lighting only using the front face normals and materials
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);  
	
	// Define ambient light (do not confuse with ambient component of individual lights)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);  
	
	// Declares and enables two lights, with null ambient component
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->setAmbient(ambientNull);
	light0->enable();

	light1 = new CGFlight(GL_LIGHT1, light1_pos);
	light1->setAmbient(ambientNull);
	light1->enable();
	
	light2 = new CGFlight(GL_LIGHT2, light2_pos);
	light2->setAmbient(ambientNull);

	light2->enable();

	// Uncomment below to enable normalization of lighting normal vectors
	glEnable (GL_NORMALIZE);

	//Declares scene elements
	table = new myTable();
	wall = new Plane(200);
	floor = new Plane(200);
	impostor = new Plane(400);
	cylinder = new myCylinder(12,10,true);
	flat_cylinder = new myCylinder(12,10,false);
	dome = new myDome(8,5,true);
	clock = new myClock(20,10,true);
	minuteHand = new myClockHand(0.0, 0.7);
	hourHand = new myClockHand(0.0, 0.4);
	secondHand = new myClockHand(0.0,0.9);
	boardA = new Plane(BOARD_A_DIVISIONS);
	boardB = new Plane(BOARD_B_DIVISIONS);
	robot = new MyRobot(12.0,20.0,0.0);
	
	//Declares materials
	materialA = new CGFappearance(ambA,difA,specA,shininessA);
	materialB = new CGFappearance(ambB,difB,specB,shininessB);
	materialC = new CGFappearance(ambC,difC,specC,shininessC);
	materialD = new CGFappearance(ambD,difD,specD,shininessD);
	materialE = new CGFappearance(ambE,difE,specE,shininessE);

	//textures
	tableAppearance = new CGFappearance(ambC,difC,specC,shininessC);
	tableAppearance->setTexture("table.png");
	
	slidesAppearance = new CGFappearance(ambB,difB,specB,shininessB);
	slidesAppearance->setTexture("slides.png");
	
	boardAppearance = new CGFappearance(ambA,difA,specA,shininessA);
	boardAppearance->setTexture("board.png");

	windowAppearance = new CGFappearance();
	windowAppearance->setTexture("window.png");

	floorAppearance = new CGFappearance(ambFloor, difFloor, specFloor, shininessFloor);
	floorAppearance->setTexture("floor.png");

	clockAppearance = new CGFappearance();
	clockAppearance->setTexture("clock.png");

	view = new CGFappearance();
	view->setTexture("view.jpg");

	robotAppearance = new CGFappearance();
	robotAppearance->setTexture("robot1.jpg");

	LightingScene::time = 0;
	LightingScene::sceneVar=0;
	LightingScene::clockRunning = 1;
	LightingScene::wireMode = 0;
	setUpdatePeriod(100);
}

void LightingScene::display() 
{

	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();

	light0->draw();
	light1->draw();
	light2->draw();
	
	// Draw axis
	axis.draw();

	// ---- END Background, camera and axis setup

	// ---- BEGIN Primitive drawing section
	
	//clock
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTranslated(7.5,8,0);
		glScaled(1,1,0.4);
		materialD->apply();
		clockAppearance->apply();
		clock->draw();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//clock -> minute hand
	glPushMatrix();
		glTranslated(7.5,8,0.5);
		minuteHand->draw();
	glPopMatrix();

	//clock -> hour hand
	glPushMatrix();
		glTranslated(7.5,8,0.5);
		hourHand->draw();
	glPopMatrix();

	//clock -> second hand
	glPushMatrix();
		glTranslated(7.5,8,0.5);
		secondHand->draw();
	glPopMatrix();
	
	
	//cilindro
	glPushMatrix();
		glTranslated(6,2,5);
		glRotated(-90, 1, 0, 0);
		glScaled(1,1,4);
		materialD->apply();
		cylinder->draw();
	glPopMatrix();
	
	glPushMatrix();
		glTranslated(12,2,5);
		glRotated(-90, 1, 0, 0);
		glScaled(1,1,4);
		materialD->apply();
		flat_cylinder->draw();
	glPopMatrix();
	
	//Floor
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
		glTranslated(7.5,0,7.5);
		glScaled(15,0.2,15);
		floorAppearance->setTextureWrap(GL_REPEAT,GL_REPEAT);
		floorAppearance->apply();
		floor->draw2(12.0,10.0,0.0,0.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	//Impostor
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
		glTranslated(-15,4,8);
		glRotated(180.0,1,0,0);
		glRotated(-90.0,0,0,1);
		glRotated(-90.0,0,1,0);
		glScaled(30,0.2,25);	
		view->setTextureWrap(GL_CLAMP,GL_CLAMP);
		view->apply();
		impostor->draw2(1.0,1.0,0.0,0.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	//LeftWall
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
		glTranslated(0,4,7.5);
		glRotated(-90.0,0,0,1);
		glRotated(-90.0,0,1,0);
		glRotated(180.0,0.0,1.0,0.0);
		glScaled(15,0.2,8);	
		windowAppearance->setTextureWrap(GL_CLAMP,GL_CLAMP);
		windowAppearance->apply();
		wall->draw3(3.6,1.8,1.3,0.5);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	
	//PlaneWall
	glPushMatrix();
		glTranslated(7.5,4,0);
		glRotated(90.0,1,0,0);
		glScaled(15,0.2,8);
		wall->draw();
	glPopMatrix();

	// Board A
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
		glTranslated(4,4,0.2);
		glScaled(BOARD_WIDTH,BOARD_HEIGHT,1);
		glRotated(90.0,1,0,0);
		boardAppearance->setTextureWrap(GL_CLAMP,GL_CLAMP);
		boardAppearance->apply();
		boardA->draw2(1.0,1.2,0.0,0.1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	//Board B
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
		glTranslated(10.5,4,0.2);
		glScaled(BOARD_WIDTH,BOARD_HEIGHT,1);
		glRotated(90.0,1,0,0);
		slidesAppearance->apply();
		boardB->draw();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	//First Table
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
		glTranslated(2.5,0,8);
		glScaled(1.0,1.0,1.0);
		tableAppearance->apply();
		table->drawTable();
		materialD->apply();
		table->drawLegs();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	//Second Table
	glPushMatrix();
		glTranslated(9,0,8);
		tableAppearance->apply();
		table->drawTable();
		materialD->apply();
		table->drawLegs();
	glPopMatrix();
	
	
	glPushMatrix();
		glScaled(3.0,3.0,3.0);
		glEnable(GL_TEXTURE_2D);
			this->chooseTexture(this->textureId);
			robotAppearance->apply();
			robot->draw2(this->wireMode);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	// ---- END Primitive drawing section
	
	glutSwapBuffers();
}

LightingScene::~LightingScene() 
{
	delete(light0);
	delete(light1);

	delete(table);
	delete(wall);
	delete(boardA);
	delete(boardB);
	delete(materialA);
	delete(materialB);
}