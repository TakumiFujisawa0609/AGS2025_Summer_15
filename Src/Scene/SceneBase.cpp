#include "SceneBase.h"
#include"../Application.h"

SceneBase::SceneBase(void)
{
	zoomPos_ = { (float)Application::SCREEN_SIZE_X / 2,(float)Application::SCREEN_SIZE_Y / 2 };
	scale_ = 1.0f;
}

SceneBase::~SceneBase(void)
{
}

void SceneBase::Init(void)
{
}

void SceneBase::Update(void)
{
}

void SceneBase::Draw(void)
{
}

void SceneBase::Release(void)
{
}
