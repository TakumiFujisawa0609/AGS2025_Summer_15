#include"Camera.h"


Camera* Camera::instance = nullptr;

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	cameraPos = VGet(0.0f, 150.0f, -300.0f);
}

void Camera::Set()
{
	SetCameraPositionAndAngle(cameraPos, 0.0f, 0.0f, 0.0f);
}

void Camera::Follow(dir xyz, float move)
{
	switch (xyz)
	{
	case Camera::X:
		cameraPos.x += move;
		break;
	case Camera::Y:
		cameraPos.y += move;
		break;
	case Camera::Z:
		cameraPos.z += move;
		break;
	default:
		break;
	}
}




