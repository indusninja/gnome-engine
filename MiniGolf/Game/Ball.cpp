#include "..\Game\stdafx.h"

// Initialize the Ball at a given vertex, as per a Ball radius, along a
// specified normal
void Ball::init(Point3 vertex, Vector3 normal)
{
	memset(this, 0, sizeof(Ball));
	velocity.Zero();
	acceleration.Zero();
	newPosition.init(vertex.x + (BALL_RADIUS*normal.x),
		vertex.y + (BALL_RADIUS*normal.y), 
		vertex.z + (BALL_RADIUS*normal.z));
	oldPosition = newPosition;
}

// To set the acceleration of the ball to a specific vector
void Ball::setAcceleration(Vector3 vec)
{
	acceleration.init(vec.x, vec.y, vec.z);
}

// To move the ball for a time-slice 't'
// NOTE:	The ball sometimes gets stuck due to higher ticks returned by the 
//			clock when using a timer for render loop
void Ball::move(float t)
{
	acceleration.y += (GRAVITY);
	oldPosition.init(newPosition);
	newPosition.x += displacement(velocity.x, acceleration.x, t);
	newPosition.z += displacement(velocity.z, acceleration.z, t);
	newPosition.y += displacement(velocity.y, acceleration.y, t);
}

// To apply frictional forces to the movement of the ball
void Ball::applyFriction(void)
{
	velocity /= FRICTION;
	acceleration /= FRICTION;
}

// To draw the ball at its current position
void Ball::draw(float colorR, float colorG, float colorB)
{
	glPushMatrix();
	glTranslatef(newPosition.x, newPosition.y, newPosition.z);

	float materialColor[] = { colorR, colorG, colorB, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
	float specularColor[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

	UINT id = 0; 
	string texture = "golfball.tga";
	if(getTexture(id, texture))
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, id);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

		glutSolidSphere(BALL_RADIUS, 50, 50);

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_2D);
	}
	else
		glutSolidSphere(BALL_RADIUS, 50, 50);
	glPopMatrix();
}