#include"BossSelect.h"

#include<DxLib.h>
#include<cmath>

#include"../Manager/Collision.h"
#include"../Manager/Camera.h"
#include"../Utility/AsoUtility.h"
#include"../Manager/Score/Score.h"
#include"../Manager/SoundManager.h"

#include"../Manager/Decoration/BlastEffect/BlastEffectManager.h"

#include"../Object/Stage/SelectStage/SelectStage.h"
#include"../Object/Player/SelectPlayer/SelectPlayer.h"

BossSelect::BossSelect()
{
}

BossSelect::~BossSelect()
{
}

using BOSS = SceneManager::BOSS_KINDS;

void BossSelect::Init()
{
	this->Release();

	stage_ = new SelectStage();
	stage_->Init();

	player_ = new SelectPlayer();
	player_->Init();

	blast_ = new BlastEffectManager();
	blast_->Init();

	Collision::CreateInstance();
	auto& colli = Collision::GetInstance();
	colli.SetStage(stage_->GetMapData());

	auto& camera = Camera::GetInstance();
	camera.Init();
	camera.SetMapNum(stage_->GetMapNum());

	scoreImage_ = LoadGraph("Data/Image/Score.png");

	nowSelectImage_ = LoadGraph("Data/Image/Stage/Select/NowSelect.png");

	comingSoon_ = LoadGraph("Data/Image/ComingSoon.png");

	bossInfo_[(int)BOSS::TUTORIAL].type_ = BOSS::TUTORIAL;
	bossInfo_[(int)BOSS::TUTORIAL].image_ = LoadGraph("Data/Image/Stage/Select/SelectTutorial.png");
	bossInfo_[(int)BOSS::TUTORIAL].thum_ = LoadGraph("Data/Image/Stage/Select/ThumTutorial.png");
	bossInfo_[(int)BOSS::TUTORIAL].pos_ = { 1200.0f,250.0f };

	bossInfo_[(int)BOSS::NOKOPY].type_ = BOSS::NOKOPY;
	bossInfo_[(int)BOSS::NOKOPY].image_ = LoadGraph("Data/Image/Stage/Select/SelectNokopy.png");
	bossInfo_[(int)BOSS::NOKOPY].thum_ = LoadGraph("Data/Image/Stage/Select/ThumNokopy.png");
	bossInfo_[(int)BOSS::NOKOPY].pos_ = { 1050.0f,550.0f };

	bossInfo_[(int)BOSS::RUNBOO].type_ = BOSS::RUNBOO;
	bossInfo_[(int)BOSS::RUNBOO].image_ = LoadGraph("Data/Image/Stage/Select/SelectRunboo.png");
	bossInfo_[(int)BOSS::RUNBOO].thum_ = LoadGraph("Data/Image/Stage/Select/ThumRunboo.png");
	bossInfo_[(int)BOSS::RUNBOO].pos_ = { 50.0f,300.0f };

	bossInfo_[(int)BOSS::BAMMOON].type_ = BOSS::BAMMOON;
	bossInfo_[(int)BOSS::BAMMOON].image_ = LoadGraph("Data/Image/Stage/Select/SelectBammoon.png");
	bossInfo_[(int)BOSS::BAMMOON].thum_ = LoadGraph("Data/Image/Stage/Select/ThumBammoon.png");
	bossInfo_[(int)BOSS::BAMMOON].pos_ = { 650,120.0f };

	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Load(S::SOUND::BPHIT);
	sound.Load(S::SOUND::BGM1);
	sound.Play(S::SOUND::BGM1, false, 100, true, false);
}

void BossSelect::Update()
{
	player_->Update();
	player_->SetVec(bossInfo_[(int)player_->NowSelect()].pos_);

	this->Collision();

	blast_->Update();

	static int inter = 0;
	if (++inter > 4) {
		inter = 0;
		if (++nowSelectCount_ > 100) { nowSelectCount_ = 0; }
	}
}

void BossSelect::Draw()
{
	using a = Application;

	stage_->BackDraw();

	DrawRotaGraph(a::SCREEN_SIZE_X / 2, a::SCREEN_SIZE_Y / 2 + 30, 1, 0, scoreImage_, true);

	BOSS now = player_->NowSelect();

	std::vector<float> s = Score::GetIns().GetRanking(now);

	int fontSize = 32;
	SetFontSize(fontSize);
	for (int i = 0; i < s.size(); i++) {
		DrawFormatString(710 , 340 + (i * (fontSize + 15)), RGB(255, 255, 255), (s[i] == -1) ? "---":"%.2fs", s[i]);
	}
	SetFontSize(16);

	for (auto& boss : bossInfo_) {
		DrawRotaGraph(boss.pos_.x, boss.pos_.y,
			(now == boss.type_) ? 1.2 : 1,
			(boss.type_ == BOSS::NOKOPY) ? AsoUtility::Deg2RadF(-45.0f) : 0,
			boss.image_, true);

		if (now == boss.type_) {
			DrawRotaGraph(515, 420, 1, 0, boss.thum_, true);
			if (boss.type_ == BOSS::RUNBOO) {
				DrawRotaGraph(a::SCREEN_SIZE_X / 2, a::SCREEN_SIZE_Y / 2 + 30, 1, AsoUtility::Deg2RadF(-15.0f), comingSoon_, true);
			}
		}
	}

	nowSelectPos_ = bossInfo_[(int)now].pos_;
	DrawRotaGraphF(nowSelectPos_.x, nowSelectPos_.y-20 + (sin(nowSelectCount_) * 10), 1, 0, nowSelectImage_, true);

	player_->Draw();

	blast_->Draw();

	stage_->Draw();
}

void BossSelect::Release()
{
	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Delete(S::SOUND::BGM1);
	sound.Delete (S::SOUND::BPHIT);

	// ‰æ‘œ‚Ì‰ð•ú
	DeleteGraph(scoreImage_);
	DeleteGraph(nowSelectImage_);
	DeleteGraph(comingSoon_);

	for (auto& boss : bossInfo_) {
		DeleteGraph(boss.image_);
		DeleteGraph(boss.thum_);
	}

	Collision::DeleteInstance();

	if (blast_) {
		blast_->Release();
		delete blast_;
		blast_ = nullptr;
	}
	if (player_) {
		player_->Release();
		delete player_;
		player_ = nullptr;
	}
	if (stage_) {
		stage_->Release();
		delete stage_;
		stage_ = nullptr;
	}
}


void BossSelect::Collision()
{
	using M = SceneManager;
	auto& sMng = M::GetInstance();

	Vector2F b = player_->GetBamboo().pos_;

	Vector2F vec = {};
	float dis = 0.0f;

	for (auto& boss : bossInfo_) {
		vec = boss.pos_ - b;
		dis = sqrtf(vec.x * vec.x + vec.y * vec.y);

		if (dis < SelectPlayer::BAMBOO_SPEED) {
			SoundManager::GetIns().Play(SoundManager::SOUND::BPHIT, true, 200);
			blast_->On(b);
			sMng.SetBossKinds(boss.type_);
			sMng.ChangeScene(M::SCENE_ID::BATTLEDONE);
		}
	}
}