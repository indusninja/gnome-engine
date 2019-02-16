#include "..\Misc\stdafx.h"
using namespace std;

ModelLoader::ModelLoader(void)
{
	position.Zero();
	rotation.Zero();
	scale.init(1, 1, 1);
}

ModelLoader::ModelLoader(Point3 pos, Vector3 rot, Vector3 sca)
{
	position = pos;
	rotation = rot;
	scale = sca;
}

void ModelLoader::Load3dsObject(const char* filename)
{
	// Temp vars to be given to the model
	numVerts = 0;
	numPolys = 0;
	FILE* file;	// Our file pointer
	char temp;	 // Temporary char for reading name of object
	short chunkID; // Stores ID of current chunk.
	long chunkLength;
	short useless;

	// Open our file for reading(r) and in binary mode(b)- "rb"
	file = fopen(filename, "rb");

	fseek(file, 0, SEEK_END);	// seek to end of file
	long filesize = ftell(file); // get the maximum file pointer
	fseek(file, 0, SEEK_SET);	// seek back to beginning of file

	// While current position is lesser than the total length
	while (ftell(file) < filesize)
	{
		fread(&chunkID, 2, 1, file);
		fread(&chunkLength, 4, 1, file);
		switch (chunkID)
		{
			case 0x4d4d: // Skip these chunks
				break;
			case 0x3d3d:
				break;
			case 0x4000: // Chunk containing name
				for (int i = 0; i < 20; i++)
				{
					fread(&temp, 1, 1, file);
					name[i] = temp;
					if (temp == '\0')
						break;
				}
				break;
			case 0x3f80: // Skip again
				break;
			case 0x4100:
				break;
			case 0x4110: // Chunk with num of vertices followed by their
						 // coordinates
				fread(&numVerts, sizeof(unsigned short), 1, file);
				{
					for (int i = 0; i < numVerts; i++)
					{
						Point3 v;
						fread(&v.x, sizeof(float), 1, file);
						fread(&v.y, sizeof(float), 1, file);
						fread(&v.z, sizeof(float), 1, file);
						vertices.push_back(v);
					}
				}
				break;
			case 0x4120: // Chunk with numPolys and the indices
				fread(&numPolys, sizeof(unsigned short), 1, file);
				{
					for (int i = 0; i < numPolys; i++)
					{
						Poly p;
						fread(&p.Index1, sizeof(unsigned short), 1, file);
						fread(&p.Index2, sizeof(unsigned short), 1, file);
						fread(&p.Index3, sizeof(unsigned short), 1, file);
						fread(&useless, sizeof(unsigned short), 1, file);
						polygons.push_back(p);
					}
				}
				break;
			case 0x4140: // Chunk with texture coords
				fread(&useless, sizeof(unsigned short), 1, file);
				{
					for (int i = 0; i < numVerts; i++)
					{
						TexMapCoord m;
						fread(&m.u, sizeof(float), 1, file);
						fread(&m.v, sizeof(float), 1, file);
						mapcoords.push_back(m);
					}
				}
				break;
			default:
				fseek(file, chunkLength - 6, SEEK_CUR);
		}
	}
	fclose(file);
}

// Method to draw a 3DS Max model
void ModelLoader::Draw(void)
{
	glPushMatrix();
	float materialColor[] = { 0.75f, 0.75f, 0.1f, 1.0f };
	float specularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);
	glTranslatef(position.x, position.y, position.z);
	glScalef(scale.x, scale.y, scale.z);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < (int)polygons.size(); i++)
	{
		glVertex3f(vertices[polygons[i].Index1].x,
				   vertices[polygons[i].Index1].y,
				   vertices[polygons[i].Index1].z);
		glVertex3f(vertices[polygons[i].Index2].x,
				   vertices[polygons[i].Index2].y,
				   vertices[polygons[i].Index2].z);
		glVertex3f(vertices[polygons[i].Index3].x,
				   vertices[polygons[i].Index3].y,
				   vertices[polygons[i].Index3].z);
	}
	glEnd();
	glPopMatrix();
}

// DEBUG method to print out details of the model loaded
void ModelLoader::Print(void)
{
	ofstream outfile;
	outfile.open("Logs/modelLoad_debug_log.txt");
	outfile << "Number of Vertices: " << vertices.size() << endl;
	outfile << "Number of Polygons: " << polygons.size() << endl;
	outfile << "Texture Coordinate Points: " << mapcoords.size() << endl;

	for (int i = 0; i < (int)polygons.size(); i++)
	{
		outfile << "P" << i + 1 << " : "
				<< "--------------------------------------" << endl;
		outfile << polygons[i].Index1 << " = " << vertices[polygons[i].Index1]
				<< endl;
		outfile << polygons[i].Index2 << " = " << vertices[polygons[i].Index2]
				<< endl;
		outfile << polygons[i].Index3 << " = " << vertices[polygons[i].Index3]
				<< endl;
	}
}
