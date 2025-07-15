#include "Pause.h"
#include<string>
#include "../Application.h"
#include "../Manager/SceneManager.h"

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

	for (int ii = 0; ii < 2; ii++)
	{
		prevDecision[ii] = 0;
		nowDecision[ii]  = 0;

		prevUp[ii] = 0;
		nowUp[ii]  = 0;

		prevDown[ii] = 0;
		nowDown[ii]  = 0;
	}

	prevPadDecision = 0;
	nowPadDecision = 0;

	prevPadDown = 0;
	nowPadDown = 0;

	prevPadUp = 0;
	nowPadUp = 0;
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

	int pad = GetJoypadInputState(DX_INPUT_PAD1);

	prevPadDecision = nowPadDecision;
	nowPadDecision = (pad & PAD_INPUT_A);

	prevPadUp = nowPadUp;
	nowPadUp = (pad & PAD_INPUT_UP);

	prevPadDown = nowPadDown;
	nowPadDown = (pad & PAD_INPUT_DOWN);

	for (int ii = 0; ii < 2; ii++)
	{
		//決定ボタン（アップトリガー）
		bool isDecision = prevDecision[ii] == 1 && nowDecision[ii] == 0;

		//上キー（ダウントリガー）
		bool isUp = prevUp[ii] == 0 && nowUp[ii] == 1;

		//下キー（ダウントリガー）
		bool isDown = prevDown[ii] == 0 && nowDown[ii] == 1;
		

		//選択中がどれかを見分ける
		switch (select_)
		{
		case Pause::CONTINUE:
			if (isDecision) pauseState_ = STATE::E_UPDATE;
			if (isDown || (prevPadDown == 0 && nowPadDown != 0)) select_ = NEWGAME;
			break;
		case Pause::NEWGAME:
		
			if (isUp || (prevPadUp == 0 && nowPadUp != 0))   select_ = CONTINUE;
			if (isDown || (prevPadDown == 0 && nowPadDown != 0)) select_ = EXIT;

			if (isDecision)
			{
				pauseState_ = STATE::E_UPDATE;
				scene_.ChangeScene(SceneManager::SCENE_ID::TITLE);
			}

			break;
		case Pause::EXIT:
			if (isDecision) isExit = true;
			if (isUp || (prevPadUp == 0 && nowPadUp != 0)) select_ = NEWGAME;
			break;
		}
	}

	for (int ii = 0; ii < SELECT::MAX; ii++)
	{
		dispPos[ii].x = startPos_.x + obj_[ii].pos_.x + Application::SCREEN_SIZE_X / 2;
		dispPos[ii].y = move_.y + (startPos_.y + obj_[ii].pos_.y + Application::SCREEN_SIZE_Y / 2 + ii * DISTANCE);
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

void Pause::KeyInput(void)
{
	for (int ii = 0; ii < 2; ii++)
	{
		int keyDecision = CheckHitKey((ii) ? KEY_INPUT_SPACE : KEY_INPUT_RETURN);
		int keyUp       = CheckHitKey((ii) ? KEY_INPUT_W : KEY_INPUT_UP);
		int keyDown     = CheckHitKey((ii) ? KEY_INPUT_S : KEY_INPUT_DOWN);

		prevDecision[ii] = nowDecision[ii];
		nowDecision[ii] = keyDecision;

		prevUp[ii] = nowUp[ii];
		nowUp[ii] = keyUp;

		prevDown[ii] = nowDown[ii];
		nowDown[ii] = keyDown;
	}
}
