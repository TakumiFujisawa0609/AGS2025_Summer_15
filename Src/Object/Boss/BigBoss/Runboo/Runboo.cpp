#include "Runboo.h"
#include<DxLib.h>
#include "../../Tutorial/BossTutorial.h"
#include"Weakness.h"


Runboo::Runboo()
{
}

Runboo::~Runboo()
{
}

void Runboo::Init()
{
	for (int ii = 0; ii < WEAK_MAX; ii++)
	{
		weak_[ii] = new Weakness();
		weak_[ii]->Init({ 100, (float)(Application::SCREEN_SIZE_Y / 3 + ii * Application::SCREEN_SIZE_Y / 3) });
	}



	unit_.disppos_ = { 0.0f,0.0f };
	unit_.pos_ = { 0.0f,0.0f };

	unit_.hp_ = 100;
	unit_.isAlive_ = true;


}

void Runboo::Update()
{
	for (int ii = 0; ii < WEAK_MAX; ii++)weak_[ii]->Update();
}

void Runboo::Draw()
{
	DrawBox(
		unit_.disppos_.x,
		unit_.disppos_.y,
		unit_.disppos_.x + 200,
		unit_.disppos_.y + Application::SCREEN_SIZE_Y + 100,
		RGB(255, 255, 255), true
	);

	for (int ii = 0; ii < WEAK_MAX; ii++)weak_[ii]->Draw();
}

void Runboo::Release()
{
	for (int ii = 0; ii < WEAK_MAX; ii++)
	{
		weak_[ii]->Release();
		delete weak_[ii];
		weak_[ii] = nullptr;
	}
}

std::vector<Base*> Runboo::GetObj(void)
{
	return std::vector<Base*>();
}

void Runboo::Idle(void)
{
}

void Runboo::Move(void)
{
}

void Runboo::Attack(void)
{
}

void Runboo::Damage(void)
{
}

void Runboo::Death(void)
{
}



