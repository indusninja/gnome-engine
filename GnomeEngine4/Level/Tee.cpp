#include "..\Misc\stdafx.h"

ostream& operator<<(ostream& output, const Tee& t)
{
	output << "Tee " << t.teeID << " on Tile " << t.tileID
		   << " and at Vertex: " << t.vertex << endl;
	output << "Tee Normal: " << t.normal << endl;
	return output;
}
