#include "TPinterface.h"
#include "LightingScene.h"
#include <iostream>

TPinterface::TPinterface()
{
	angleOffset=15.0;
	distance=0.0;
}


void TPinterface::processKeyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'a':
		{ 
			cout << this->angleOffset << endl;
			((LightingScene *) scene)->robot->rotate(angleOffset);
			cout << "ROTATING LEFT : ANGLE IS NOW " << ((LightingScene *) scene)->robot->getAngle() << endl;
			break;
		}
		case 'd':
		{	
			((LightingScene*)scene)->robot->rotate(-this->angleOffset);
			cout << "ROTATING RIGHT : ANGLE IS NOW " << ((LightingScene *) scene)->robot->getAngle() << endl;
			break;
		}
		case 'w':
		{
			((LightingScene*)scene)->robot->move(this->distance);
			cout << "MOVING FORWARD : COORD IS NOW " << ((LightingScene *) scene)->robot->getX() << " " << ((LightingScene *) scene)->robot->getZ()  << endl;
			break;
		}
		case 's':
		{
			((LightingScene*)scene)->robot->move(-this->distance);
			cout << "MOVING BACKWARDS : COORD IS NOW " << ((LightingScene *) scene)->robot->getX() << " " << ((LightingScene *) scene)->robot->getZ()  << endl;
			break;
		}

	}
}

void TPinterface::initGUI()
{
	addColumn();
	GLUI_Panel *lightPanel = addPanel("Lights",1);
	addCheckboxToPanel(lightPanel,"Left Side",&(((LightingScene*) scene)->light0Check),1);
	addCheckboxToPanel(lightPanel,"Right Side",&(((LightingScene*) scene)->light1Check),2);
	addCheckboxToPanel(lightPanel,"The Sun",&(((LightingScene*) scene)->light2Check),3);
	
	addColumn();
	GLUI_Panel *clockPanel = addPanel("Clock",1);
	addButtonToPanel(clockPanel, "Clock", 5);
	
	addColumn();
	GLUI_Panel *wireframe = addPanel("Wireframe",1);
	GLUI_RadioGroup *group1 = addRadioGroupToPanel(wireframe, &(((LightingScene*) scene)->wireMode),6);
	addRadioButtonToGroup(group1,"Solid Mode");
	addRadioButtonToGroup(group1, "Wireframe Mode");
	
	addColumn();
	GLUI_Listbox *listTextures = addListbox("Textures ", &(((LightingScene*) scene)->textureId),7);
	listTextures->add_item(0," Directions Fixed");
	listTextures->add_item(1," Truncated 1");
	listTextures->add_item(2," Directions Original");
	listTextures->add_item(3, "Truncated 2");
	
	addColumn();
	GLUI_Panel *variables = addPanel("Variables",1);
	GLUI_EditText *angle = addEditTextToPanel(variables, "Angle", &this->angleOffset, 8);
	angle->set_float_limits(0, 90, GLUI_LIMIT_CLAMP);

	GLUI_EditText *distance = addEditTextToPanel(variables, "Distance", &this->distance, 9);
	distance->set_float_limits(0, 10, GLUI_LIMIT_CLAMP);
}

void TPinterface::processGUI(GLUI_Control *ctrl)
{
	printf ("GUI control id: %d\n  ",ctrl->user_id);
	switch (ctrl->user_id)
	{
		case 1:
		{
			(((LightingScene*) scene)->toggleLights());
			break;
		};

		case 2:
		{
			(((LightingScene*) scene)->toggleLights());
			break;
		};
		case 3:
		{
			(((LightingScene*) scene)->toggleLights());
			break;
		};
		case 5:
		{
			(((LightingScene*) scene)->toggleClock());
			break;
		}
	};
}

