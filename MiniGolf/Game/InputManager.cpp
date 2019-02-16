#include "..\Game\stdafx.h"

// Constructor for class InputManager
InputManager::InputManager()
{
	theta_aroundYaxis = 0;
	menu.init();
}

// To handle the key down event
bool InputManager::KeyboardDown_handle(unsigned char key, int x, int y)
{
	bool flag = false;
	switch(key)
	{
		// Press 'Esc' key to activate Pause Menu
	case 27:
		menu.isActive = true;
		menu.setActiveMenu(7);
		break; 

	case 32:
		flag = true;
		break;

	default:
		break;
	}
	return flag;
}

// To handle the key up event
void InputManager::KeyboardUp_handle(unsigned char key, int x, int y)
{
	// Code to handle Keyboard Key-up event goes here
}

// To handle special inputs such as left, right arrow and function keys
bool InputManager::Special_handle(int key, int x, int y)
{
	if(key==GLUT_KEY_LEFT)
	{ 
		theta_aroundYaxis += arrowMoveStep; 
		if(theta_aroundYaxis<0) theta_aroundYaxis -= 360;
	}
	if(key==GLUT_KEY_RIGHT)
	{ 
		theta_aroundYaxis -= arrowMoveStep; 
		if(theta_aroundYaxis>360) theta_aroundYaxis += 360;
	}

	if(key==GLUT_KEY_F1)
		return true;			// toggle full-screen mode
	else
		return false;			// do not toggle full-screen mode
}

// To handle passive (non clicking) mouse movement in the GL scene
bool InputManager::PassiveMovement_handle(int x, int y)
{
	// Code to handle Passive Mouse Movement goes here
	return false;
}

// To handle Mouse (clicking) events in the GL scene
int InputManager::Mouse_handle(int button, int state, int x, int y)
{
	// Code to handle Mouse clicks goes here
	int flag = -1;
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		if((state==GLUT_UP)&&(menu.isActive))
			flag = menu.CheckClick(x, y);
		break;
	case GLUT_MIDDLE_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	}
	return flag;
}

// To get the direction vector where the arrow is supposed to be pointing
Vector3 InputManager::getDirection(int power)
{
	Vector3 direction(0,0,0);
	direction.x = sin(DEGREES_TO_RADIANS(theta_aroundYaxis-180));
	direction.z = cos(DEGREES_TO_RADIANS(theta_aroundYaxis-180));
	direction.ScalarMultiply((float)power);
	return direction;
}