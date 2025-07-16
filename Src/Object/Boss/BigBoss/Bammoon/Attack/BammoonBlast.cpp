#include"BammoonBlast.h"

#include<DxLib.h>
#include<cmath>

#include"../../../../../Manager/Camera.h"

BammoonBlast::BammoonBlast()
{

}

BammoonBlast::~BammoonBlast()
{
}

void BammoonBlast::Init(const Vector2F* pos)
{
	AttackBase::Init(pos);

	reticleImg_ = LoadGraph("Data/Image/Boss/Reticle.png");
	LoadDivGraph("Data/Image/Effect/BammoonBlast.png", BammoonBlast_NUM_MAX, BammoonBlast_NUM_X, BammoonBlast_NUM_Y, BammoonBlast_SIZE, BammoonBlast_SIZE, BammoonBlastImg_);
	img = LoadGraph("Data/Image/Boss/Bomb.png");

	BammoonBlastCount_ = 0;
	end_ = false;

	obj_.resize(MAX_NUM);
	for (auto& o : obj_) {
		o.isAlive_ = false;
	}
	bList.resize(MAX_NUM);
	for (auto& b : bList) {
		b.angle_ = 0.0f;
		b.expansion_ = 0.0f;
		b.target_ = {};
		b.vec_ = {};
		b.BammoonBlast_ = false;
		b.animeCounter_ = 0;
	}
}
void BammoonBlast::Update(void)
{
	int i = -1;
	for (auto& o : obj_) {
		i++;
		if (!o.isAlive_)continue;

		if (!bList[i].BammoonBlast_) {

			o.pos_ += bList[i].vec_;

			Vector2F v = bList[i].target_ - o.pos_;
			float dis = sqrtf(v.x * v.x + v.y * v.y);

			if (dis < 5.0f) {
				BammoonBlastCount_++;
				o.size_ *= 2.0f;
				bList[i].BammoonBlast_ = true;
			}

		}
		else {
			bList[i].animeCounter_++;
			if (bList[i].animeCounter_ > BammoonBlast_NUM_MAX) o.isAlive_ = false;
		}

		bList[i].angle_ += 0.1f;
		bList[i].expansion_ = std::sin(bList[i].angle_);
	}

	if (BammoonBlastCount_ >= MAX_NUM)end_ = true;
}
void BammoonBlast::Draw(void)
{
	auto& camera = Camera::GetInstance();

	int i = -1;
	for (auto& o : obj_) {
		i++;
		if (!o.isAlive_)continue;

		Vector2F disp = { bList[i].target_.x - camera.GetPos().x,bList[i].target_.y - camera.GetPos().y };
		DrawRotaGraph(disp.x, disp.y, bList[i].expansion_, bList[i].angle_, reticleImg_, true);

		DrawRotaGraph(o.pos_.x, o.pos_.y, (bList[i].BammoonBlast_) ? 0.5 : 1, 0,
			(bList[i].BammoonBlast_) ? BammoonBlastImg_[bList[i].animeCounter_] : img, true);
	}
}
void BammoonBlast::Release(void)
{
	for (int i = 0; i < BammoonBlast_NUM_MAX; i++) {
		DeleteGraph(BammoonBlastImg_[i]);
	}
	DeleteGraph(reticleImg_);
}


void BammoonBlast::On(int i, Vector2F pPos)
{
	if (obj_.size() - 1 < i)return;

	if (i == 0) { end_ = false; BammoonBlastCount_ = 0; }

	obj_[i].pos_ = *boss;

	bList[i].target_ = pPos;

	Vector2F v = bList[i].target_ - obj_[i].pos_;
	float size = sqrtf(v.x * v.x + v.y * v.y);
	bList[i].vec_ = (v / size) * 5.0f;

	bList[i].angle_ = 0.0f;
	bList[i].expansion_ = 0.0f;
	bList[i].BammoonBlast_ = false;
	bList[i].animeCounter_ = 0;

	obj_[i].inviCounter_ = 0;

	obj_[i].isAlive_ = true;
}

void BammoonBlast::Hit(int i)
{
	obj_[i].inviCounter_ = 1;
	BammoonBlastCount_++;
	obj_[i].size_ *= 2.0f;
	bList[i].BammoonBlast_ = true;
}