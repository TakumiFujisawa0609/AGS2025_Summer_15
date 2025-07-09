#include "Pbullet.h"

#include<string>

#include"../../../../../Manager/Camera.h"
#include"../../../../../Utility/AsoUtility.h"

Pbullet::Pbullet() {
}

Pbullet::~Pbullet() {
}

void Pbullet::Init(const Vector2F* pos) 
{
	AttackBase::Init(pos);

	obj_.resize(NUM);
	move_.resize(NUM);
	animeCou_.resize(NUM);
	animeInterval_.resize(NUM);
	hit_.resize(NUM);

	for (int i = 0; i < NUM; i++) {
		obj_[i].isAlive_ = false;
		obj_[i].pos_ = {};

		move_[i] = {};
		animeCou_[i] = 0;
		animeInterval_[i] = 0;
		hit_[i] = false;
	}

	end_ = false;

	for (int i = 0; i < PBULLET_ANIME_NUM; i++) {
		std::string path = "Data/Image/Boss/Bammoon/AttackEffect/Pbullet/Pbullet" + std::to_string(i + 1) + ".png";
		pBulletImg_[i] = LoadGraph(path.c_str());
		if (pBulletImg_[i] == -1) {
			return;
		}
	}
	for (int i = 0; i < HIT_ANIME_NUM; i++) {
		std::string path = "Data/Image/Boss/Bammoon/AttackEffect/Pbullet/Hit/hits" + std::to_string(i + 1) + ".png";
		hitImg_[i] = LoadGraph(path.c_str());
		if (hitImg_[i] == -1) {
			return;
		}
	}
}

void Pbullet::Update(void) 
{
	int i = -1;
	for (auto& p : obj_) {
		i++;
		if (!p.isAlive_) continue;

		p.pos_ += move_[i];

		p.disppos_ = p.pos_ - Camera::GetInstance().GetPos();

		if (++animeInterval_[i] > ANIME_INTERVAL) {
			animeInterval_[i] = 0;
			if (++animeCou_[i] > PBULLET_ANIME_NUM)animeCou_[i] = 0;
		}
	}
	if(num_>=NUM) end_ = true;
}

void Pbullet::Draw(void) 
{
	int i = -1;
	for (auto& p : obj_) {
		i++;
		if (!p.isAlive_)continue;

		DrawRotaGraph(p.disppos_.x, p.disppos_.y, 2, atan2(move_[i].y, move_[i].x), pBulletImg_[animeCou_[i]], true);
	}
}

void Pbullet::Release(void) 
{
	for (int i = 0; i < HIT_ANIME_NUM; i++) {
		DeleteGraph(hitImg_[i]);
	}
	for (int i = 0; i < PBULLET_ANIME_NUM; i++) {
		DeleteGraph(pBulletImg_[i]);
	}
	obj_.clear();
}

void Pbullet::On(int i, Vector2F pPos)
{
	if (obj_.size() <= i)return;

	if (i == 0) { end_ = false; num_ = 0; }
	num_++;

	obj_[i].pos_ = *boss;

	Vector2F v = pPos - obj_[i].pos_;
	float dis = sqrtf(v.x * v.x + v.y * v.y);
	v /= dis;

	float rad = RAD * (i - NUM / 2);

	v.x += sinf(rad);
	v.y += cosf(rad);

	move_[i] = v * SPEED;

	obj_[i].isAlive_ = true;
}

void Pbullet::Hit(int i)
{
	if (obj_.size() <= i)return;

	hit_[i] = true;
}