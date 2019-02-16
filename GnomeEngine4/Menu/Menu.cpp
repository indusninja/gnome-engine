#include "..\Misc\stdafx.h"
using namespace std;

void Menu::AddButton(int index, Button btn)
{
	mButtons[index] = btn;
}

int Menu::Length(void)
{
	return (int)mButtons.size();
}

void Menu::ArrangeButtons(void)
{
	int viewportWidth = getWindowWidth();
	int viewportHeight = getWindowHeight();

	int individualBtnWidth = individualBtnWidth = (int)(viewportWidth / 2);
	int individualBtnHeight = 40;

	if (mButtons.size() != 1)
		individualBtnHeight =
		  (int)(viewportHeight / ((mButtons.size() * 2) + 1));

	int posX = (viewportWidth / 2) - (individualBtnWidth / 2);
	int posY = viewportHeight - (individualBtnHeight * 2);
	if (mButtons.size() != 1)
		posY = individualBtnHeight;

	for (map<int, Button>::iterator i = mButtons.begin(); i != mButtons.end();
		 i++)
	{
		i->second.init(posX, posY, individualBtnWidth, individualBtnHeight);
		posY += (individualBtnHeight * 2);
	}
}

int Menu::CheckClick(int x, int y)
{
	int ButtonClicked = -1;
	for (map<int, Button>::iterator i = mButtons.begin(); i != mButtons.end();
		 i++)
		if (i->second.CheckClick(x, y))
			ButtonClicked = i->first;
	return ButtonClicked;
}

void Menu::Draw(void)
{
	// Render logic for individual buttons goes here
	for (map<int, Button>::iterator i = mButtons.begin(); i != mButtons.end();
		 i++)
		i->second.Draw();
}

void Menu::Print(void)
{
	for (map<int, Button>::iterator i = mButtons.begin(); i != mButtons.end();
		 i++)
		i->second.Print();
}
