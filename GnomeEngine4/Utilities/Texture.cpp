#include "..\Misc\stdafx.h"

bool Load_Texture(UINT& texture, LPSTR strFileName)
{
	if (!strFileName)
		return false;

	TargaImage* pImage = NULL;
	pImage = LoadTGA(strFileName);

	if (pImage == NULL)
		return false;

	glGenTextures(1, &texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glBindTexture(GL_TEXTURE_2D, texture);

	int textureType = GL_RGB;

	if (pImage->channels == 4)
		textureType = GL_RGBA;

	gluBuild2DMipmaps(GL_TEXTURE_2D,
					  pImage->channels,
					  pImage->sizeX,
					  pImage->sizeY,
					  textureType,
					  GL_UNSIGNED_BYTE,
					  pImage->data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	if (pImage)
	{
		if (pImage->data)
			free(pImage->data);
		free(pImage);
	}

	return true;
}

TargaImage* LoadTGA(const char* strFileName)
{
	TargaImage* pImageData = NULL;
	WORD width = 0, height = 0;
	byte length = 0;
	byte imageType = 0;
	byte bits = 0;
	FILE* pFile = NULL;
	int channels = 0;
	int stride = 0;
	int i = 0;

	if ((pFile = fopen(strFileName, "rb")) == NULL)
	{
		return NULL;
	}

	pImageData = (TargaImage*)malloc(sizeof(TargaImage));

	fread(&length, sizeof(byte), 1, pFile);

	fseek(pFile, 1, SEEK_CUR);

	fread(&imageType, sizeof(byte), 1, pFile);

	fseek(pFile, 9, SEEK_CUR);

	fread(&width, sizeof(WORD), 1, pFile);
	fread(&height, sizeof(WORD), 1, pFile);
	fread(&bits, sizeof(byte), 1, pFile);

	fseek(pFile, length + 1, SEEK_CUR);

	if (imageType != TGA_RLE)
	{
		if (bits == 24 || bits == 32)
		{
			channels = bits / 8;
			stride = channels * width;
			pImageData->data =
			  ((unsigned char*)malloc(sizeof(unsigned char) * stride * height));

			for (int y = 0; y < height; y++)
			{
				unsigned char* pLine = &(pImageData->data[stride * y]);

				fread(pLine, stride, 1, pFile);

				for (i = 0; i < stride; i += channels)
				{
					int temp = pLine[i];
					pLine[i] = pLine[i + 2];
					pLine[i + 2] = temp;
				}
			}
		}
		else if (bits == 16)
		{
			unsigned short pixels = 0;
			int r = 0, g = 0, b = 0;

			channels = 3;
			stride = channels * width;
			pImageData->data =
			  ((unsigned char*)malloc(sizeof(unsigned char) * stride * height));

			for (int i = 0; i < width * height; i++)
			{
				fread(&pixels, sizeof(unsigned short), 1, pFile);

				b = (pixels & 0x1f) << 3;
				g = ((pixels >> 5) & 0x1f) << 3;
				r = ((pixels >> 10) & 0x1f) << 3;

				pImageData->data[i * 3 + 0] = r;
				pImageData->data[i * 3 + 1] = g;
				pImageData->data[i * 3 + 2] = b;
			}
		}
		else
			return NULL;
	}
	else
	{
		byte rleID = 0;
		int colorsRead = 0;
		channels = bits / 8;
		stride = channels * width;

		pImageData->data =
		  ((unsigned char*)malloc(sizeof(unsigned char) * stride * height));
		byte* pColors = ((byte*)malloc(sizeof(byte) * channels));

		while (i < width * height)
		{
			fread(&rleID, sizeof(byte), 1, pFile);

			if (rleID < 128)
			{
				rleID++;

				while (rleID)
				{
					fread(pColors, sizeof(byte) * channels, 1, pFile);

					pImageData->data[colorsRead + 0] = pColors[2];
					pImageData->data[colorsRead + 1] = pColors[1];
					pImageData->data[colorsRead + 2] = pColors[0];

					if (bits == 32)
						pImageData->data[colorsRead + 3] = pColors[3];

					i++;
					rleID--;
					colorsRead += channels;
				}
			}
			else
			{
				rleID -= 127;

				fread(pColors, sizeof(byte) * channels, 1, pFile);

				while (rleID)
				{
					pImageData->data[colorsRead + 0] = pColors[2];
					pImageData->data[colorsRead + 1] = pColors[1];
					pImageData->data[colorsRead + 2] = pColors[0];

					if (bits == 32)
						pImageData->data[colorsRead + 3] = pColors[3];

					i++;
					rleID--;
					colorsRead += channels;
				}
			}
		}
	}

	fclose(pFile);

	pImageData->channels = channels;
	pImageData->sizeX = width;
	pImageData->sizeY = height;

	return pImageData;
}
