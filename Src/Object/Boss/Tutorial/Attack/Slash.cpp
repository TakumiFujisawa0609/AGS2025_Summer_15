#include"Slash.h"

#include<DxLib.h>

#include"../../../../Manager/Camera.h"
#include"../../../../Manager/SoundManager.h"

#include"../BossTutorial.h"

Slash::Slash()
{
	image_ = -1;
	LoadDivGraph("Data/Image/Boss/SlashAnim.png", ANIM_ALL,
		X_NUM, Y_NUM, X_SIZE, Y_SIZE, img);
}

Slash::~Slash()
{
}

void Slash::Init(const Vector2F* pos)
{

	AttackBase::Init(pos);
	
	obj_.size_ = { (float)X_SIZE,(float)Y_SIZE };
	obj_.radius_ = obj_.size_.x;
	obj_.isDraw_ = false;
	
	animCounter_ = 0;
	startCnt = CHARGE;


	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Load(S::SOUND::TUTORIALSLASH);
}

void Slash::Update()
{
	startCnt--;
	obj_.isDraw_ = true;

	if (obj_.isAlive_) {
		if (animCounter_ == 0)SoundManager::GetIns().Play(SoundManager::SOUND::TUTORIALSLASH, true, 200);

		switch (dir_)
		{
		case Slash::LEFT:
			obj_.pos_ = { boss->x - BossTutorial::SIZE_X / 2,boss->y };
			isTurn = true;
			break;
		case Slash::RIGHT:
			obj_.pos_ = { boss->x + BossTutorial::SIZE_X / 2,boss->y };
			isTurn = false;
			break;
		}

		animCounter_++;

		if (animCounter_ > ANIM_ALL) {
			obj_.isAlive_ = false;
			animCounter_ = ANIM_ALL;
		}
	}
	else if (animCounter_ > 0) {
		attackCounter_++;
		if (attackCounter_ > 120) {
			attackCounter_ = 0;
			startCnt = CHARGE;
			end_ = true;
		}
	}

	AttackBase::Update();
}

void Slash::Draw()
{
	if (obj_.isAlive_)
	{
		float diff = (isTurn) ? -(X_SIZE / 2) : (X_SIZE / 2);
		DrawRotaGraph(obj_.disppos_.x + diff, obj_.disppos_.y, 1.0f, 0.0f, img[animCounter_], true, isTurn);
	}
}

void Slash::Release()
{
	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Delete(S::SOUND::TUTORIALSLASH);

	for (int ii = 0; ii < ANIM_ALL; ii++) {
		DeleteGraph(img[ii]);
	}
	DeleteGraph(image_);
}

