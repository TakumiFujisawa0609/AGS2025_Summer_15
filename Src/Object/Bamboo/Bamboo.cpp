#include"Bamboo.h"

Bamboo::Bamboo()
{
}

Bamboo::~Bamboo()
{
}

void Bamboo::Init(void)
{
}

void Bamboo::Set(Vector2F pos, Vector2F* pPos, int image)
{
	unit_.nextpos_ = pos;
	unit_.pos_ = unit_.nextpos_;
	ChangeDispPos();

	unit_.yAccel_ = -20.0f;
	unit_.xAccel_ = (float)(GetRand(40) - 20);

	unit_.isAlive_ = true;

	scale_ = (float)(GetRand(2) + 1);
	unit_.radius_ = (DEFAULT_SIZE * scale_) / 2;
	unit_.size_ = { unit_.radius_ * 2.0f,unit_.radius_ * 2.0f };

	this->pPos_ = pPos;

	unit_.isGravity_ = true;

	this->image_ = image;
}

void Bamboo::Set(Vector2F pos)
{
	unit_.nextpos_ = pos;
	unit_.pos_ = unit_.nextpos_;
	ChangeDispPos();

	unit_.yAccel_ = -20.0f;
	unit_.xAccel_ = (float)(GetRand(40) - 20);

	unit_.isAlive_ = true;

	scale_ = (float)(GetRand(2) + 1);
	unit_.radius_ = (DEFAULT_SIZE * scale_) / 2;
	unit_.size_ = { unit_.radius_ * 2.0f,unit_.radius_ * 2.0f };

	unit_.isGravity_ = true;
}

void Bamboo::Update(void)
{
	if (!unit_.isAlive_)return;

	Vector2F vec = { pPos_->x - unit_.nextpos_.x,pPos_->y - unit_.nextpos_.y };

	float dis = sqrtf(vec.x * vec.x + vec.y * vec.y);

	if (dis < ABS_DIS) {
		vec = { (vec.x / dis) * SPEED,(vec.y / dis) * SPEED };
		
		unit_.nextpos_.x += vec.x;
		unit_.nextpos_.y += vec.y;
	}

	UnitBase::Update();
}

void Bamboo::Draw(void)
{
	if (!unit_.isAlive_)return;

	//DrawCircleAA(unit_.disppos_.x, unit_.disppos_.y, unit_.radius_, 30, RGB(0, 255, 0));
	DrawRotaGraph(unit_.disppos_.x, unit_.disppos_.y, scale_, 0, image_, true);
}

void Bamboo::Release(void)
{
}
