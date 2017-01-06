#ifndef MY_CLOCKHAND
#define MY_CLOCKHAND

#include "CGF/CGFobject.h"

class myClockHand : public CGFobject {

	public:
		float angle;
		float lenght;
		myClockHand(float angle, float lenght); 
		void setAngle(float angle);
		float getAngle();
		void draw();	
};



#endif
