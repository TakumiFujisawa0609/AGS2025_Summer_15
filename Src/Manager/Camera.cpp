#include"Camera.h"


#include"../Application.h"
#include"../Object/Stage/Tutorial/TutorialStage.h"

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

bool Camera::BossSet()
{
	return cameraPos.x == (TutorialStage::STAGE_CHIP_SIZE * mapNum_.x)-(Application::SCREEN_SIZE_X-((Application::SCREEN_SIZE_X-Application::SCREEN_SIZE_X)/2));
}




