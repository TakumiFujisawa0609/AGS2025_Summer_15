#include <memory> 
#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include "TitleScene.h"
#include"../Manager/UiManager.h"
#include"../Object/Ui/UiTitle.h"
TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}


void TitleScene::Init(void)
{
   UiManager::GetInstance()->AddUi(std::make_unique<UiTitle>()); 
   UiManager::GetInstance()->Init();
}

void TitleScene::Update(void)
{
	auto& scnM = SceneManager::GetInstance();
	UiManager::GetInstance()->Update();
	// ƒV[ƒ“‘JˆÚ
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		scnM.SetController(SceneManager::CNTL::KEY);
		scnM.ChangeScene(SceneManager::SCENE_ID::TUTORIAL);
	}

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	{
		scnM.SetController(SceneManager::CNTL::PAD);
		scnM.ChangeScene(SceneManager::SCENE_ID::TUTORIAL);
	}
}

void TitleScene::Draw(void)
{
	UiManager::GetInstance()->Draw();

}

void TitleScene::Release(void)
{
	UiManager::GetInstance()->Release();
}

