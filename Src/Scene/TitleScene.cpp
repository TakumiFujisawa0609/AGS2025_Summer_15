#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	image_ = LoadGraph("Data/Image/Title.png");
}

void TitleScene::Update(void)
{
	auto& scnM = SceneManager::GetInstance();

	// ÉVÅ[ÉìëJà⁄
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		scnM.SetController(SceneManager::CNTL::KEY);
		scnM.ChangeScene(SceneManager::SCENE_ID::BOSSSELECT);
	}

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	{
		scnM.SetController(SceneManager::CNTL::PAD);
		scnM.ChangeScene(SceneManager::SCENE_ID::BOSSSELECT);
	}
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
	DeleteGraph(image_);
}

