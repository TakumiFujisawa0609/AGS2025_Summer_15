#include"SelectPlayer.h"

#include<DxLib.h>

#include"../../../Application.h"
#include"../../../Manager/InputManager.h"

SelectPlayer::SelectPlayer()
{
}

SelectPlayer::~SelectPlayer()
{
}


void SelectPlayer::Init()
{
	LoadDivGraph((Application::PATH_PLAYER + "Idle.png").c_str(),
		ANIME_NUM, ANIME_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y, image_);
	bambooImg_ = LoadGraph("Data/Image/Player/BambooBar.png");
	LoadDivGraph("Data/Image/Player/–îˆó.png", 4, 4, 1, 183, 51, arrowImg_);


	pos_ = { Application::SCREEN_SIZE_X / 2,Application::SCREEN_SIZE_Y - 110 };
	animeCou_ = 0;
	animeInterval_ = 0;
	haveB_ = true;

	arrowAnime_ = 0;

	nowSelect_ = B_KINDS::RUNBOO; 
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

		if ((ins.IsTrgDown(KEY_INPUT_LEFT)) || (downLeftKey_)) {
			if (NullSelect(nowSelect_ - 1)) { nowSelect_ = (B_KINDS)(nowSelect_ - 1); };
		}
	
		if ((ins.IsTrgDown(KEY_INPUT_RIGHT)) || (downRightKey_)) {
			if (NullSelect(nowSelect_ + 1)) { nowSelect_ = (B_KINDS)(nowSelect_ + 1); };
		}

		if ((ins.IsTrgDown(KEY_INPUT_J)) || (nowAttackKey_)) {
			haveB_ = false;
		}

		bamboo_.pos_ = pos_;
		bamboo_.pos_.y -= 50.0f;
	}
	else {
		bamboo_.pos_ += vec_;
	}
}

void SelectPlayer::Draw()
{
	DrawRotaGraph(bamboo_.pos_.x, bamboo_.pos_.y, 1, atan2(vec_.y, vec_.x), bambooImg_, true);
	DrawRotaGraphF(pos_.x, pos_.y-18, 2.3, 0, image_[animeCou_], true);
	if (haveB_) { DrawRotaGraph(pos_.x, pos_.y, 1, atan2(vec_.y, vec_.x), arrowImg_[arrowAnime_], true); }
}

void SelectPlayer::Release()
{
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

bool SelectPlayer::NullSelect(int b)
{
	return (b == B_KINDS::TUTORIAL || b == B_KINDS::NOKOPY || b == B_KINDS::RUNBOO || b == B_KINDS::BAMMOON);
}

void SelectPlayer::JoyPadInputManager()
{
	int input = GetJoypadInputState(DX_INPUT_PAD1);

	prevLeftKey_ = nowLeftKey_;
	nowLeftKey_ = ((input & PAD_INPUT_LEFT) == 0) ? false : true;
	downLeftKey_ = (!prevLeftKey_ && nowLeftKey_);
	upLeftKey_ = (prevLeftKey_ && !nowLeftKey_);

	prevRightKey_ = nowRightKey_;
	nowRightKey_ = ((input & PAD_INPUT_RIGHT) == 0) ? false : true;
	downRightKey_ = (!prevRightKey_ && nowRightKey_);
	upRightKey_ = (prevRightKey_ && !nowRightKey_);

	nowAttackKey_ = ((input & 0x40) == 0) ? false : true;
}