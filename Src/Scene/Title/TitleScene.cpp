#include "TitleScene.h"

#include <DxLib.h>
#include <string>

#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/KeyManager.h"
#include "../../Manager/Camera.h"
#include "../../Manager/SoundManager.h"

#include"Play/PlayScene.h"
#include"End/EndScene.h"

TitleScene::TitleScene(void):
	image_(-1),
	nowSelect_(TitleScene::SELECT::PLAY)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Load(void)
{
	image_ = LoadGraph("Data/Image/Title/Title.png");

	playImg_ = AsoUtility::LoadImg("Data/Image/Title/Play.png");
	exitImg_ = AsoUtility::LoadImg("Data/Image/Title/Exit.png");
	selectFrameImg_ = AsoUtility::LoadImg("Data/Image/Title/Select.png");

	SoundManager::GetIns().Load(SoundManager::SOUND::BGM1);
}

void TitleScene::Init(void)
{
	SoundManager::GetIns().Play(SoundManager::SOUND::BGM1, false, 100, true);

	nowSelect_ = TitleScene::SELECT::PLAY;
}

void TitleScene::Update(void)
{
	auto& scnM = SceneManager::GetIns();

	// ÉVÅ[ÉìëJà⁄
	InputManager& ins = InputManager::GetInstance();

	auto& key = KEY::GetIns();

	switch (nowSelect_)
	{
	case TitleScene::SELECT::PLAY:
		if (key.GetInfo(KEY_TYPE::MOVE_RIGHT).down) { nowSelect_ = TitleScene::SELECT::EXIT; Smng::GetIns().Play(SOUND::SE_SYSTEM_SELECT, true); }
		if (key.GetInfo(KEY_TYPE::ENTER).down) { scnM.PushScene(std::make_shared<PlayScene>()); Smng::GetIns().Play(SOUND::SE_SYSTEM_BUTTON, true); return; }
		break;
	case TitleScene::SELECT::EXIT:
		if (key.GetInfo(KEY_TYPE::MOVE_LEFT).down) { nowSelect_ = TitleScene::SELECT::PLAY; Smng::GetIns().Play(SOUND::SE_SYSTEM_SELECT, true); }
		if (key.GetInfo(KEY_TYPE::ENTER).down) { SceneManager::GetIns().PushScene(std::make_shared<EndScene>()); Smng::GetIns().Play(SOUND::SE_SYSTEM_BUTTON, true); return; }
		break;
	}
}

void TitleScene::Draw(void)
{
	DrawGraph(0, 0, image_, true);


	float scale = 0.25f;
	DrawRotaGraph(SELECT_POS[(int)SELECT::PLAY].x, SELECT_POS[(int)SELECT::PLAY].y, scale, 0, playImg_, true);
	DrawRotaGraph(SELECT_POS[(int)SELECT::EXIT].x, SELECT_POS[(int)SELECT::EXIT].y, scale, 0, exitImg_, true);
	DrawRotaGraph(SELECT_POS[(int)nowSelect_].x, SELECT_POS[(int)nowSelect_].y, scale, 0, selectFrameImg_, true);

	
}

void TitleScene::Release(void)
{
	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Delete(S::SOUND::BGM1);

	DeleteGraph(playImg_);
	DeleteGraph(exitImg_);
	DeleteGraph(selectFrameImg_);
	DeleteGraph(image_);
}

