#include"Bullet.h"

#include<DxLib.h>

#include"../../../../Utility/ShapesPosition.h"
#include"../../../../Manager/Camera.h"


Bullet::Bullet()
{
	image_ = LoadGraph("Data/Image/Boss/Nokopy/happa.png");
}

Bullet::~Bullet()
{
}

void Bullet::Init(const Vector2F* pos)
{
	AttackBase::Init(pos);
	obj_.isAlive_ = true;
	obj_.radius_ = 15.0f;
	obj_.size_ = { 30.0f,30.0f };
	radius_ = 0.0f;
	stAngle_ = 0.0f;

	for (int i = 0; i < BULLET_NUM; i++) {
		bullets[i] = obj_;
	}
}

void Bullet::Update()
{
	if (radius_ < CHARGE_RADIUS) {
		radius_++;
		stAngle_ += 0.05f;
	}
	else {
		attackCounter_++;
		if (attackCounter_ > 120) {
			radius_ += 20.0f;
		}
		else {
			stAngle_+=0.1f;
		}
	}

	std::vector<Vector2F> pos = ShapesPosition::GetPositionCircle(boss->x, boss->y, radius_, stAngle_, BULLET_NUM);

	for (int i = 0; i < BULLET_NUM; i++) {
		bullets[i].pos_ = pos[i];

	}


	//’e‘S•”‚È‚­‚È‚é‚©A”¼Œa‚ªãŒÀ‚É’B‚µ‚Ä‚¢‚½‚çUŒ‚I—¹
	bool allAlive = true;
	for (int i = 0; i < BULLET_NUM; i++) {
		if (!bullets[i].isAlive_)continue;
		allAlive = false;
	}
	if (radius_ > RADIUS_MAX)allAlive = true;
	if (allAlive)end_ = true;

	AttackBase::Update();
}

void Bullet::Draw()
{
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullets[i].isAlive_) {
			//DrawCircleAA(bullets[i].disppos_.x, bullets[i].disppos_.y, bullets[i].radius_, 30, RGB(0, 0, 0));
			DrawRotaGraph(bullets[i].disppos_.x, bullets[i].disppos_.y, 1, 0, image_, true);
		}
	}
}

void Bullet::Release()
{


}

const std::vector<Base> Bullet::Get()const
{
	std::vector<Base>ret;

	for (int i = 0; i < BULLET_NUM; i++) {
		ret.emplace_back(bullets[i]);
	}

	return ret;
}


void Bullet::ChangeDispPos()
{
	auto& camera = Camera::GetInstance();
	for (int i = 0; i < BULLET_NUM; i++) {
		bullets[i].disppos_ = bullets[i].pos_ - camera.GetPos();
	}
}