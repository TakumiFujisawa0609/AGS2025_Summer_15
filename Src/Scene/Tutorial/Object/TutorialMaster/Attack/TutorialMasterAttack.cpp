#include"TutorialMasterAttack.h"

#include"../../../../../Utility/AsoUtility.h"

#include"../../../../../Manager/SoundManager.h"

TutorialMasterAttack::TutorialMasterAttack(const Vector2F& pos):
	masterPos_(pos),
	img_(),
	animeCounter_(0),
	animeInterval_(0),
	obj_()
{
}

TutorialMasterAttack::~TutorialMasterAttack()
{
}

void TutorialMasterAttack::Load(void)
{
	AsoUtility::LoadArrayImg("Data/Image/Tutorial/Master/Attack/SlashAnim.png", ANIME_NUM, ANIME_NUM, 1, LOAD_SIZE_X, LOAD_SIZE_Y, img_);

	obj_.size_ = { SIZE_X,SIZE_Y };

	Smng::GetIns().Load(SOUND::SLASH);
}

void TutorialMasterAttack::Init(void)
{
	obj_.isAlive_ = false;
}

void TutorialMasterAttack::Update(void)
{
	if (!obj_.isAlive_) { return; }

	obj_.pos_.x -= SPEED;

	if (obj_.pos_.x + (obj_.size_.x / 2) < 0.0f) { obj_.isAlive_ = false; return; }

	if (++animeInterval_ >= 5) {
		animeInterval_ = 0;
		if (++animeCounter_ >= ANIME_NUM) { animeCounter_ = 0; }
	}
}

void TutorialMasterAttack::Draw(void)
{
	if (!obj_.isAlive_) { return; }

	DrawRotaGraph(obj_.pos_.x, obj_.pos_.y, DRAW_SCALE, 0, img_[animeCounter_], true, true);
}

void TutorialMasterAttack::Release(void)
{
	Smng::GetIns().Delete(SOUND::SLASH);

	for (auto& id : img_) { DeleteGraph(id); }
}

void TutorialMasterAttack::On(void)
{
	obj_.pos_ = masterPos_;
	obj_.pos_.x -= obj_.size_.x / 2.0f;
	obj_.pos_.y += obj_.size_.y / 4.0f;

	animeCounter_ = animeInterval_ = 0;

	obj_.isAlive_ = true;
	
	Smng::GetIns().Play(SOUND::SLASH, true);
}