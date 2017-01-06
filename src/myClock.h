#ifndef MY_CLOCK
#define MY_CLOCK

#include "CGF/CGFobject.h"

class myClock : public CGFobject {

	public:
		double slices, stacks, height;
		bool smooth;
		myClock(double slices, double stack, bool smooth); 
		void draw();
		void draw_circle(double radius, double num_vertex);

};



#endif
