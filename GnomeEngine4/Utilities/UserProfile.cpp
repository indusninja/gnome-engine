#include "..\Misc\stdafx.h"
using namespace std;

void UserProfileUtil::initFromFile(void)
{
	ifstream infile;
	infile.open("Data\\users.usr");
	if (!infile)
	{
		cout << "User Data file not found!" << endl;
		return;
	}

	string s;
	while (infile >> s)
	{
		if (caseInsensitiveCompare(s, "user"))
		{
			UserProfile usr;
			infile >> usr.mUserName;
			infile >> usr.mPlayingCourseIndex;
			infile >> usr.mPlayingHoleIndex;

			mUsers[mUsers.size()] = usr;
		}
	}
	currentUser = -1;
}

void UserProfileUtil::AddUser(UserProfile usr)
{
	mUsers[mUsers.size()] = usr;
}

void UserProfileUtil::saveToFiles(void)
{
	ofstream outfile;
	outfile.open("Data\\users.usr");
	for (int i = 0; i < (int)mUsers.size(); i++)
	{
		outfile << "user" << endl;
		outfile << mUsers[i].mUserName << endl;
		outfile << mUsers[i].mPlayingCourseIndex << endl;
		outfile << mUsers[i].mPlayingHoleIndex << endl;
		outfile << mUsers[i].mScore << endl;
	}
}
