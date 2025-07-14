#include"Csphere.h"

#include<DxLib.h>

Csphere::Csphere()
{
}

Csphere::~Csphere()
{
}

void Csphere::Init(const Vector2F* pos)
{
	int err = 0;
	err = LoadDivGraph("Data/Image/Boss/Bammoon/AttackEffect/Csphere/Csphere.png", ANIME_NUM, ANIME_NUM, 1, LOAD_SIZE, LOAD_SIZE, img_);


	bossPos_ = pos;

	scale_ = DEFAULT_SCALE;
	obj_.size_ = { DEFAULT_SIZE,DEFAULT_SIZE };
	obj_.radius_ = DEFAULT_SIZE / 2.0f;

	obj_ = {};

	moveVec_ = {};

	animCou_ = 0;
	animInterval_ = 0;

	aliveCou_ = ALIVE_TIME;

	flo_ = 0;
	floMove_ = {};

	end_ = false;
}

void Csphere::Update(void)
{
	if (!obj_.isAlive_)return;

	if (--aliveCou_ <= 0) { obj_.isAlive_ = false; end_ = true; return; }

	if (obj_.inviCounter_ > 0)obj_.inviCounter_--;

	obj_.pos_ += moveVec_;
	
	if (aliveCou_ % 15 == 0) {
		if (++flo_ > 50)flo_ = 0;
		floMove_ = {(float)sin(flo_) * 3.0f, (float)cos(flo_) * 3.0f};
	}
	obj_.pos_ += floMove_;

	ChangeDispPos();
	SetScale();
	Animation();
}

void Csphere::Draw(void)
{
	if (!obj_.isAlive_)return;


	DrawRotaGraph(obj_.disppos_.x, obj_.disppos_.y, scale_, 0, img_[animCou_], true);
}

void Csphere::Release(void)
{
	for (int& id : img_) { DeleteGraph(id); }
}

void Csphere::CorceChange(Vector2F pPos)
{
	Vector2F v = pPos - obj_.pos_;
	float size = sqrtf(v.x * v.x + v.y * v.y);
	v /= size;

	moveVec_ = v * SPEED;
}

void Csphere::SetScale(void)
{
	if (aliveCou_ <= 100) {
		scale_ = aliveCou_ / 50.0f;
	}
	else {
		// ƒfƒtƒHƒ‹ƒg‚ÌŠg‘å”{—¦‚É0`0.5‚ð‰ÁŽZ‚·‚é
		float s = (float)sin(flo_);
		scale_ = DEFAULT_SCALE + (((s < 0.0f) ? s * -1 : s) / 2.0f);
	}

	// “–‚½‚è”»’è‚ÉŽg—p‚·‚éƒTƒCƒY‚ðŠi”[‚·‚é•Ï”‚É•ÏX‚µ‚½Šg‘å”{—¦‚ð“K—p‚µ‚½³‚µ‚¢ƒTƒCƒY‚ðŠi”[‚·‚é
	obj_.size_ = { LOAD_SIZE * scale_,LOAD_SIZE * scale_ };
	obj_.radius_ = (LOAD_SIZE * scale_) / 2.0f;
}

void Csphere::Animation(void)
{
	if (++animInterval_ >= ANIME_SPEED) {
		animInterval_ = 0;
		if (++animCou_ >= ANIME_NUM)animCou_ = 0;
	}
}


void Csphere::On(Vector2F pPos)
{
	obj_.pos_ = *bossPos_;
	ChangeDispPos();
	CorceChange(pPos);
	obj_.isAlive_ = true;
	end_ = false;
	aliveCou_ = ALIVE_TIME;
	obj_.inviCounter_ = 0;
}

void Csphere::Hit(void)
{
	if (aliveCou_ > 100) {
		aliveCou_ -= 500;
		if (aliveCou_ < 100)aliveCou_ = 100;
	}
	obj_.inviCounter_ = 20;
}