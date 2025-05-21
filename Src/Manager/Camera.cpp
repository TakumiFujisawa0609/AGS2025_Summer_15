#include<DxLib.h>
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
	prevPos = cameraPos;
	shakecounter_ = 0;
}

void Camera::Set()
{
	if (shakecounter_ > 1) {
		shakecounter_--;
		int shake = shakecounter_ / 5 % 2;
		shake *= 2;
		shake -= 1;
		shake *= 5;
		cameraPos.x += shake;
		cameraPos.y -= shake;
	}
	else if (shakecounter_ == 1) {
		shakecounter_ = 0;
		cameraPos = prevPos;
	}
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

void Camera::SHAKE(void)
{
	if (shakecounter_ > 0)return;
	shakecounter_ = SHAKE_COUNTER_SET;
	prevPos = cameraPos;
}




