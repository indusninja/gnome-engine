#include "..\Game\stdafx.h"
using namespace std;

void LevelManager::readLevelsFromFile(const char* filename)
{
	ball = new Ball();
	ifstream infile;
	infile.open(filename);
	if (!infile)
	{
		cout << "Unable to open '" << filename
			 << "'. Please check file and re-run command." << endl;
		exit(1);
	}

	Level lvl;
	currentLevel = 0;
	playCurrentHoleOnly = false;
	string s;
	while (infile >> s)
	{
		if (caseInsensitiveCompare(s, "course"))
		{
			string name;
			infile >> name;
			string::iterator it = name.end();
			it--;
			while (*it != '\"')
			{
				infile >> s;
				name += " " + s;
				it = name.end();
				it--;
			}
			courseName = name;
			infile >> numberOfHoles;
		}
		else if (caseInsensitiveCompare(s, "begin_hole"))
		{
			Level lvl;
			while ((infile >> s) && (!caseInsensitiveCompare(s, "end_hole")))
			{
				int i;
				float a, b, c;
				Point3 point;
				if (caseInsensitiveCompare(s, "name"))
				{
					string name;
					infile >> name;
					string::iterator it = name.end();
					it--;
					while (*it != '\"')
					{
						infile >> s;
						name += " " + s;
						it = name.end();
						it--;
					}
					lvl.levelName = name;
				}
				else if (caseInsensitiveCompare(s, "tile"))
				{
					Tile tile;
					tile.tileType = "tile";
					infile >> tile.tileID;
					infile >> tile.numberOfVertices;
					for (int j = 0; j < tile.numberOfVertices; j++)
					{
						infile >> a;
						infile >> b;
						infile >> c;
						point.init(a, b, c);
						tile.vertices[j] = point;
					}
					for (int j = 0; j < tile.numberOfVertices; j++)
					{
						infile >> i;
						tile.neighbours[j] = i;
					}
					tile.normal.getFaceNormal(
					  tile.vertices[0], tile.vertices[1], tile.vertices[2]);
					tile.initCollisionDetectionEdges();
					lvl.tileSet[tile.tileID] = tile;
				}
				else if (caseInsensitiveCompare(s, "tee"))
				{
					Tee tee;
					tee.teeID = 0;
					infile >> tee.tileID;
					infile >> a;
					infile >> b;
					infile >> c;
					tee.vertex.init(a, b, c);
					tee.normal.init(lvl.tileSet[tee.tileID].normal);
					lvl.tees[tee.teeID] = tee;
				}
				else if (caseInsensitiveCompare(s, "cup"))
				{
					Cup cup;
					cup.cupID = 0;
					infile >> cup.tileID;
					infile >> a;
					infile >> b;
					infile >> c;
					cup.vertex.init(a, b, c);
					cup.normal.init(lvl.tileSet[cup.tileID].normal);
					lvl.cups[cup.cupID] = cup;
				}
				else if (caseInsensitiveCompare(s, "par"))
					infile >> lvl.Par;
			}
			levels.push_back(lvl);
		}
	}
	infile.close();
	resetToLevel(currentLevel);
	vector<string> holeNames;
	for (int i = 0; i < (int)levels.size(); i++)
		holeNames.push_back(levels[i].levelName);
	inputManager.menu.init(courseName, holeNames);

#ifdef _DEBUG
	ofstream outfile;
	outfile.open("Logs/debug_log.txt");
	outfile << *this;
#endif
}

void LevelManager::resetToLevel(int index)
{
	currentLevel = index;
	if (currentLevel >= numberOfHoles)
		currentLevel = 0;
	ballOnTileID = levels[currentLevel].tees[0].tileID;
	ball->init(levels[currentLevel].tees[0].vertex,
			   levels[currentLevel].tees[0].normal);
	inputManager.theta_aroundYaxis = 0;
	inputManager.camera.UpdateCamera(
	  ball->newPosition, inputManager.getDirection(1), CAMERA_DISTANCE);
	inputManager.menu.SetHolePar(levels[currentLevel].Par);
}

void LevelManager::drawCurrentLevel(void)
{
	setupLookAt(inputManager.camera);
	UINT id = 0;
	string texture = "ground_grass_512_tile.tga";
	getTexture(id, texture);
	levels[currentLevel].drawLevel(id);

	ball->draw(1.0f, 1.0f, 1.0f);
	Vector3 Rot(0, 0, 0), Sca(0.005f, -0.005f, 0.005f);
	drawFlag("Assets/flag.3ds", levels[currentLevel].cups[0].vertex, Rot, Sca);
	if (ball->newPosition.isEqual(ball->oldPosition))
	{
		drawArrow(
		  ball->newPosition, 0.0f, inputManager.theta_aroundYaxis, 0.0f);
		inputManager.menu.Draw(true, playCurrentHoleOnly);
	}
	else
		inputManager.menu.Draw(false, playCurrentHoleOnly);
}

