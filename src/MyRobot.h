#ifndef MY_ROBOT
#define MY_ROBOT

#include "CGF/CGFobject.h"
#include <vector>

using namespace std;

class MyRobot : public CGFobject
{
	public:
		double slices, stacks, height;
		float angle;
		double xCoord, zCoord;
		vector<double> vertexX, vertexY, vertexZ;
		vector<double> normalX,normalY, normalZ;
		vector<double> texture0X, texture0Y, texture90X, texture90Y, texture180X, texture180Y, texture270X, texture270Y;
		vector<double> textureTop;

		MyRobot(double slices, double stack, double angle);
		void draw();
		void draw2(int wireMode);
		void quarter(int wireMode, int rotation);
		void calculatePoints();
		void calculateTextures();
		void calculateTexturesTop();
		float getAngle();
		double getX();
		double getZ();
		void rotate(float angle);
		void move(float distance);
};


#endif