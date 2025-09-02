#include "TitleScene.h"

#include <DxLib.h>
#include <string>

#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include "../Manager/SoundManager.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Load(void)
{
	image_ = LoadGraph("Data/Image/Title.png");

	SoundManager::GetIns().Load(SoundManager::SOUND::BGM1);
}

void TitleScene::Init(void)
{
	SoundManager::GetIns().Play(SoundManager::SOUND::BGM1, false, 100, true);
}

void TitleScene::Update(void)
{
	auto& scnM = SceneManager::GetIns();

	// ÉVÅ[ÉìëJà⁄
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		//scnM.SetController(SceneManager::CNTL::KEY);
		scnM.ChangeScene(SceneManager::SCENE_ID::BOSSSELECT);
		return;
	}

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	{
		//scnM.SetController(SceneManager::CNTL::PAD);
		scnM.ChangeScene(SceneManager::SCENE_ID::BOSSSELECT);
		return;
	}

	if (CheckHitKey(KEY_INPUT_0)) { scnM.ChangeScene(SceneManager::SCENE_ID::TUTORIAL); return; }
}

void TitleScene::Draw(void)
{
	DrawGraph(0, 0, image_, true);

	std::string letter = "-- SPACE or B to START --";
	int fontSize = 32;
	SetFontSize(fontSize);
	DrawString((Application::SCREEN_SIZE_X / 2) -225, (int)(Application::SCREEN_SIZE_Y * 0.9f), letter.c_str(), RGB(255, 255, 255));
	SetFontSize(16);

}

void TitleScene::Release(void)
{
	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Delete(S::SOUND::BGM1);
	DeleteGraph(image_);
}

