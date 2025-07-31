#include"SelectPlayer.h"

#include<DxLib.h>

#include"../../../Application.h"
#include"../../../Manager/InputManager.h"
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

	nowSelect_ = BOSS::BAMMOON; 

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
		auto& ins = InputManager::GetInstance();
		JoyPadInputManager();

		switch (nowSelect_)
		{
		case SceneManager::BOSS_KINDS::TUTORIAL:
			if ((ins.IsTrgDown(KEY_INPUT_LEFT)) || (ins.IsTrgDown(KEY_INPUT_A)) ||
				(downLeftKey_)) {
				nowSelect_ = BOSS::BAMMOON;
			}
			if ((ins.IsTrgDown(KEY_INPUT_RIGHT)) || (ins.IsTrgDown(KEY_INPUT_D)) ||
				(ins.IsTrgDown(KEY_INPUT_DOWN)) || (ins.IsTrgDown(KEY_INPUT_S)) ||
				(downRightKey_) || (downDownKey_)) {
				nowSelect_ = BOSS::NOKOPY;
			}
			break;
		case SceneManager::BOSS_KINDS::NOKOPY:
			if ((ins.IsTrgDown(KEY_INPUT_LEFT)) || (ins.IsTrgDown(KEY_INPUT_A)) ||
				(ins.IsTrgDown(KEY_INPUT_UP)) || (ins.IsTrgDown(KEY_INPUT_W)) ||
				(downLeftKey_) || (downUpKey_)) {
				nowSelect_ = BOSS::TUTORIAL;
			}
			break;
		case SceneManager::BOSS_KINDS::BAMMOON:
			if ((ins.IsTrgDown(KEY_INPUT_LEFT)) || (ins.IsTrgDown(KEY_INPUT_A)) ||
				(ins.IsTrgDown(KEY_INPUT_DOWN)) || (ins.IsTrgDown(KEY_INPUT_S)) ||
				(downLeftKey_) || (downDownKey_)) {
				nowSelect_ = BOSS::RUNBOO;
			}
			if ((ins.IsTrgDown(KEY_INPUT_RIGHT)) || (ins.IsTrgDown(KEY_INPUT_D)) ||
				(downRightKey_)) {
				nowSelect_ = BOSS::TUTORIAL;
			}

			break;
		case SceneManager::BOSS_KINDS::RUNBOO:
			if ((ins.IsTrgDown(KEY_INPUT_RIGHT)) || (ins.IsTrgDown(KEY_INPUT_D)) ||
				(ins.IsTrgDown(KEY_INPUT_UP)) || (ins.IsTrgDown(KEY_INPUT_W)) ||
				(downRightKey_) || (downUpKey_)) {
				nowSelect_ = BOSS::BAMMOON;
			}
			break;
		}

		bamboo_.pos_ = pos_;
		bamboo_.pos_.y -= 50.0f;

		if (nowSelect_ != BOSS::RUNBOO) {
			if ((ins.IsTrgDown(KEY_INPUT_SPACE)) || (ins.IsTrgDown(KEY_INPUT_RETURN)) ||
				(ins.IsTrgDown(KEY_INPUT_J)) || (nowAttackKey_)) {
				haveB_ = false;
				SoundManager::GetIns().Play(SoundManager::SOUND::BPTHROW, true);
			}
		}
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

void SelectPlayer::JoyPadInputManager()
{
	int input = GetJoypadInputState(DX_INPUT_PAD1);

	prevUpKey_ = nowUpKey_;
	nowUpKey_ = ((input & PAD_INPUT_UP) == 0) ? false : true;
	downUpKey_ = (!prevUpKey_ && nowUpKey_);
	upUpKey_ = (prevUpKey_ && !nowUpKey_);

	prevDownKey_ = nowDownKey_;
	nowDownKey_ = ((input & PAD_INPUT_DOWN) == 0) ? false : true;
	downDownKey_ = (!prevDownKey_ && nowDownKey_);
	upDownKey_ = (prevDownKey_ && !nowDownKey_);

	prevLeftKey_ = nowLeftKey_;
	nowLeftKey_ = ((input & PAD_INPUT_LEFT) == 0) ? false : true;
	downLeftKey_ = (!prevLeftKey_ && nowLeftKey_);
	upLeftKey_ = (prevLeftKey_ && !nowLeftKey_);

	prevRightKey_ = nowRightKey_;
	nowRightKey_ = ((input & PAD_INPUT_RIGHT) == 0) ? false : true;
	downRightKey_ = (!prevRightKey_ && nowRightKey_);
	upRightKey_ = (prevRightKey_ && !nowRightKey_);

	nowAttackKey_ = (((input & 0x40) == 0) && ((input & 0x20) == 0)) ? false : true;
}