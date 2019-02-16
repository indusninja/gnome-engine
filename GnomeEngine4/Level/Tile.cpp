#include "..\Misc\stdafx.h"
using namespace std;

void Tile::draw(float colorR, float colorG, float colorB, UINT textureID)
{
	// Render Tile Logic
	float materialColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
	float specularColor[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	float s[] = { 1.0, 0.0, 0.0, 0.0 };
	float t[] = { 0.0, 0.0, 1.0, 0.0 };
	glTexGenfv(GL_S, GL_OBJECT_PLANE, s);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, t);
	glBegin(GL_POLYGON);
	for (map<int, Point3>::iterator j = this->vertices.begin();
		 j != this->vertices.end();
		 j++)
		glVertex3f(j->second.x, j->second.y, j->second.z);
	glEnd();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	// Render Tile Border Logic
	glLineWidth(3.0f);
	materialColor[0] = materialColor[1] = materialColor[2] = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
	specularColor[0] = specularColor[1] = specularColor[2] = 0.8f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

	glBegin(GL_LINES);
	for (int i = 0; i < (int)this->neighbours.size(); i++)
	{
		if (this->neighbours[i] == 0)
		{
			glVertex3f(
			  this->vertices[i].x, this->vertices[i].y, this->vertices[i].z);
			glVertex3f(this->vertices[(i + 1) % this->numberOfVertices].x,
					   this->vertices[(i + 1) % this->numberOfVertices].y,
					   this->vertices[(i + 1) % this->numberOfVertices].z);
		}
	}
	glEnd();
	glLineWidth(1.0f);
}

void Tile::initCollisionDetectionEdges(void)
{
	for (int i = 0; i < this->numberOfVertices; i++)
	{
		edges[i].init(this->vertices[i],
					  this->vertices[(i + 1) % this->numberOfVertices]);
		edges[i].CrossProduct(this->normal, &edgeNormals[i]);
		edgeNormals[i].Reverse();
		edgeNormals[i].Normalize();
	}
}

ostream& operator<<(ostream& output, const Tile& t)
{
	output << "Tile Type: " << t.tileType << endl;
	output << "Tile ID: " << t.tileID << endl;
	output << "Number of Vertices in Tile: " << t.numberOfVertices << endl;

	for (map<int, Point3>::const_iterator j = t.vertices.begin();
		 j != t.vertices.end();
		 j++)
		output << "Vertex " << (j->first) << ": " << (j->second) << endl;

	output << "Normal: " << t.normal << endl;

	stringstream ss;
	ss << "Neighbours - ";
	for (map<int, int>::const_iterator j = t.neighbours.begin();
		 j != t.neighbours.end();
		 j++)
	{
		ss << "{Edge ";
		ss << (j->first) + 1;
		ss << ":";
		if (j->second == 0)
			ss << "BORDER";
		else
			ss << j->second;
		ss << "} ";
	}
	output << ss.str() << endl;
	return output;
}
