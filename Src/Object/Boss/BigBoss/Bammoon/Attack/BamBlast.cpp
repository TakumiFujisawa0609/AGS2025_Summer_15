#include"BamBlast.h"

#include<DxLib.h>
#include<cmath>

#include"../../../../../Manager/Camera.h"
#include"../../../../../Manager/SoundManager.h"


BamBlast::BamBlast()
{

}

BamBlast::~BamBlast()
{
}

using SOUND = SoundManager::SOUND;

void BamBlast::Init(const Vector2F* pos)
{
	AttackBase::Init(pos);

	reticleImg_ = LoadGraph("Data/Image/Boss/Reticle.png");
	LoadDivGraph("Data/Image/Effect/Blast.png", BLAST_NUM_MAX, BLAST_NUM_X, BLAST_NUM_Y, BLAST_SIZE, BLAST_SIZE, blastImg_);
	img = LoadGraph("Data/Image/Boss/Bomb.png");

	blastCount_ = 0;
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
		b.blast_ = false;
		b.animeCounter_ = 0;
	}

	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Load(SOUND::BAMMOONBLAST);
	sound.Load(SOUND::BAMMOONBLASTTHROW);
}
void BamBlast::Update(void)
{
	int i = -1;
	for (auto& o : obj_) {
		i++;
		if (!o.isAlive_)continue;

		if (!bList[i].blast_) {

			o.pos_ += bList[i].vec_;

			Vector2F v = bList[i].target_ - o.pos_;
			float dis = sqrtf(v.x * v.x + v.y * v.y);

			if (dis < 5.0f) {
				blastCount_++;
				o.size_ *= 2.0f;
				bList[i].blast_ = true;
				SoundManager::GetIns().Play(SOUND::BAMMOONBLAST, true, 200);
			}

		}
		else {
			bList[i].animeCounter_++;
			if (bList[i].animeCounter_ > BLAST_NUM_MAX) o.isAlive_ = false;
		}

		bList[i].angle_ += 0.1f;
		bList[i].expansion_ = std::sin(bList[i].angle_);
	}

	if (blastCount_ >= MAX_NUM)end_ = true;
}
void BamBlast::Draw(void)
{
	auto& camera = Camera::GetInstance();

	int i = -1;
	for (auto& o : obj_) {
		i++;
		if (!o.isAlive_)continue;

		Vector2F disp = { bList[i].target_.x - camera.GetPos().x,bList[i].target_.y - camera.GetPos().y };
		DrawRotaGraph(disp.x, disp.y, bList[i].expansion_, bList[i].angle_, reticleImg_, true);

		DrawRotaGraph(o.pos_.x, o.pos_.y, (bList[i].blast_) ? 0.5 : 1, 0,
			(bList[i].blast_) ? blastImg_[bList[i].animeCounter_] : img, true);
	}
}
void BamBlast::Release(void)
{
	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Delete(SOUND::BAMMOONBLASTTHROW);
	sound.Delete(SOUND::BAMMOONBLAST);

	for (int i = 0; i < BLAST_NUM_MAX; i++) {
		DeleteGraph(blastImg_[i]);
	}
	DeleteGraph(reticleImg_);
}


void BamBlast::On(int i, Vector2F pPos)
{
	if (obj_.size() <= i)return;

	if (i == 0) { end_ = false; blastCount_ = 0; }

	obj_[i].pos_ = *boss;

	bList[i].target_ = pPos;

	Vector2F v = bList[i].target_ - obj_[i].pos_;
	float size = sqrtf(v.x * v.x + v.y * v.y);
	bList[i].vec_ = (v / size) * 5.0f;

	bList[i].angle_ = 0.0f;
	bList[i].expansion_ = 0.0f;
	bList[i].blast_ = false;
	bList[i].animeCounter_ = 0;

	obj_[i].radius_ = 45.0f;
	obj_[i].size_ = { obj_[i].radius_,obj_[i].radius_ };

	obj_[i].inviCounter_ = 0;

	obj_[i].isAlive_ = true;

	SoundManager::GetIns().Play(SOUND::BAMMOONBLASTTHROW, true, 200);
}

void BamBlast::Hit(int i)
{
	if (obj_.size() <= i)return;

	obj_[i].inviCounter_ = 1;
	blastCount_++;
	obj_[i].size_ *= 2.0f;
	bList[i].blast_ = true;
}