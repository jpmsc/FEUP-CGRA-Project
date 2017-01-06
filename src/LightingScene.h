#ifndef LightingScene_H
#define LightingScene_H

#include "CGFscene.h"
#include "CGFappearance.h"
#include "ExampleObject.h"
#include "Plane.h"
#include "myCylinder.h"
#include "myDome.h"
#include "myClock.h"
#include "myClockHand.h"
#include "MyRobot.h"
#include <iostream>

class LightingScene : public CGFscene
{
public:
	void init();
	void display();
	virtual void update(unsigned long);
	void toggleClock();
	void toggleLights();
	void chooseTexture(int id);

	unsigned long time;
	int sceneVar;
	int light0Check;
	int light1Check;
	int light2Check;
	int light3Check;
	int clockRunning;
	int wireMode;
	int textureId;
	int angleOffset;

	CGFlight* light0;
	CGFlight* light1;
	CGFlight* light2;
	CGFlight* light3;

	myTable* table;
	myCylinder* cylinder;
	myCylinder* flat_cylinder;
	myDome* dome;
	Plane* wall;
	Plane* floor;
	Plane* impostor;
	Plane* boardA;
	Plane* boardB;
	myClock* clock;
	myClockHand* minuteHand;
	myClockHand* hourHand;
	myClockHand* secondHand;
	
	MyRobot* robot;

	CGFappearance* materialA;
	CGFappearance* materialB;
	CGFappearance* materialC;
	CGFappearance* materialD;
	CGFappearance* materialE;

	CGFappearance* tableAppearance;
	CGFappearance* slidesAppearance;
	CGFappearance* boardAppearance;
	CGFappearance* windowAppearance;
	CGFappearance* floorAppearance;
	CGFappearance* clockAppearance;
	CGFappearance* view;
	CGFappearance* robotAppearance;

	~LightingScene();
};

#endif