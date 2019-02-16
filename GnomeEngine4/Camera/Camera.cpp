#include "..\Misc\stdafx.h"

Camera::Camera(void)
{
	cameraTarget.init(0, 0, -1);
	cameraPosition.init(0, 0, 0);
	cameraUp.init(0, 1, 0);
}

void Camera::UpdateCamera(Point3 objectPosition,
						  Vector3 dir,
						  float CameraDistance)
{
	dir.Normalize();
	cameraPosition.x = objectPosition.x - dir.x;
	cameraPosition.y = objectPosition.y + CameraDistance;
	cameraPosition.z = objectPosition.z - dir.z;

	cameraTarget.x = objectPosition.x;
	cameraTarget.y = objectPosition.y;
	cameraTarget.z = objectPosition.z;
}

ostream& operator<<(ostream& output, const Camera& cam)
{
	cout << "CAMERA - Pos: " << cam.cameraPosition
		 << ", View: " << cam.cameraTarget << ", Up: " << cam.cameraUp << endl;
	return output;
}
