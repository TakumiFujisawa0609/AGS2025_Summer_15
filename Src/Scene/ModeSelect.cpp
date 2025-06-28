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
	auto& scnM = SceneManager::GetInstance();
	auto& key = InputManager::GetInstance();

	if (key.IsTrgDown(KEY_INPUT_1))scnM.ChangeScene(SceneManager::SCENE_ID::TUTORIAL);
	if (key.IsTrgDown(KEY_INPUT_2))scnM.ChangeScene(SceneManager::SCENE_ID::BOSSSELECT);

}

void ModeSelect::Draw()
{
	using a = Application;

	DrawBox(0, 0, a::SCREEN_SIZE_X, a::SCREEN_SIZE_Y, RGB(255, 0, 0), true);

}

void ModeSelect::Release()
{

}