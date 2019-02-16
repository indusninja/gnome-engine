#include "..\Misc\stdafx.h"
using namespace std;

void Button::init(string strText, Color3f textC, Color3f backC)
{
	text = strText;
	textColor.init(textC);
	backColor.init(backC);
}

void Button::init(string strText,
				  float text_R,
				  float text_G,
				  float text_B,
				  float back_R,
				  float back_G,
				  float back_B)
{
	text = strText;
	textColor.init(text_R, text_G, text_B);
	backColor.init(back_R, back_G, back_B);
}

void Button::init(int pos_X, int pos_Y, int w, int h)
{
	topLeftX = pos_X;
	topLeftY = pos_Y;
	width = w;
	height = h;
}

bool Button::CheckClick(int x, int y)
{
	if ((x >= topLeftX) && (x <= topLeftX + width) && (y >= topLeftY) &&
		(y <= topLeftY + height))
		return true;
	else
		return false;
}

void Button::Draw(void)
{
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(getWindowWidth(), 0, getWindowHeight(), 0, -100.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glLoadIdentity();
	glColor3f(backColor.Red, backColor.Green, backColor.Blue);
	glBegin(GL_LINES);
	glVertex2f(topLeftX, topLeftY);
	glVertex2f(topLeftX + width, topLeftY);
	glVertex2f(topLeftX + width, topLeftY);
	glVertex2f(topLeftX + width, topLeftY + height);
	glVertex2f(topLeftX + width, topLeftY + height);
	glVertex2f(topLeftX, topLeftY + height);
	glVertex2f(topLeftX, topLeftY + height);
	glVertex2f(topLeftX, topLeftY);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	glColor3f(textColor.Red, textColor.Green, textColor.Blue);
	glRasterPos2f(topLeftX + width / 2 + (text.length() * 3),
				  topLeftY + height / 2);
	for (int i = 0; i < (int)text.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Button::Print(void)
{
	cout << "Text: " << text << endl;
	cout << "Text Color: " << textColor.Red << ", " << textColor.Green << ", "
		 << textColor.Blue << endl;
	cout << "Back Color: " << backColor.Red << ", " << backColor.Green << ", "
		 << backColor.Blue << endl;
	cout << "Position: " << topLeftX << ", " << topLeftY << endl;
	cout << "Size: " << width << ", " << height << endl;
}
