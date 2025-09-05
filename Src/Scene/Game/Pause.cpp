#include "Pause.h"
#include<string>
#include "../../Application.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Manager/KeyManager.h"

void Pause::Load(void)
{
	Camera::CreateInstance();
	

	std::string PATH = "Data/Image/MenuButton/";

	image_[SELECT::CONTINUE] = LoadGraph((PATH + "ゲームにもどる.png").c_str());
	image_[SELECT::NEWGAME] = LoadGraph((PATH + "最初からやり直す.png").c_str());
	image_[SELECT::EXIT] = LoadGraph((PATH + "タイトルにもどる.png").c_str());

	select_ = SELECT::CONTINUE;
}

void Pause::Init(void)
{
	SoundManager::GetIns().AllStop();

	obj_[SELECT::CONTINUE].pos_ = { 0.0f,0.0f };
	obj_[SELECT::NEWGAME].pos_  = { 0.0f,0.0f };
	obj_[SELECT::EXIT].pos_     = { 0.0f,0.0f };

	move_ = { 0.0f,0.0f };

	startPos_ = { 0.0f,0.0f };

	for (int ii = 0; ii < SELECT::MAX; ii++) dispPos[ii] = { 0.0f, 0.0f };
}

void Pause::Update(void)
{
	SceneManager& scene_ = SceneManager::GetIns();

	startPos_.x = 0;
	startPos_.y = 0;

	float targetY = -(obj_[select_].pos_.y + select_ * DISTANCE);
	move_.y += (targetY - move_.y) * 0.2f;


	auto& key = KEY::GetIns();

	//選択中がどれかを見分ける
	switch (select_)
	{
	case Pause::CONTINUE:
		if (key.GetInfo(KEY_TYPE::MOVE_DOWN).down) { select_ = NEWGAME; }


		if (key.GetInfo(KEY_TYPE::ENTER).down) {
			scene_.PopScene();
			SoundManager::GetIns().Play(SoundManager::SOUND::HIBIODOSI, true);
			SoundManager::GetIns().PausePlay();
		}

		break;
	case Pause::NEWGAME:

		if (key.GetInfo(KEY_TYPE::MOVE_UP).down) { select_ = CONTINUE; }
		if (key.GetInfo(KEY_TYPE::MOVE_DOWN).down) { select_ = EXIT; }

		if (key.GetInfo(KEY_TYPE::ENTER).down)
		{
			SoundManager::GetIns().PauseInfoDelete();
			scene_.JumpScene(SceneManager::SCENE_ID::BATTLEDONE);
			SoundManager::GetIns().Play(SoundManager::SOUND::HIBIODOSI, true);
		}

		break;
	case Pause::EXIT:
		if (key.GetInfo(KEY_TYPE::MOVE_UP).down) { select_ = NEWGAME; }

		if (key.GetInfo(KEY_TYPE::ENTER).down) {
			SoundManager::GetIns().PauseInfoDelete();
			scene_.JumpScene(SceneManager::SCENE_ID::TITLE);
			SoundManager::GetIns().Play(SoundManager::SOUND::HIBIODOSI, true);
		}
		break;
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