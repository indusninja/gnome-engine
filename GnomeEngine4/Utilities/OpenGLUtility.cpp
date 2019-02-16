#include "..\Misc\stdafx.h"

// Variables defining window size
int kWindowWidth = 800;
int kWindowHeight = 640;

// Variable defining window fullscreen state
bool fullscreen = false;

Color3f::Color3f()
{
	init(1.0f, 1.0f, 1.0f);
}

Color3f::Color3f(float R, float G, float B)
{
	init(R, G, B);
}

void Color3f::init(float R, float G, float B)
{
	Red = R;
	Green = G;
	Blue = B;
}

void Color3f::init(Color3f color)
{
	Red = color.Red;
	Green = color.Green;
	Blue = color.Blue;
}

// To access the current Window Height
int getWindowHeight(void)
{
	return kWindowHeight;
}

// To access the current Window Width
int getWindowWidth(void)
{
	return kWindowWidth;
}

// To access the current Window fullscreen state
bool isFullscreen(void)
{
	return fullscreen;
}

// To initialize the OpenGL window
void init(int* a, char* b[], const char* title, Camera cam)
{
	glutInit(a, b);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(kWindowWidth, kWindowHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(title);
	glClearColor(0.2f, 0.4f, 0.73f, 0.0f);
	glClearDepth(1.0f);
	toggleFullScreenMode();
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_NORMALIZE);

	setupLookAt(cam);
}

// To toggle the fullscreen state of the GL window
void toggleFullScreenMode(void)
{
	fullscreen = !fullscreen;

	if (fullscreen)
	{
		glutFullScreen();
		kWindowWidth = glutGet(GLUT_SCREEN_WIDTH);
		kWindowHeight = glutGet(GLUT_SCREEN_HEIGHT);
	}
	else
	{
		glutReshapeWindow(800, 640);
		glutPositionWindow(100, 100);
		kWindowWidth = glutGet(GLUT_WINDOW_WIDTH);
		kWindowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	}
}

// To setup a light
// TODO: currently very static method. The aim would be to extend so that the it
// can setup different lights with different parameters
void setupLight(float posx, float posy, float posz, float a)
{
	static GLfloat light0Ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	static GLfloat light0Diffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	static GLfloat light0Specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	static GLfloat light0Position[] = { posx, posy, posz, a };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0Position);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

// To setup the lookat for the camera as per values passed by the user
void setupLookAt(float posx,
				 float posy,
				 float posz,
				 float viewx,
				 float viewy,
				 float viewz,
				 float upx,
				 float upy,
				 float upz)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
	  70.0f, (GLfloat)kWindowWidth / (GLfloat)kWindowHeight, 0.1f, 1000.0f);

	gluLookAt(posx, posy, posz, viewx, viewy, viewz, upx, upy, upz);

	glMatrixMode(GL_MODELVIEW);
}

// To setup the lookat for the camera as per data from the Camera class
void setupLookAt(Camera cam)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
	  70.0f, (GLfloat)kWindowWidth / (GLfloat)kWindowHeight, 0.1f, 1000.0f);

	gluLookAt(cam.cameraPosition.x,
			  cam.cameraPosition.y,
			  cam.cameraPosition.z,
			  cam.cameraTarget.x,
			  cam.cameraTarget.y,
			  cam.cameraTarget.z,
			  cam.cameraUp.x,
			  cam.cameraUp.y,
			  cam.cameraUp.z);

	glMatrixMode(GL_MODELVIEW);
}

// DEBUG METHOD
// To draw a grid across the screen to get a perspective of where drawing is
// taking place in world
void drawGrid(float y_offset,
			  float gridSize,
			  int colorR,
			  int colorG,
			  int colorB)
{
	glDisable(GL_LINE_STIPPLE);
	for (float i = -500; i <= 500; i += gridSize)
	{
		glBegin(GL_LINES);
		glColor3ub(colorR, colorG, colorB);
		glVertex3f(-500, y_offset, i);
		glVertex3f(500, y_offset, i);
		glVertex3f(i, y_offset, -500);
		glVertex3f(i, y_offset, 500);
		glEnd();
	}
}

void drawArrow(Point3 fulcrum, float rotx, float roty, float rotz)
{
	float materialColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float specularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

	float vertices[7][3] = { { 0.05f, 0.0f, 0.05f },   { 0.05f, 0.0f, -0.25f },
							 { 0.10f, 0.0f, -0.25f },  { 0.00f, 0.0f, -0.35f },
							 { -0.10f, 0.0f, -0.25f }, { -0.05f, 0.0f, -0.25f },
							 { -0.05f, 0.0f, 0.05f } };
	glPushMatrix();
	// Translate the drawing to the fulcrum point
	glTranslatef(fulcrum.x, fulcrum.y - BALL_RADIUS + 0.001f, fulcrum.z);
	// Rotate about the fulcrum point for input angles
	glRotatef(rotx, 1.0f, 0.0f, 0.0f);
	glRotatef(roty, 0.0f, 1.0f, 0.0f);
	glRotatef(rotz, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
	glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
	glEnd();
	glPopMatrix();
}
