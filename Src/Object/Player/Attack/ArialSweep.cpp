#include<DxLib.h>
#include "ArialSweep.h"

ArialSweep::ArialSweep()
{
}

ArialSweep::~ArialSweep()
{
}

void ArialSweep::Init(void)
{
}

void ArialSweep::Init(Vector2F* pos)
{
	PlayerAttackBase::Init(pos);
	unit_.isAlive_ = true;
	mPos_ = { 0,0 };
	worldMousePos_ = { 0,0 };
	

}

void ArialSweep::Update(void)
{
	GetMousePoint(&mPos_.x, &mPos_.y);
	//•`‰æŽž‚Ì‚¸‚ê‚ð•â³
	worldMousePos_.x = mPos_.x + ((Application::MAIN_SCREEN_SIZE_X - Application::SCREEN_SIZE_X) / 2);
	worldMousePos_.y = mPos_.y + ((Application::MAIN_SCREEN_SIZE_Y - Application::SCREEN_SIZE_Y) / 2);
	
	Vector2F vec=UnitBase::GetMoveVec(*playerPos_, worldMousePos_);


}

void ArialSweep::Draw(void)
{
	
	DrawCircle(worldMousePos_.x, worldMousePos_.y, 2, 0x0f0f0f, true);
	DrawLine(playerPos_->x, playerPos_->y, worldMousePos_.x, worldMousePos_.y, 0x000f12);
}

void ArialSweep::Release(void)
{
}
