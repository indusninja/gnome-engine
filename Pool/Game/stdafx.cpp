// stdafx.cpp : source file that includes just the standard includes
// GnomeEngine.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "..\Game\stdafx.h"
using namespace std;

vector<UINT> TextureArray;
vector<string> TextureNames;

bool getTexture(UINT &ID, int index)
{
	if(index<(int)TextureArray.size())
	{
		ID = TextureArray[index];
		return true;
	}
	else
		return false;
}

bool getTexture(UINT &ID, string name)
{
	for(int i=0; i<(int)TextureNames.size(); i++)
	{
		string::size_type loc = TextureNames[i].find( name, 0 );
		if( loc != string::npos )
		{
			ID = TextureArray[i];
			return true;
		}
	}
	return false;
}

void initAssets(vector<string> assetNames)
{
	for(UINT i=0; i<(int)assetNames.size(); i++)
	{
		UINT temp = 0;
		size_t len = assetNames[i].length();
		LPSTR str2 = new char[len+1];
		assetNames[i]._Copy_s(str2,len,len);
		str2[len] = '\0';
		if(Load_Texture(temp, str2))
		{
			TextureArray.push_back(temp);
			TextureNames.push_back(assetNames[i]);
		}

		free(str2);
	}
}

void drawFlag(const char* assetName, Point3 vertex, Vector3 Rotate, Vector3 Scale)
{
	ModelLoader ml(vertex, Rotate, Scale);
	ml.Load3dsObject(assetName);
#ifdef _DEBUG
	ml.Print();
#endif
	ml.Draw();
}