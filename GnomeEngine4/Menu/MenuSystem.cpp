#include "..\Game\stdafx.h"
using namespace std;

int Power = 0, powerStep = 1;

void MenuSystem::init(void)
{
	activeMenuIndex = 0;
	isActive = true;
	Menu startMenu;
	Button btn;
	btn.init("Load Game", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	startMenu.AddButton(0, btn);
	btn.init("High Scores", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	startMenu.AddButton(1, btn);
	btn.init("Help", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	startMenu.AddButton(2, btn);
	btn.init("About", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	startMenu.AddButton(3, btn);
	btn.init("Exit", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	startMenu.AddButton(4, btn);
	mMenus[0] = startMenu;

	Menu mLoadGame;
	btn.init("Play Course", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	mLoadGame.AddButton(0, btn);
	btn.init("Play Hole", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	mLoadGame.AddButton(1, btn);
	btn.init("Back", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	mLoadGame.AddButton(2, btn);
	mMenus[1] = mLoadGame;

	Menu mPlayCourse;
	btn.init("Back", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	mPlayCourse.AddButton(0, btn);
	mMenus[2] = mPlayCourse;

	Menu mPlayHole;
	btn.init("Back", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	mPlayHole.AddButton(0, btn);
	mMenus[3] = mPlayHole;

	Menu mHighScore;
	btn.init("Back", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	mHighScore.AddButton(0, btn);
	mMenus[4] = mHighScore;

	Menu mHelp;
	btn.init("Back", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	mHelp.AddButton(0, btn);
	mMenus[5] = mHelp;

	Menu mAbout;
	btn.init("Back", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	mAbout.AddButton(0, btn);
	mMenus[6] = mAbout;

	Menu mEscMenu;
	btn.init("Resume Game", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	mEscMenu.AddButton(0, btn);
	btn.init("Exit to Menu", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	mEscMenu.AddButton(1, btn);
	btn.init("Exit to Desktop", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	mEscMenu.AddButton(2, btn);
	mMenus[7] = mEscMenu;

	RearrangeMenus();
	ResetScores();
}
void MenuSystem::init(string courseName, vector<string> holes)
{
	Button btn;

	Menu mPlayCourse;
	btn.init(courseName, 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	mPlayCourse.AddButton(0, btn);
	btn.init("Back", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	mPlayCourse.AddButton(1, btn);
	mMenus[2] = mPlayCourse;

	Menu mPlayHole;
	for(int i=0;i<(int)holes.size();i++)
	{
		btn.init(holes[i], 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
		mPlayHole.AddButton(i, btn);	
	}
	btn.init("Back", 0.75f, 0.75f, 1.0f, 0.4f, 0.4f, 0.4f);
	mPlayHole.AddButton((int)holes.size(), btn);
	mMenus[3] = mPlayHole;

	RearrangeMenus();
}

void MenuSystem::ResetScores(void)
{
	mTotalScore = 0;
	ResetHoleStrokes();
}

void MenuSystem::RearrangeMenus(void)
{
	for(map<int, Menu>::iterator i=mMenus.begin();i!=mMenus.end();i++)
		i->second.ArrangeButtons();
}

void MenuSystem::setActiveMenu(int index)
{
	activeMenuIndex = index;
	if(index>=0)
		isActive = true;
	else
		isActive = false;
}

int MenuSystem::getActiveMenu(void)
{
	return activeMenuIndex;
}

void MenuSystem::updatePower(void)
{
	Power += powerStep;
	if(Power>=20)
		powerStep = -1;
	if(Power<=0)
		powerStep = 1;
}

int MenuSystem::getPower(void)
{
	return Power;
}

void MenuSystem::incrementStroke(void)
{
	mHoleScore++;
	//mHolePar = par;
	mTotalScore++;
}

void MenuSystem::ResetHoleStrokes(void)
{
	mHoleScore = 0;
}

void MenuSystem::SetHolePar(int par)
{
	mHolePar = par;
}

// Take actions for the buttons selected
int MenuSystem::CheckClick(int x, int y)
{
	int flag = -1, MenuState = -1;
	switch(activeMenuIndex)
	{
	case 0:
		// Start Menu
		switch(mMenus[0].CheckClick(x, y))
		{
		case 0:
			// Load Game Button clicked
			activeMenuIndex = 1;
			flag = 1;
			break;
		case 1:
			// High Scores Button clicked
			activeMenuIndex = 4;
			flag = 4;
			break;
		case 2:
			// Help Button clicked
			activeMenuIndex = 5;
			flag = 5;
			break;
		case 3:
			// About Button clicked
			activeMenuIndex = 6;
			flag = 6;
			break;
		case 4:
			// Exit Button clicked
			exit(1);
			break;
		}
		break;
	case 1:
		// Load Game Menu
		switch(mMenus[1].CheckClick(x, y))
		{
		case 0:
			// "Play Course" Button clicked
			activeMenuIndex = 2;
			flag = 2;
			break;
		case 1:
			// "Play Hole" Button clicked
			activeMenuIndex = 3;
			flag = 3;
			break;
		case 2:
			// Back Button clicked
			activeMenuIndex = 0;
			flag = 0;
			break;
		}
		break;
	case 2:
		// "Play Course" Menu
		MenuState = mMenus[2].CheckClick(x, y);
		if(MenuState==(mMenus[2].Length()-1))
		{
			// Back button was clicked
			activeMenuIndex = 1;
			flag = 1;
		}
		if( (MenuState!=(mMenus[2].Length()-1)) && (MenuState!=-1) )
		{
			isActive = false;
			flag = 20 + MenuState;
		}
		break;
	case 3:
		// Play Hole Menu
		MenuState = mMenus[3].CheckClick(x, y);
		if(MenuState==(mMenus[3].Length()-1))
		{
			// Back button was clicked
			activeMenuIndex = 1;
			flag = 1;
		}
		if( (MenuState!=(mMenus[3].Length()-1)) && (MenuState!=-1) )
		{
			isActive = false;
			flag = 30 + MenuState;
		}
		break;
	case 4:
		// High Score Menu
		switch(mMenus[4].CheckClick(x, y))
		{
		case 0:
			// Back Button clicked
			activeMenuIndex = 0;
			flag = 0;
			break;
		}
		break;
	case 5:
		// Help Menu
		switch(mMenus[5].CheckClick(x, y))
		{
		case 0:
			// Back Button clicked
			activeMenuIndex = 0;
			flag = 0;
			break;
		}
		break;
	case 6:
		// About Menu
		switch(mMenus[6].CheckClick(x, y))
		{
		case 0:
			// Back Button clicked
			activeMenuIndex = 0;
			flag = 0;
			break;
		}
		break;
	case 7:
		// Escape Menu
		switch(mMenus[7].CheckClick(x, y))
		{
		case 0:
			// Resume Game Button clicked
			isActive = false;
			flag = 0;
			break;
		case 1:
			// Exit to Menu Button clicked
			activeMenuIndex = 0;
			flag = 0;
			break;
		case 2:
			// Exit to Desktop clicked
			exit(1);
			break;
		}
		break;
	}
	if(flag==0)
		ResetScores();
	return flag;
}

void MenuSystem::Draw(bool stationary, bool playCurrentHoleOnly)
{
	if(isActive)
		mMenus[activeMenuIndex].Draw();
	else
		DrawHUD(stationary, playCurrentHoleOnly);
}

void MenuSystem::DrawHUD(bool stationary, bool playCurrentHoleOnly)
{
	glDisable( GL_LIGHTING );
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho( -100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f );
	glMatrixMode( GL_MODELVIEW );
	if(stationary)
	{
		float powerRectangleLength = 60;
		float powerRectangleWidth = 10;
		float powerRectangleTopLeft[] = { -90, 90 };

		glPushMatrix();
		glLoadIdentity();
		glColor3f( 0.75f, 0.75f, 0.1f );
		glBegin( GL_QUADS );
		glVertex2f(powerRectangleTopLeft[0], powerRectangleTopLeft[1]);
		glVertex2f(powerRectangleTopLeft[0] + (Power*3), powerRectangleTopLeft[1]);
		glVertex2f(powerRectangleTopLeft[0] + (Power*3), powerRectangleTopLeft[1] - powerRectangleWidth);
		glVertex2f(powerRectangleTopLeft[0], powerRectangleTopLeft[1] - powerRectangleWidth);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glLoadIdentity();
		glTranslatef( -90.0f, -90.0f, 0.0f );
		glScalef( 0.05f, 0.05f, 0.05f );
		char *message = "Press space-bar to select stroke power";
		int index = 0;
		glColor3f( 0.75f, 0.75f, 1.0f );
		while( *( message + index++ ) != '\0' )
			glutStrokeCharacter( GLUT_STROKE_ROMAN, *( message + index -1 ));
		glPopMatrix();
	}

		glPushMatrix();
		glLoadIdentity();
		glTranslatef( 30.0f, 90.0f, 0.0f );
		glScalef( 0.04f, 0.04f, 0.04f );
		stringstream MessageConstructor;
		MessageConstructor << "Stroke: ";
		int score = mHoleScore - mHolePar;
		switch(score)
		{
		case -4:
			//Condor: four strokes under par
			MessageConstructor << "Condor";
			break;
		case -3:
			//Albatross: Three shots less than par
			MessageConstructor << "Albatross";
			break;
		case -2:
			// Eagle: Two shots less
			MessageConstructor << "Eagle";
			break;
		case -1:
			// Birdie: One shot less
			MessageConstructor << "Birdie";
			break;
		case 0:
			// Par: equal to par
			MessageConstructor << "Par";
			break;
		case 1:
			// Bogey: One shot more
			MessageConstructor << "Bogey";
			break;
		case 2:
			// Double bogey: Two shots more
			MessageConstructor << "Double Bogey";
			break;
		case 3:
			// Triple bogey: Three shots more
			MessageConstructor << "Triple Bogey";
			break;
		case 4:
			// Quadruple Bogey: four strokes over par
			MessageConstructor << "Quadruple Bogey";
			break;
		default:
			MessageConstructor << score;
			break;
		}
		string outputMessage = MessageConstructor.str();
		int index = 0;
		glColor3f( 0.75f, 0.75f, 1.0f );
		while( outputMessage[index++] != '\0' )
			glutStrokeCharacter( GLUT_STROKE_ROMAN, outputMessage[index -1]);
		glPopMatrix();

		glPushMatrix();
		glLoadIdentity();
		glTranslatef( 30.0f, 83.0f, 0.0f );
		glScalef( 0.04f, 0.04f, 0.04f );
		MessageConstructor.str("");
		MessageConstructor << "Total Score: ";
		MessageConstructor << mTotalScore;
		string TotalScore = MessageConstructor.str();
		index = 0;
		glColor3f( 0.75f, 0.75f, 1.0f );
		while( TotalScore[index++] != '\0' )
			glutStrokeCharacter( GLUT_STROKE_ROMAN, TotalScore[index -1]);
		glPopMatrix();

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glEnable( GL_LIGHTING );
}