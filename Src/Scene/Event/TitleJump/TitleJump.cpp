#include"TitleJump.h"

#include"../../../Utility/AsoUtility.h"
#include"../../../Manager/KeyManager.h"
#include"../../../Manager/SoundManager.h"

#include"../../../Application.h"
#include"../../../Manager/SceneManager.h"

TitleJump::TitleJump():
	nowSelect_(SELECT::NO),
	img_()
{
}

TitleJump::~TitleJump()
{
}

void TitleJump::Load(void)
{
	img_[(int)SELECT::YES] = AsoUtility::LoadImg("Data/Image/TitleJump/Yes.png");
	img_[(int)SELECT::NO] = AsoUtility::LoadImg("Data/Image/TitleJump/No.png");
}

void TitleJump::Init(void)
{
	nowSelect_ = SELECT::NO;

	SoundManager::GetIns().AllStop();
}

void TitleJump::Update(void)
{
	switch (nowSelect_)
	{
	case SELECT::YES:
		if (KEY::GetIns().GetInfo(KEY_TYPE::ENTER).down) {
			Smng::GetIns().PauseInfoDelete();
			Smng::GetIns().Play(SOUND::SE_SYSTEM_BUTTON, true);
			SceneManager::GetIns().JumpScene(SCENE_ID::TITLE);
			return;
		}
		if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_DOWN).down) { nowSelect_ = SELECT::NO; Smng::GetIns().Play(SOUND::SE_SYSTEM_SELECT, true); }
		break;
	case SELECT::NO:
		if (KEY::GetIns().GetInfo(KEY_TYPE::ENTER).down) {
			SoundManager::GetIns().PausePlay();
			Smng::GetIns().Play(SOUND::SE_SYSTEM_BUTTON, true);
			SceneManager::GetIns().PopScene();
		}
		if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_UP).down) { nowSelect_ = SELECT::YES; Smng::GetIns().Play(SOUND::SE_SYSTEM_SELECT, true); }
		break;
	}
}

void TitleJump::Draw(void)
{
	int xx = Application::SCREEN_SIZE_X;
	int yy = Application::SCREEN_SIZE_Y;
	int x = xx / 2;
	int y = yy / 2;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, 0, xx, yy, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawRotaGraph(x, y, 1, 0, img_[(int)nowSelect_], true);
}

void TitleJump::Release(void)
{
	for (auto& id : img_) { DeleteGraph(id); }
}