#ifndef EXAMPLEOBJECT_H
#define EXAMPLEOBJECT_H

#include "CGFobject.h"
#include "CGFappearance.h"

class ExampleObject: public CGFobject {
	public:
		void draw();
};

#endif

class myUnitCube : public CGFobject {
	public:
		void draw();
};

class myTable : public CGFobject {
	myUnitCube aCube;
	public:
		void drawTable();
		void drawLegs();
};

class myFloor : public CGFobject {
	myUnitCube bCube;
	public:
		void draw();
};

class myChair : public CGFobject {
	myUnitCube cCube;
	public:
		void draw();
};