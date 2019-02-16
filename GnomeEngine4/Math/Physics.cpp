#include "..\Misc\stdafx.h"

void BallToFloorCollision(Point3& ballPosition,
						  Vector3& ballVelocity,
						  Vector3& ballAcceleration,
						  Plane floorPlane,
						  float ballRadius,
						  float gravity)
{
	float yOffset = floorPlane.ComputePointPlaneHalfSpace(ballPosition);
	if (yOffset < ballRadius)
	{
		ballPosition.y =
		  floorPlane.ComputeSafeYonPlane(ballPosition.x, ballPosition.z) +
		  ballRadius;
		ballVelocity.y *= -0.5f;
		ballAcceleration.y = gravity;
		// To add an acceleration along slopes
		Vector3 slopeAcc(
		  -floorPlane.normal.x, floorPlane.normal.y, -floorPlane.normal.z);
		slopeAcc.ScalarMultiply(gravity);
		ballAcceleration += slopeAcc;
	}
}

int BallToWallCollision(Point3& ballPosition,
						Vector3& ballVelocity,
						Vector3& ballAcceleration,
						Plane wallPlane,
						float ballRadius,
						int neighbour)
{
	float ds = wallPlane.ComputePointPlaneHalfSpace(ballPosition);
	if (ds < ballRadius)
		if (neighbour == 0)
		{
			ballAcceleration.getReflectionVector(wallPlane.normal);
			ballVelocity.getReflectionVector(wallPlane.normal);
		}
		else
			return neighbour;
	return -1;
}

bool BallToHoleCollision(Point3& holePosition,
						 Point3& ballPosition,
						 Vector3& ballVelocity,
						 Vector3& ballAcceleration,
						 float ballRadius,
						 float cupRadius)
{
	float xDif = ballPosition.x - holePosition.x;
	float yDif = ballPosition.y - holePosition.y;
	float zDif = ballPosition.z - holePosition.z;
	float ballToCup_dist = (xDif * xDif) + (yDif * yDif) + (zDif * zDif);
	float radiusSumSquared =
	  (ballRadius + cupRadius) * (ballRadius + cupRadius);
	if (ballToCup_dist < radiusSumSquared)
		return true;
	else
		return false;
}

bool BallToBallCollision(Point3& ballPosition1,
						 Point3& ballPosition2,
						 float ballRadius)
{
	// float
	return false;
}
