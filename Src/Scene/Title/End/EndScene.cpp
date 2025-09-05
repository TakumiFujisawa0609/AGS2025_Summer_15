#include"EndScene.h"

#include<DxLib.h>

#include"../../../Utility/AsoUtility.h"

#include"../../../Application.h"
#include"../../../Manager/SceneManager.h"
#include"../../../Manager/KeyManager.h"
#include"../../../Manager/SoundManager.h"

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
}

void EndScene::Load(void)
{
	Img_[(int)SELECT::YES] = AsoUtility::LoadImg("Data/Image/Title/End/Yes.png");
	Img_[(int)SELECT::NO] = AsoUtility::LoadImg("Data/Image/Title/End/No.png");
}

void EndScene::Init(void) 
{
	nowSelect_ = SELECT::YES;

	SoundManager::GetIns().AllStop();
}

void EndScene::Update(void) 
{
	switch (nowSelect_)
	{
	case EndScene::SELECT::YES:
		if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_DOWN).down) { nowSelect_ = EndScene::SELECT::NO; }
		if (KEY::GetIns().GetInfo(KEY_TYPE::ENTER).down) {
			SoundManager::GetIns().PauseInfoDelete();
			Application::GetInstance().GameEnd();
			return;
		}
		break;
	case EndScene::SELECT::NO:
		if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_UP).down) { nowSelect_ = EndScene::SELECT::YES; }
		if (KEY::GetIns().GetInfo(KEY_TYPE::ENTER).down) {
			SoundManager::GetIns().PausePlay();
			SceneManager::GetIns().PopScene();
			return;
		}
		break;
	}
}

void EndScene::Draw(void) 
{
	Vector2 screen = { Application::SCREEN_SIZE_X / 2,Application::SCREEN_SIZE_Y / 2 };

	DrawRotaGraph(screen.x, screen.y, 1, 0, Img_[(int)nowSelect_], true);
}

void EndScene::Release(void) 
{
	for (auto& id : Img_) { DeleteGraph(id); }
}