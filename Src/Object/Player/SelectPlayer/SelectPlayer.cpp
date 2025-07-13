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


	pos_ = {};
	animeCou_ = 0;
	haveB_ = true;
}

void SelectPlayer::Update()
{
	if (++animeCou_ > ANIME_NUM) { animeCou_ = 0; }

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

		}
	}
}

void SelectPlayer::Draw()
{
	if (haveB_)DrawRotaGraph(pos_.x, pos_.y - 50, 1, 0, bambooImg_, true);
	DrawRotaGraphF(pos_.x, pos_.y, 1, 0, image_[animeCou_], true);
}

void SelectPlayer::Release()
{
	DeleteGraph(bambooImg_);
	for (auto& id : image_) { DeleteGraph(id); }

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