#include<DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include"../Manager/SoundManager.h"

#include "GameOverScene.h"

GameOverScene::GameOverScene(void)
{
}

GameOverScene::~GameOverScene(void)
{
}

void GameOverScene::Init(void)
{
	image_ = LoadGraph("Data/Image/GameOver.png");

	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Load(S::SOUND::BGM1);
	sound.Play(S::SOUND::BGM1, false, 100, true);
}

void GameOverScene::Update(void)
{
	// ÉVÅ[ÉìëJà⁄
	int input = GetJoypadInputState(DX_INPUT_PAD1);

	padKey_ = (((input & 0x40) == 0) && ((input & 0x20) == 0)) ? false : true;

	InputManager& ins = InputManager::GetInstance();

	if ((ins.IsTrgDown(KEY_INPUT_SPACE)) || (padKey_))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameOverScene::Draw(void)
{
	DrawGraph(0, 0, image_, true);
}

void GameOverScene::Release(void)
{
	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Delete(S::SOUND::BGM1);

	DeleteGraph(image_);
}
