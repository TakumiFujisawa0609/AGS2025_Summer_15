#include"PlayScene.h"

#include"../../../Utility/AsoUtility.h"

#include"../../../Manager/KeyManager.h"
#include"../../../Manager/SoundManager.h"

#include"../../../Manager/SceneManager.h"

PlayScene::PlayScene() :
	nowSelect_(SELECT::BATTLE),
	prevSelect_(nowSelect_)
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Load(void)
{
	boardImg_ = AsoUtility::LoadImg("Data/Image/Title/Play/Board.png");

	selectImg_[(int)SELECT::BATTLE] = AsoUtility::LoadImg("Data/Image/Title/Play/Battle.png");
	selectImg_[(int)SELECT::TUTORIAL] = AsoUtility::LoadImg("Data/Image/Title/Play/Tutorial.png");
	selectImg_[(int)SELECT::EXIT] = AsoUtility::LoadImg("Data/Image/Title/Play/Exit.png");

	nowSelectFrameImg_ = AsoUtility::LoadImg("Data/Image/Title/Play/SelectFrame.png");
}

void PlayScene::Init(void) 
{
	nowSelect_ = SELECT::BATTLE;
	prevSelect_ = nowSelect_;

	SoundManager::GetIns().AllStop();
}

void PlayScene::Update(void) 
{
	bool select = false;
	
	switch (nowSelect_)
	{
	case SELECT::BATTLE:
		if (KEY::GetIns().GetInfo(KEY_TYPE::ENTER).down) {
			SoundManager::GetIns().PauseInfoDelete();
			Smng::GetIns().Play(SOUND::SE_SYSTEM_BUTTON, true);
			SceneManager::GetIns().JumpScene(SCENE_ID::BOSSSELECT);
			return;
		}
		if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_RIGHT).down) { nowSelect_ = SELECT::TUTORIAL; select = true; }
		if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_DOWN).down) { prevSelect_ = nowSelect_; nowSelect_ = SELECT::EXIT; select = true; }
		break;
	case SELECT::TUTORIAL:
		if (KEY::GetIns().GetInfo(KEY_TYPE::ENTER).down) {
			SoundManager::GetIns().PauseInfoDelete();
			Smng::GetIns().Play(SOUND::SE_SYSTEM_BUTTON, true);
			SceneManager::GetIns().JumpScene(SCENE_ID::TUTORIAL);
			return;
		}
		if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_LEFT).down) { nowSelect_ = SELECT::BATTLE; select = true; }
		if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_DOWN).down) { prevSelect_ = nowSelect_; nowSelect_ = SELECT::EXIT; select = true; }
		break;
	case SELECT::EXIT:
		if (KEY::GetIns().GetInfo(KEY_TYPE::ENTER).down) {
			SoundManager::GetIns().PausePlay();
			Smng::GetIns().Play(SOUND::SE_SYSTEM_BUTTON, true);
			SceneManager::GetIns().PopScene();
			return;
		}

		if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_RIGHT).down) { nowSelect_ = SELECT::TUTORIAL; select = true; }
		if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_LEFT).down) { nowSelect_ = SELECT::BATTLE; select = true; }
		if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_UP).down) { nowSelect_ = prevSelect_; select = true; }
		break;
	}

	if (select) { Smng::GetIns().Play(SOUND::SE_SYSTEM_SELECT, true); }

	if (KEY::GetIns().GetInfo(KEY_TYPE::PAUSE).down) {
		SoundManager::GetIns().PausePlay();
		Smng::GetIns().Play(SOUND::SE_SYSTEM_BUTTON, true);
		SceneManager::GetIns().PopScene();
		return;
	}
}

void PlayScene::Draw(void) 
{
	int xx = Application::SCREEN_SIZE_X;
	int yy = Application::SCREEN_SIZE_Y;
	int x = xx / 2;
	int y = yy / 2;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, 0, xx, yy, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawRotaGraph(x, y, 1, 0, boardImg_, true);

	for (int i = 0; i < (int)SELECT::MAX; i++) {
		DrawRotaGraph(SELECT_POS[i].x, SELECT_POS[i].y, 1, 0, selectImg_[i], true);
	}
	DrawRotaGraph(SELECT_POS[(int)nowSelect_].x, SELECT_POS[(int)nowSelect_].y, SELECT_DRAW_SCALE[(int)nowSelect_], 0, nowSelectFrameImg_, true);
}

void PlayScene::Release(void) 
{
	DeleteGraph(nowSelectFrameImg_);
	for (auto& id : selectImg_) { DeleteGraph(id); }
	DeleteGraph(boardImg_);
}