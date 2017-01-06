#ifndef MY_CYLINDER
#define MY_CYLINDER

#include "CGF/CGFobject.h"

class myCylinder : public CGFobject {

	public:
		double slices, stacks,height;
		bool smooth;
		myCylinder(double slices, double stack, bool smooth);
		void draw();

};



#endif
