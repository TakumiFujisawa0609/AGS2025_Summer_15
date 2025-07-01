#include"ModeSelect.h"

#include<DxLib.h>

#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Application.h"

ModeSelect::ModeSelect()
{
}

ModeSelect::~ModeSelect()
{
}


void ModeSelect::Init()
{

}

void ModeSelect::Update()
{
	using M = SceneManager;
	auto& scnM = M::GetInstance();
	auto& key = InputManager::GetInstance();

	if (key.IsTrgDown(KEY_INPUT_1))scnM.ChangeScene(M::SCENE_ID::TUTORIAL);
	if (key.IsTrgDown(KEY_INPUT_2))scnM.ChangeScene(M::SCENE_ID::BOSSSELECT);

}

void ModeSelect::Draw()
{
	using a = Application;

	DrawBox(0, 0, a::SCREEN_SIZE_X, a::SCREEN_SIZE_Y, RGB(255, 0, 0), true);

	int fontsize = 32;
	SetFontSize(32);
	DrawString(0, 0, "１でチュートリアル", RGB(255, 255, 255));
	DrawString(0, fontsize, "２でボスセレクト", RGB(255, 255, 255));
	SetFontSize(16);
}

void ModeSelect::Release()
{

}