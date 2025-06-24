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
	VECTOR startPos_;

	startPos_.x = ((Application::MAIN_SCREEN_SIZE_X - Application::SCREEN_SIZE_X) / 2) + Camera::GetInstance().GetPos().x;
	startPos_.y = ((Application::MAIN_SCREEN_SIZE_Y - Application::SCREEN_SIZE_Y) / 2) + Camera::GetInstance().GetPos().y;

	for (int i = 0; i < SELECT::MAX; ++i)
	{
		DrawRotaGraph(
			startPos_.x + obj_[i].pos_.x + Application::SCREEN_SIZE_X / 2,
			move_.y + (startPos_.y + obj_[i].pos_.y + Application::SCREEN_SIZE_Y / 2 + i * DISTANCE),
			0.5f, 0.0f, image_[i], true
		);
	}

	obj_[SELECT::CONTINUE].pos_ = { 0.0f,0.0f };
	obj_[SELECT::NEWGAME].pos_  = { 0.0f,0.0f };
	obj_[SELECT::EXIT].pos_     = { 0.0f,0.0f };

	move_ = { 0.0f,0.0f };

	isNewGame  = false;
	isExit     = false;

	for (int ii = 0; ii < 2; ii++)
	{
		prevDecision[ii] = 0;
		nowDecision[ii]  = 0;

		prevUp[ii] = 0;
		nowUp[ii]  = 0;

		prevDown[ii] = 0;
		nowDown[ii]  = 0;
	}
}

void Pause::Update(void)
{
	//使うキー
	KeyInput();

	float targetY = -(obj_[select_].pos_.y + select_ * DISTANCE);

	move_.y += (targetY - move_.y) * 0.2f;

	for (int ii = 0; ii < 2; ii++)
	{
		bool isDecision = prevDecision[ii] == 1 && nowDecision[ii] == 0;
		bool isUp = prevUp[ii] == 0 && nowUp[ii] == 1;
		bool isDown = prevDown[ii] == 0 && nowDown[ii] == 1;

		switch (select_)
		{
		case Pause::CONTINUE:
			if (isDecision) pauseState_ = STATE::E_UPDATE;
			if (isDown) select_ = NEWGAME;
			break;

		case Pause::NEWGAME:
			if (isDecision) isNewGame = true;
			if (isUp)   select_ = CONTINUE;
			if (isDown) select_ = EXIT;
			break;

		case Pause::EXIT:
			if (isDecision) isExit = true;
			if (isUp) select_ = NEWGAME;
			break;
		}
	}
}

void Pause::Draw(void)
{
	VECTOR startPos_;

	startPos_.x = ((Application::MAIN_SCREEN_SIZE_X - Application::SCREEN_SIZE_X) / 2);
	startPos_.y = ((Application::MAIN_SCREEN_SIZE_Y - Application::SCREEN_SIZE_Y) / 2);

	//switch (select_)
	//{
	//case Pause::CONTINUE:
	//	DrawString(startPos_.x, startPos_.y, "CONTINUE", RGB(255, 255, 255), true);
	//	break;
	//case Pause::NEWGAME:
	//	DrawString(startPos_.x, startPos_.y, "NEWGAME", RGB(255, 255, 255), true);
	//	break;
	//case Pause::EXIT:
	//	DrawString(startPos_.x, startPos_.y, "EXIT", RGB(255, 255, 255), true);
	//	break;
	//}

	for (int i = 0; i < SELECT::MAX; ++i)
	{
		DrawRotaGraph(
			startPos_.x + obj_[i].pos_.x + Application::SCREEN_SIZE_X / 2,
			move_.y + (startPos_.y + obj_[i].pos_.y + Application::SCREEN_SIZE_Y / 2 + i * DISTANCE),
			0.5f, 0.0f, image_[i], true
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
		//参考演算子まじで便利
		int keyDecision = (ii) ? CheckHitKey(KEY_INPUT_SPACE) : CheckHitKey(KEY_INPUT_RETURN);
		int keyUp = (ii) ? CheckHitKey(KEY_INPUT_W) : CheckHitKey(KEY_INPUT_UP);
		int keyDown = (ii) ? CheckHitKey(KEY_INPUT_S) : CheckHitKey(KEY_INPUT_DOWN);

		prevDecision[ii] = nowDecision[ii];
		nowDecision[ii] = keyDecision;

		prevUp[ii] = nowUp[ii];
		nowUp[ii] = keyUp;

		prevDown[ii] = nowDown[ii];
		nowDown[ii] = keyDown;
	}
}
