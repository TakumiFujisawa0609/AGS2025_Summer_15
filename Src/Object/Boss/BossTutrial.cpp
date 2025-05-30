#include"BossTutrial.h"


BossTutrial::BossTutrial()
{
}

BossTutrial::~BossTutrial()
{
}

void BossTutrial::Init()
{
	unit_.isAlive_ = true;
	unit_.isDraw_ = true;
	unit_.pos_ = { 3000,250 };
	unit_.radius_ = 0;
	unit_.size_ = { 140, 240};
}

void BossTutrial::Update()
{
	StageCollisionUpdate();
	ChangeDispPos();
}

void BossTutrial::Draw()
{
	if (unit_.isDraw_)
	{
		DrawBox(unit_.disppos_.x - 70, unit_.disppos_.y - 120, unit_.disppos_.x + 70, unit_.disppos_.y + 120, 0xff0000, true);
	}
	DrawFormatString(120, 120, 0x0ff0ff, "boss(%.2f,%.2f)", unit_.pos_.x, unit_.pos_.y);
}

void BossTutrial::Release()
{

}

void BossTutrial::Move()
{

}