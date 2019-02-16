#include "..\Game\stdafx.h"
using namespace std;

void LevelManager::readLevelsFromFile(const char* filename)
{
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
					infile >> tee.teeID;
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
					infile >> cup.cupID;
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
	vector<Ball*> empty;
	this->balls = empty;
	for (map<int, Tee>::const_iterator i = levels[currentLevel].tees.begin();
		 i != levels[currentLevel].tees.end();
		 ++i)
	{
		Ball* b = new Ball();
		b->init(i->second.tileID, i->second.vertex, i->second.normal);
		this->balls.push_back(b);
	}

	inputManager.theta_aroundYaxis = 0;
	inputManager.camera.UpdateCamera(
	  balls[15]->newPosition, inputManager.getDirection(1), CAMERA_DISTANCE);
	inputManager.menu.SetHolePar(levels[currentLevel].Par);
}

void LevelManager::drawCurrentLevel(void)
{
	setupLookAt(inputManager.camera);
	UINT id = 0;
	string texture = "felt_1.tga";
	getTexture(id, texture);
	levels[currentLevel].drawLevel(id);

	bool stationary = true;
	for (int i = 0; i < (int)balls.size(); i++)
	{
		balls[i]->draw(1.0f, 1.0f, 1.0f, "Ball_1_Yellow.tga");
		if (!balls[i]->newPosition.isEqual(balls[i]->oldPosition))
			stationary = false;
	}

	if (stationary)
	{
		drawArrow(
		  balls[15]->newPosition, 0.0f, inputManager.theta_aroundYaxis, 0.0f);
		inputManager.menu.Draw(true, playCurrentHoleOnly);
	}
	else
		inputManager.menu.Draw(false, playCurrentHoleOnly);
}

void LevelManager::updateCurrentLevel(float deltaTime)
{
	if (!inputManager.menu.isActive)
	{
		for (int i = 0; i < (int)balls.size(); i++)
		{
			balls[i]->move(deltaTime);
			balls[i]->applyFriction();
		}
		resolveCollisions(deltaTime);
		inputManager.camera.UpdateCamera(balls[15]->newPosition,
										 inputManager.getDirection(1),
										 CAMERA_DISTANCE);
	}
	inputManager.menu.updatePower();
}

void LevelManager::resolveCollisions(float t)
{
	Plane floorPlane, wallPlane;
	for (int i = 0; i < (int)balls.size(); i++)
	{
		for (int j = 0;
			 j <
			 levels[currentLevel].tileSet[balls[i]->onTileID].numberOfVertices;
			 j++)
		{
			wallPlane.init(
			  levels[currentLevel].tileSet[balls[i]->onTileID].vertices[j],
			  levels[currentLevel].tileSet[balls[i]->onTileID].edgeNormals[j]);
			int newTile = BallToWallCollision(
			  balls[i]->newPosition,
			  balls[i]->velocity,
			  balls[i]->acceleration,
			  wallPlane,
			  BALL_RADIUS,
			  levels[currentLevel].tileSet[balls[i]->onTileID].neighbours[j]);
			if (newTile != -1)
				balls[i]->onTileID = newTile;
		}
		floorPlane.init(
		  levels[currentLevel].tileSet[balls[i]->onTileID].vertices[0],
		  levels[currentLevel].tileSet[balls[i]->onTileID].normal);
		BallToFloorCollision(balls[i]->newPosition,
							 balls[i]->velocity,
							 balls[i]->acceleration,
							 floorPlane,
							 BALL_RADIUS,
							 GRAVITY);

		balls[i]->velocity.x += (balls[i]->acceleration.x * t);
		balls[i]->velocity.y += (balls[i]->acceleration.y * t);
		balls[i]->velocity.z += (balls[i]->acceleration.z * t);
	}

	/*float ballToCup_dist = sqrt( pow(levels[currentLevel].cups[0].vertex.x -
	ball->newPosition.x, 2) + pow(levels[currentLevel].cups[0].vertex.z -
	ball->newPosition.z, 2) ); if( (ballToCup_dist < CUP_RADIUS) &&
		(ball->newPosition.y <= levels[currentLevel].cups[0].vertex.y +
	BALL_RADIUS) && (ball->velocity.Length()<0.9f) )
	{
		if(!playCurrentHoleOnly)
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
	}*/
	// if(BallToHoleCollision(levels[currentLevel].tileSet[balls[i]->onTileID],
	// Point3 &ballPosition, Vector3 &ballVelocity, Vector3 &ballAcceleration,
	// BALL_RADIUS, CUP_RADIUS))
}

void LevelManager::setBallAcceleration(bool testVerticalMotion)
{
	Vector3 Test(0, 1, 0);
	int power = inputManager.menu.getPower();
	Test.ScalarMultiply((float)power * powerMultiplier);
	if (testVerticalMotion)
		balls[15]->setAcceleration(Test);
	else if (balls[15]->newPosition.isEqual(balls[15]->oldPosition))
		balls[15]->setAcceleration(
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
