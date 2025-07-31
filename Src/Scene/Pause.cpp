#include "Pause.h"
#include<string>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include"../Manager/Score/Score.h"

void Pause::Load(void)
{
	Camera::CreateInstance();
	

	std::string PATH = "Data/Image/MenuButton/";

	image_[SELECT::CONTINUE] = LoadGraph((PATH + "Continue Button.png").c_str());
	image_[SELECT::NEWGAME] = LoadGraph((PATH + "New game Button.png").c_str());
	image_[SELECT::EXIT] = LoadGraph((PATH + "Exit Button.png").c_str());

	select_ = SELECT::CONTINUE;
	pauseState_ = STATE::E_UPDATE;
	

}

void Pause::Init(void)
{
	obj_[SELECT::CONTINUE].pos_ = { 0.0f,0.0f };
	obj_[SELECT::NEWGAME].pos_  = { 0.0f,0.0f };
	obj_[SELECT::EXIT].pos_     = { 0.0f,0.0f };

	move_ = { 0.0f,0.0f };

	startPos_ = { 0.0f,0.0f };

	isExit     = false;

	for (int ii = 0; ii < SELECT::MAX; ii++) dispPos[ii] = { 0.0f, 0.0f };

	prevDecision = nowDecision = upKeyDecision = downKeyDecision = false;

	prevUp = nowUp = upKeyUp = downKeyUp = false;

	prevDown = nowDown = upKeyDown = downKeyDown = false;
}

void Pause::Update(void)
{
	SceneManager& scene_ = SceneManager::GetInstance();

	startPos_.x = 0;
	startPos_.y = 0;

	//使うキー
	KeyInput();

	float targetY = -(obj_[select_].pos_.y + select_ * DISTANCE);
	move_.y += (targetY - move_.y) * 0.2f;



	//選択中がどれかを見分ける
	switch (select_)
	{
	case Pause::CONTINUE:
		if (downKeyDecision) {
			SetPauseState(STATE::E_UPDATE);
			SoundManager::GetIns().Play(SoundManager::SOUND::HIBIODOSI, true);
		}
		if (downKeyDown) select_ = NEWGAME;
		break;
	case Pause::NEWGAME:

		if (downKeyUp)   select_ = CONTINUE;
		if (downKeyDown) select_ = EXIT;

		if (downKeyDecision)
		{
			pauseState_ = STATE::E_UPDATE;
			scene_.ChangeScene(SceneManager::SCENE_ID::TITLE);
			SoundManager::GetIns().Play(SoundManager::SOUND::HIBIODOSI, true);
		}

		break;
	case Pause::EXIT:
		if (downKeyDecision) {
			isExit = true;
		}
		if (downKeyUp) select_ = NEWGAME;
		break;
	}

	for (int ii = 0; ii < SELECT::MAX; ii++)
	{
		dispPos[ii].x = startPos_.x + obj_[ii].pos_.x + Application::SCREEN_SIZE_X / 2;
		dispPos[ii].y = move_.y + (startPos_.y + obj_[ii].pos_.y + Application::SCREEN_SIZE_Y / 2 + ii * DISTANCE);
	}

	if (CheckHitKey(KEY_INPUT_1) == 1 &&
		CheckHitKey(KEY_INPUT_5) == 1 &&
		CheckHitKey(KEY_INPUT_0) == 1) {
		Score::GetIns().RankingReset(BOSS_KINDS::MAX);
	}
}

void Pause::Draw(void)
{
	VECTOR startPos_;

	startPos_.x = 0;
	startPos_.y = 0;

	SetDrawBright(128, 128, 128);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 120);

	DrawBox(
		startPos_.x, startPos_.y,
		startPos_.x + Application::SCREEN_SIZE_X,
		startPos_.y + Application::SCREEN_SIZE_Y,
		RGB(200, 200, 200), true
	);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBright(255, 255, 255);

	//画像の描画
	for (int ii = 0; ii < SELECT::MAX; ++ii)
	{
		DrawRotaGraph(
			dispPos[ii].x,
			dispPos[ii].y,
			(select_==ii)?0.7:0.5f, 0.0f, image_[ii], true
		);
	}
}

void Pause::Release(void)
{
	for (int ii = 0; ii < SELECT::MAX; ii++)
	{
		DeleteGraph(image_[ii]);
	}

	Camera::DeleteInstance();
}

void Pause::SetPauseState(STATE state)
{
	pauseState_ = state;
	if (state == STATE::E_PAUSE) {
		SoundManager::GetIns().AllStop();
	}
	else if (state==STATE::E_UPDATE)
	{
		SoundManager::GetIns().PausePlay();
	}
}

void Pause::KeyInput(void)
{
	int input = GetJoypadInputState(DX_INPUT_PAD1);

	prevDecision = nowDecision;
	nowDecision = ((CheckHitKey(KEY_INPUT_SPACE) == 0) &&
		(CheckHitKey(KEY_INPUT_RETURN) == 0) &&
		((input & 0x40) == 0) && ((input & 0x20) == 0)) ? false : true;
	upKeyDecision = (prevDecision && !nowDecision);
	downKeyDecision = (!prevDecision && nowDecision);

	prevUp = nowUp;
	nowUp = ((CheckHitKey(KEY_INPUT_W) == 0) &&
		(CheckHitKey(KEY_INPUT_UP) == 0) &&
		((input & PAD_INPUT_UP) == 0)) ? false : true;
	upKeyUp = (prevUp && !nowUp);
	downKeyUp = (!prevUp && nowUp);

	prevDown = nowDown;
	nowDown = ((CheckHitKey(KEY_INPUT_S) == 0) &&
		(CheckHitKey(KEY_INPUT_DOWN) == 0) &&
		((input & PAD_INPUT_DOWN) == 0)) ? false : true;
	upKeyDown = (prevDown && !nowDown);
	downKeyDown = (!prevDown && nowDown);

}
