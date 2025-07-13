#include"BossSelect.h"

#include<DxLib.h>

#include"../Manager/SceneManager.h"

BossSelect::BossSelect()
{
}

BossSelect::~BossSelect()
{
}

void BossSelect::Init()
{

}

void BossSelect::Update()
{
	using M = SceneManager;
	auto& m = M::GetInstance();

	if (CheckHitKey(KEY_INPUT_0) == 1) {
		m.ChangeScene(M::SCENE_ID::TUTORIAL);
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
}

void BossSelect::Draw()
{
	using a = Application;

	DrawBox(0, 0, a::SCREEN_SIZE_X, a::SCREEN_SIZE_Y, RGB(0, 255, 0), true);

	int fontsize = 32;
	SetFontSize(32);
	DrawString(0, 0, "ÇPÇ≈É{ÉXÇP", RGB(255, 255, 255));
	DrawString(0, fontsize, "ÇQÇ≈É{ÉXÇQ", RGB(255, 255, 255));
	DrawString(0, fontsize * 2, "ÇRÇ≈ÉoÉìÉÄÅ[Éì", RGB(255, 255, 255));
	SetFontSize(16);
}

void BossSelect::Release()
{

}