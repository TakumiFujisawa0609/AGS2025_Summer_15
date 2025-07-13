#include"BossSelect.h"

#include<DxLib.h>

#include"../Manager/SceneManager.h"
#include"../Manager/Collision.h"
#include"../Manager/Camera.h"

#include"../Object/Stage/SelectStage/SelectStage.h"
#include"../Object/Player/Player.h"

BossSelect::BossSelect()
{
}

BossSelect::~BossSelect()
{
}

void BossSelect::Init()
{
	stage_ = new SelectStage();
	stage_->Init();

	player_ = new Player();
	player_->Init();
	player_->BpOptain();

	Collision::CreateInstance();
	auto& colli = Collision::GetInstance();
	colli.Init();
	colli.SetStage(stage_->GetMapData());

	auto& camera = Camera::GetInstance();
	camera.Init();
	camera.SetMapNum(stage_->GetMapNum());

	haveBcou_ = 0;
}

void BossSelect::Update()
{
	using M = SceneManager;
	auto& m = M::GetInstance();

	if (CheckHitKey(KEY_INPUT_0) == 1) {
		m.SetBossKinds(M::BOSS_KINDS::TUTORIAL);
		m.ChangeScene(M::SCENE_ID::BATTLEDONE);
	}

	if (CheckHitKey(KEY_INPUT_1) == 1) {
		m.SetBossKinds(M::BOSS_KINDS::NOKOPY);
		m.ChangeScene(M::SCENE_ID::BATTLEDONE);
	}
	if (CheckHitKey(KEY_INPUT_2) == 1) {
		m.SetBossKinds(M::BOSS_KINDS::RUNBOO);
		m.ChangeScene(M::SCENE_ID::BATTLEDONE);
	}
	if (CheckHitKey(KEY_INPUT_3) == 1) {
		m.SetBossKinds(M::BOSS_KINDS::BAMMOON);
		m.ChangeScene(M::SCENE_ID::BATTLEDONE);
	}

	player_->Update();
	if (player_->GetHaveB()) { haveBcou_ = 0; }
	else { if (++haveBcou_ > 200) { player_->BpOptain(); haveBcou_ = 0; } }

	this->Collision();
}

void BossSelect::Draw()
{
	using a = Application;

	stage_->BackDraw();

	player_->Draw();

	stage_->Draw();
	int fontsize = 32;
	SetFontSize(32);
	DrawString(0, 0, "‚P‚Åƒ{ƒX‚P", RGB(255, 255, 255));
	DrawString(0, fontsize, "‚Q‚Åƒ{ƒX‚Q", RGB(255, 255, 255));
	DrawString(0, fontsize * 2, "‚R‚Åƒoƒ“ƒ€[ƒ“", RGB(255, 255, 255));
	SetFontSize(16);
}

void BossSelect::Release()
{
	Collision::DeleteInstance();

	player_->Release();
	delete player_;

	stage_->Release();
	delete stage_;

}


void BossSelect::Collision()
{

}