void LevelManager::updateCurrentLevel(float deltaTime)
{
	if (!inputManager.menu.isActive)
	{
		ball->move(deltaTime);
		resolveCollisions(deltaTime);
		inputManager.camera.UpdateCamera(
		  ball->newPosition, inputManager.getDirection(1), CAMERA_DISTANCE);
		ball->applyFriction();
	}
	inputManager.menu.updatePower();

#ifdef _DEBUG
	/*cout << "UPDATE CALL - " << deltaTime << " ms"<<endl;
	cout << "S(x,y,z): " << ball->newPosition << endl;
	cout << "V(x,y,z): " << ball->velocity << endl;
	cout << "A(x,y,z): " << ball->acceleration << endl;*/
#endif
}

void LevelManager::resolveCollisions(float t)
{
	Plane tilePlane;
	for (int i = 0;
		 i < levels[currentLevel].tileSet[ballOnTileID].numberOfVertices;
		 i++)
	{
		tilePlane.init(
		  levels[currentLevel].tileSet[ballOnTileID].vertices[i],
		  levels[currentLevel].tileSet[ballOnTileID].edgeNormals[i]);
		float ds = tilePlane.ComputePointPlaneHalfSpace(ball->newPosition);
		if (ds < BALL_RADIUS)
		{
			if (levels[currentLevel].tileSet[ballOnTileID].neighbours[i] == 0)
			{
				ball->acceleration.getReflectionVector(
				  levels[currentLevel].tileSet[ballOnTileID].edgeNormals[i]);
				ball->velocity.getReflectionVector(
				  levels[currentLevel].tileSet[ballOnTileID].edgeNormals[i]);
			}
			else
			{
				int ID =
				  levels[currentLevel].tileSet[ballOnTileID].neighbours[i];
				ballOnTileID = ID;
			}
		}
	}

	tilePlane.init(levels[currentLevel].tileSet[ballOnTileID].vertices[0],
				   levels[currentLevel].tileSet[ballOnTileID].normal);
	float yOffset = tilePlane.ComputePointPlaneHalfSpace(ball->newPosition);
	if (yOffset < BALL_RADIUS)
	{
		ball->newPosition.y = tilePlane.ComputeSafeYonPlane(
								ball->newPosition.x, ball->newPosition.z) +
							  BALL_RADIUS;
		ball->velocity.y *= -0.5f;
		ball->acceleration.y = GRAVITY;
		// To add an acceleration along slopes
		Vector3 slopeAcc(-levels[currentLevel].tileSet[ballOnTileID].normal.x,
						 levels[currentLevel].tileSet[ballOnTileID].normal.y,
						 -levels[currentLevel].tileSet[ballOnTileID].normal.z);
		slopeAcc.ScalarMultiply(GRAVITY);
		ball->acceleration += slopeAcc;
	}
	ball->velocity.x += (ball->acceleration.x * t);
	ball->velocity.y += (ball->acceleration.y * t);
	ball->velocity.z += (ball->acceleration.z * t);

	float ballToCup_dist =
	  sqrt(pow(levels[currentLevel].cups[0].vertex.x - ball->newPosition.x, 2) +
		   pow(levels[currentLevel].cups[0].vertex.z - ball->newPosition.z, 2));
	if ((ballToCup_dist < CUP_RADIUS) &&
		(ball->newPosition.y <=
		 levels[currentLevel].cups[0].vertex.y + BALL_RADIUS) &&
		(ball->velocity.Length() < 0.9f))
	{
		if (!playCurrentHoleOnly)
		{
			inputManager.menu.ResetHoleStrokes();
			currentLevel++;
		}
		else
		{
			inputManager.menu.setActiveMenu(0);
			inputManager.menu.ResetScores();
		}
		resetToLevel(currentLevel);
	}
}

void LevelManager::setBallAcceleration(bool testVerticalMotion)
{
	Vector3 Test(0, 1, 0);
	int power = inputManager.menu.getPower();
	Test.ScalarMultiply((float)power * powerMultiplier);
	if (testVerticalMotion)
		ball->setAcceleration(Test);
	else if (ball->newPosition.isEqual(ball->oldPosition))
		ball->setAcceleration(
		  inputManager.getDirection(power * powerMultiplier));
	inputManager.menu.incrementStroke();
}

ostream& operator<<(ostream& output, const LevelManager& lm)
{
	output << "Course: " << lm.courseName << endl;
	output << "Total Number of Levels in course: " << lm.numberOfHoles << endl;
	output
	  << "================================================================="
	  << endl;
	for (int i = 0; i < (int)lm.levels.size(); i++)
		output << lm.levels[i];
	return output;
}
