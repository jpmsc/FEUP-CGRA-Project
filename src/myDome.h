#ifndef MY_DOME
#define MY_DOME

#include "CGF/CGFobject.h"

class myDome : public CGFobject {

	public:
		double slices, stacks;
		bool smooth;
		myDome(double slices, double stack, bool smooth);
		void draw();
};



#endif
