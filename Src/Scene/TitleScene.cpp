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

}

void TitleScene::Update(void)
{
	auto& scnM = SceneManager::GetInstance();

	// シーン遷移
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
	DrawString(0,0,"タイトルシーン",RGB(255,255,255));

}

void TitleScene::Release(void)
{
}

