// ModelLoader.h : Data Structure to hold a 3D Model and method to load a 3DS Max model.

// --------------------------------------------------------------------------------
// WARNING: WORK IN PROGRESS! 3DS LOADER NOT WORKING FOR ALL FEATURES OF THE MODEL.
// ================================================================================

// Thanks for code sample and 3DS Max format details from Damiano Vitulli at 
// http://www.spacesimulator.net/tut4_3dsloader.html

#ifndef __ModelLoader_h
#define __ModelLoader_h

struct TexMapCoord
{
	float u;
	float v;
};

struct Poly
{
	unsigned short Index1;
	unsigned short Index2;
	unsigned short Index3;
};

class ModelLoader
{
	char name[20];
	int numVerts, numPolys;
	vector<Point3> vertices;
	vector<Poly> polygons;
	vector<TexMapCoord> mapcoords;
	Point3 position;
	Vector3 rotation;
	Vector3 scale;

public:
	ModelLoader(void);
	ModelLoader(Point3 pos, Vector3 rot, Vector3 sca);
	void Load3dsObject(const char *filename);
	void Draw(void);
	void Print(void);
};

#endif