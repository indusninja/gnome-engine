#include "..\Misc\stdafx.h"

// Draw a Circle with radius = CUP_RADIUS in the x-z plane
void Cup::draw(int triangleCount)
{
	float materialColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float specularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

	glBegin(GL_POLYGON);
	for (int i = 0; i < triangleCount; i++)
	{
		float theta = PI2 * float(i) / float(triangleCount);

		float deltax = CUP_RADIUS * cosf(theta);
		float deltaz = CUP_RADIUS * sinf(theta);

		glVertex3f(
		  vertex.x + deltax, vertex.y + (0.01f * normal.y), vertex.z + deltaz);
	}
	glEnd();
}

ostream& operator<<(ostream& output, const Cup& c)
{
	output << "Cup " << c.cupID << " on Tile " << c.tileID
		   << " and at Vertex: " << c.vertex << endl;
	output << "Cup Normal: " << c.normal << endl;
	return output;
}
