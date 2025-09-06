#include"SelectPlayer.h"

#include<DxLib.h>

#include"../../../Application.h"
#include"../../../Manager/InputManager.h"
#include"../../../Manager/KeyManager.h"
#include"../../../Manager/SoundManager.h"
#include"../../../Manager/Score/Score.h"

SelectPlayer::SelectPlayer()
{
}

SelectPlayer::~SelectPlayer()
{
}

using BOSS = SceneManager::BOSS_KINDS;

void SelectPlayer::Init()
{
	LoadDivGraph((Application::PATH_PLAYER + "Idle.png").c_str(),
		ANIME_NUM, ANIME_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y, image_);
	bambooImg_ = LoadGraph("Data/Image/Player/BambooBar.png");
	LoadDivGraph("Data/Image/Player/–îˆó.png", 4, 4, 1, 183, 51, arrowImg_);


	pos_ = { Application::SCREEN_SIZE_X / 2 - 20,Application::SCREEN_SIZE_Y - 110 };
	animeCou_ = 0;
	animeInterval_ = 0;
	haveB_ = true;

	arrowAnime_ = 0;

	nowSelect_ = BOSS::TUTORIAL;

	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Load(S::SOUND::BPTHROW);
}

void SelectPlayer::Update()
{
	if (++animeInterval_ >= ANIME_SPEED) {
		animeInterval_ = 0;
		if (++animeCou_ >= ANIME_NUM) { animeCou_ = 0; }
		static int inter = 0;
		if (++inter >= ANIME_SPEED) {
			inter = 0;
			if (++arrowAnime_ >= 4) { arrowAnime_ = 0; }
		}
	}

	if (haveB_) {
		auto& key = KEY::GetIns();

		switch (nowSelect_)
		{
		case SceneManager::BOSS_KINDS::TUTORIAL:
			if (key.GetInfo(KEY_TYPE::MOVE_LEFT).down) { nowSelect_ = BOSS::BAMMOON; }
			if (key.GetInfo(KEY_TYPE::MOVE_RIGHT).down || key.GetInfo(KEY_TYPE::MOVE_DOWN).down) { nowSelect_ = BOSS::NOKOPY; }
			break;
		case SceneManager::BOSS_KINDS::NOKOPY:
			if (key.GetInfo(KEY_TYPE::MOVE_LEFT).down || key.GetInfo(KEY_TYPE::MOVE_UP).down) { nowSelect_ = BOSS::TUTORIAL; }
			break;
		case SceneManager::BOSS_KINDS::BAMMOON:
			if (key.GetInfo(KEY_TYPE::MOVE_LEFT).down || key.GetInfo(KEY_TYPE::MOVE_DOWN).down) { nowSelect_ = BOSS::RUNBOO; }
			if (key.GetInfo(KEY_TYPE::MOVE_RIGHT).down) { nowSelect_ = BOSS::TUTORIAL; }
			break;
		case SceneManager::BOSS_KINDS::RUNBOO:
			if (key.GetInfo(KEY_TYPE::MOVE_RIGHT).down || key.GetInfo(KEY_TYPE::MOVE_UP).down) { nowSelect_ = BOSS::BAMMOON; }
			break;
		}

		bamboo_.pos_ = pos_;
		bamboo_.pos_.y -= 50.0f;

		//if (nowSelect_ != BOSS::RUNBOO) {
		if (key.GetInfo(KEY_TYPE::ENTER).down) {
			haveB_ = false;
			SoundManager::GetIns().Play(SoundManager::SOUND::BPTHROW, true);
		}
		//}
	}
	else {
		bamboo_.pos_ += vec_;
	}

	if (CheckHitKey(KEY_INPUT_1) == 1 &&
		CheckHitKey(KEY_INPUT_5) == 1 &&
		CheckHitKey(KEY_INPUT_0) == 1) {
		Score::GetIns().RankingReset(nowSelect_);
	}
}

void SelectPlayer::Draw()
{
	DrawRotaGraphF(bamboo_.pos_.x, bamboo_.pos_.y, 1, atan2(vec_.y, vec_.x), bambooImg_, true);

	bool reverse = (nowSelect_ != BOSS::RUNBOO);
	DrawRotaGraphF(pos_.x, pos_.y-18, 2.3, 0, image_[animeCou_], true,reverse);
	if (haveB_) { DrawRotaGraph(pos_.x, pos_.y, 1, atan2(vec_.y, vec_.x), arrowImg_[arrowAnime_], true); }
}

void SelectPlayer::Release()
{
	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Delete(S::SOUND::BPTHROW);

	DeleteGraph(bambooImg_);
	for (auto& id : image_) { DeleteGraph(id); }

}

void SelectPlayer::SetVec(Vector2F target)
{
	Vector2F vec = target - bamboo_.pos_;
	float size = sqrtf(vec.x * vec.x + vec.y * vec.y);
	this->vec_ = vec / size;
	this->vec_ *= BAMBOO_SPEED;
}