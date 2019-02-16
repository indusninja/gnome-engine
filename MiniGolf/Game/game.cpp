#include "..\Game\stdafx.h"
using namespace std;

GLvoid glDrawScene(GLvoid);
GLvoid glUpdateScene(int);

void glKeyboardDown(unsigned char, int, int);
void glSpecial(int, int, int);
void glMouse(int button, int state, int x, int y);

LevelManager levelManager;

int main(int argc, char *argv[])
{
	if(argc==1)
	{
		cout<<"Invalid command syntax. Please use correct syntax for command : <program name> <data file name>."<<endl;
		exit(1);
	}

	levelManager.readLevelsFromFile(argv[1]);

	init(&argc, argv, "MiniGolf - by Prakash Prasad", levelManager.inputManager.camera);

	levelManager.inputManager.menu.RearrangeMenus();

	setupLight(0.0f, 5.0f, 0.0f, 1.0f);
	vector<string> assets;
	assets.push_back("Assets/ground_grass_512_tile.tga");
	initAssets(assets);

	glutDisplayFunc(glDrawScene);
	glutTimerFunc(1000/fps, glUpdateScene, 1);
	glutKeyboardFunc(glKeyboardDown);
	glutSpecialFunc(glSpecial);
	glutMouseFunc(glMouse);

	glutMainLoop();
	return 0;
}

void glUpdateScene(int value)
{
	levelManager.updateCurrentLevel(1/fps);
	glutPostRedisplay();
	glutTimerFunc(1000/fps, glUpdateScene, value);
}

GLvoid glDrawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	levelManager.drawCurrentLevel();
	glPopMatrix();
	glutSwapBuffers();
}

void glKeyboardDown(unsigned char key, int x, int y)
{
#ifdef _DEBUG
	Vector3 HighBall = levelManager.inputManager.getDirection(100);
	HighBall.y = 100;
	if(key==77 || key==109)
		levelManager.ball->setAcceleration(HighBall);
	if(key==84 || key==116)
		levelManager.setBallAcceleration(true);
#endif
	if(levelManager.inputManager.KeyboardDown_handle(key, x, y))
		levelManager.setBallAcceleration(false);
	glutPostRedisplay();
}

void glSpecial(int key, int x, int y)
{
	if(levelManager.inputManager.Special_handle(key, x, y))
	{
		toggleFullScreenMode();
		levelManager.inputManager.menu.RearrangeMenus();
	}
	glutPostRedisplay();
}

void glMouse(int button, int state, int x, int y)
{
	int MouseState = levelManager.inputManager.Mouse_handle(button, state, x, y);
	switch(MouseState)
	{
	// If a number in 20's was returned, that means a course has been selected from the "Play Course" Menu
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
		levelManager.currentLevel = 0;
		levelManager.resetToLevel(0);
		levelManager.playCurrentHoleOnly = false;
		break;
	// If a number in 30's or above was returned, that means a hole has been selected from the "Play Hole" Menu
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
	case 58:
	case 59:
		levelManager.currentLevel = MouseState - 30;
		levelManager.resetToLevel(MouseState - 30);
		levelManager.playCurrentHoleOnly = true;
		break;
	default:
		break;
	}
	if(MouseState!=-1)
		glutPostRedisplay();
}