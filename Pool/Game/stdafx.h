// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#define PI ((float)3.141592654f)
#define PI2 ((float)6.283185308f)
#define EPSILON2 (float)(1E-2)
#define EPSILON3 (float)(1E-3)
#define EPSILON4 (float)(1E-4)
#define EPSILON5 (float)(1E-5)
#define EPSILON6 (float)(1E-6)
#define DEGREES_TO_RADIANS(ang) ((ang)*PI / 180.0)
#define RADIANS_TO_DEGREES(rads) ((rads)*180.0 / PI)
#define YROTATE_CEIL ((float)40.0f)
#define BALL_RADIUS ((float)0.042f)
#define CUP_RADIUS ((float)0.08f)
#define GRAVITY ((float)-5.0f)
#define FRICTION ((float)1.1f)
#define ACCURACY ((int)3)
#define CAMERA_DISTANCE ((float)0.65f)

// const float cameraDistance = 0.5f;
const float arrowMoveStep = 3.0f;
const float powerMultiplier = 5.0f;

const float fps = 60.0f;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cctype>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <windows.h>
#include "glut.h"

#include "Texture.h"
#include "Utility.h"
#include "Point3.h"
#include "Vector3.h"
#include "Plane.h"
#include "Physics.h"
#include "ModelLoader.h"
#include "Timer.h"
#include "Tile.h"
#include "Cup.h"
#include "Tee.h"
#include "..\Game\Ball.h"
#include "Camera.h"
#include "OpenGLUtility.h"
#include "Button.h"
#include "Menu.h"
#include "..\Game\MenuManager.h"
#include "UserProfile.h"
#include "Level.h"
#include "..\Game\InputManager.h"
#include "..\Game\LevelManager.h"

void initAssets(std::vector<std::string> assetNames);
bool getTexture(UINT& ID, int index);
bool getTexture(UINT& ID, std::string name);
void drawFlag(const char* assetName,
			  Point3 vertex,
			  Vector3 Rotate,
			  Vector3 Scale);
