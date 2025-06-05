#include<DxLib.h>
#include "ArialSweep.h"
#include"../../../Manager/InputManager.h"
#include"../../../Utility/AsoUtility.h"

ArialSweep::ArialSweep()
{
}

ArialSweep::~ArialSweep()
{
}

void ArialSweep::Init(Vector2F* movePos, Vector2F* drawPos)
{
	PlayerAttackBase::Init(movePos, drawPos);
	unit_.isAlive_ = true;
	mPos_ = { 0,0 };
	worldMousePos_ = { 0,0 };

}

void ArialSweep::Update(Vector2* mousePos)
{
	mPos_ = *mousePos;
	//•`‰æŽž‚Ì‚¸‚ê‚ð•â³
	worldMousePos_.x = mPos_.x + ((Application::MAIN_SCREEN_SIZE_X - Application::SCREEN_SIZE_X) / 2);
	worldMousePos_.y = mPos_.y + ((Application::MAIN_SCREEN_SIZE_Y - Application::SCREEN_SIZE_Y) / 2);
}


void ArialSweep::Draw(void)
{

	DrawCircle(worldMousePos_.x, worldMousePos_.y, 2, 0x0f0f0f, true);
	DrawLine(pDrawPos_->x, pDrawPos_->y, worldMousePos_.x, worldMousePos_.y, 0x000f12);
}

void ArialSweep::Release(void)
{
}
