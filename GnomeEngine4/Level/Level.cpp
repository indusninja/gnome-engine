#include "..\Misc\stdafx.h"
using namespace std;

void Level::drawLevel(UINT textureID)
{
	for (map<int, Tile>::iterator i = this->tileSet.begin();
		 i != this->tileSet.end();
		 ++i)
		if (i->second.tileType == "tile")
			i->second.draw(0.0f, 0.7f, 0.0f, textureID);
		else
			i->second.draw(0.2f, 0.9f, 0.2f, textureID);

	for (map<int, Cup>::iterator i = this->cups.begin(); i != this->cups.end();
		 ++i)
		i->second.draw(64);
}

ostream& operator<<(ostream& output, const Level& l)
{
	output << "LEVEL: " << l.levelName << " has " << l.tileSet.size()
		   << " tiles, " << l.tees.size() << " tees, and " << l.cups.size()
		   << " cups. Par = " << l.Par << endl;
	output
	  << "-----------------------------------------------------------------"
	  << endl;
	for (map<int, Tile>::const_iterator i = l.tileSet.begin();
		 i != l.tileSet.end();
		 ++i)
	{
		output << (i->second);
		output
		  << "-----------------------------------------------------------------"
		  << endl;
	}
	for (map<int, Tee>::const_iterator i = l.tees.begin(); i != l.tees.end();
		 ++i)
	{
		output << (i->second);
		output
		  << "-----------------------------------------------------------------"
		  << endl;
	}
	for (map<int, Cup>::const_iterator i = l.cups.begin(); i != l.cups.end();
		 ++i)
	{
		output << (i->second);
		output
		  << "-----------------------------------------------------------------"
		  << endl;
	}
	output
	  << "================================================================="
	  << endl;
	return output;
}
