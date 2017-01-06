#pragma once

#include "CGF\CGFobject.h"
class Plane
{
public:
	Plane(void);
	Plane(int);
	~Plane(void);
	void draw();
	void draw2(double xScale, double zScale, double xOffset, double zOffset);
	void draw3(double xScale, double zScale, double xOffset, double zOffset);

private:
	int _numDivisions; // Number of triangles that constitute rows/columns
};

