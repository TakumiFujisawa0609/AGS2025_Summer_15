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
	cameraPos = { 0.0f,0.0f };
}

void Camera::Set()
{
	//SetCameraPositionAndAngle(cameraPos, 0.0f, 0.0f, 0.0f);
}

void Camera::Follow(dir xy, float move)
{
	switch (xy)
	{
	case Camera::X:
		cameraPos.x += move;
		break;
	case Camera::Y:
		cameraPos.y += move;
		break;
	default:
		break;
	}
}




