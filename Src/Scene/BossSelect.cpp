#include"BossSelect.h"

#include<DxLib.h>
#include<cmath>

#include"../Manager/SceneManager.h"
#include"../Manager/Collision.h"
#include"../Manager/Camera.h"
#include"../Utility/AsoUtility.h"
#include"../Manager/Score/Score.h"

#include"../Manager/Decoration/BlastEffect/BlastEffectManager.h"

#include"../Object/Stage/SelectStage/SelectStage.h"
#include"../Object/Player/SelectPlayer/SelectPlayer.h"

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

	player_ = new SelectPlayer();
	player_->Init();

	blast_ = new BlastEffectManager();
	blast_->Init();

	Collision::CreateInstance();
	auto& colli = Collision::GetInstance();
	colli.Init();
	colli.SetStage(stage_->GetMapData());

	auto& camera = Camera::GetInstance();
	camera.Init();
	camera.SetMapNum(stage_->GetMapNum());

	haveBcou_ = 0;

	scoreImage_ = LoadGraph("Data/Image/Score.png");

	tutorialImg_ = LoadGraph("Data/Image/Stage/Select/SelectTutorial.png");
	tutorialPos_ = { 1200.0f,250.0f };
	nokopyImg_ = LoadGraph("Data/Image/Stage/Select/SelectNokopy.png");
	nokopyPos_ = { 1050.0f,550.0f };
	runbooImg_ = LoadGraph("Data/Image/Stage/Select/SelectRunboo.png");
	runbooPos_ = { 50.0f,300.0f };
	bammoonImg_ = LoadGraph("Data/Image/Stage/Select/SelectBammoon.png");
	bammoonPos_ = { 650,120.0f };

	nowSelectImage_ = LoadGraph("Data/Image/Stage/Select/NowSelect.png");
}

void BossSelect::Update()
{
	player_->Update();

	using B = SelectPlayer::B_KINDS;
	B b = player_->NowSelect();
	Vector2F target = {};
	switch (b)
	{
	case SelectPlayer::RUNBOO:
		player_->SetVec(runbooPos_);
		nowSelectPos_ = runbooPos_;
		break;
	case SelectPlayer::BAMMOON:
		player_->SetVec(bammoonPos_);
		nowSelectPos_ = bammoonPos_;
		break;
	case SelectPlayer::TUTORIAL:
		player_->SetVec(tutorialPos_);
		nowSelectPos_ = tutorialPos_;
		break;
	case SelectPlayer::NOKOPY:
		player_->SetVec(nokopyPos_);
		nowSelectPos_ = nokopyPos_;
		break;
	}
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
	using BKINDS = SceneManager::BOSS_KINDS;

	stage_->BackDraw();

	using B = SelectPlayer::B_KINDS;
	B b = player_->NowSelect();

	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2 + 30, 1, 0, scoreImage_, true);

	auto& score = Score::GetIns();
	std::vector<float> s = {};
	switch (b)
	{
	case SelectPlayer::RUNBOO:
		s = score.GetRanking(BKINDS::RUNBOO);
		break;
	case SelectPlayer::BAMMOON:
		s = score.GetRanking(BKINDS::BAMMOON);
		break;
	case SelectPlayer::TUTORIAL:
		s = score.GetRanking(BKINDS::TUTORIAL);
		break;
	case SelectPlayer::NOKOPY:
		s = score.GetRanking(BKINDS::NOKOPY);
		break;
	}
	int fontSize = 32;
	SetFontSize(fontSize);
	for (int i = 0; i < s.size(); i++) {
		DrawFormatString(710 , 340 + (i * (fontSize + 15)), RGB(255, 255, 255), (s[i] == -1) ? "---":"%.2fs", s[i]);
	}
	SetFontSize(16);


	DrawRotaGraphF(tutorialPos_.x, tutorialPos_.y, (b == B::TUTORIAL) ? 1.2 : 1, 0, tutorialImg_, true);
	DrawRotaGraphF(nokopyPos_.x, nokopyPos_.y, (b == B::NOKOPY) ? 1.2 : 1, AsoUtility::Deg2RadF(-45.0f), nokopyImg_, true);
	DrawRotaGraphF(runbooPos_.x, runbooPos_.y, (b == B::RUNBOO) ? 1.2 : 1, 0, runbooImg_, true);
	DrawRotaGraphF(bammoonPos_.x, bammoonPos_.y, (b == B::BAMMOON) ? 1.2 : 1, 0, bammoonImg_, true);


	DrawRotaGraphF(nowSelectPos_.x, nowSelectPos_.y-20 + (sin(nowSelectCount_) * 10), 1, 0, nowSelectImage_, true);

	player_->Draw();

	blast_->Draw();

	stage_->Draw();
}

void BossSelect::Release()
{
	DeleteGraph(bammoonImg_);
	DeleteGraph(runbooImg_);
	DeleteGraph(nokopyImg_);
	DeleteGraph(tutorialImg_);

	Collision::DeleteInstance();

	blast_->Release();
	delete blast_;

	player_->Release();
	delete player_;

	stage_->Release();
	delete stage_;

}


void BossSelect::Collision()
{
	using M = SceneManager;
	auto& sMng = M::GetInstance();

	Vector2F b = player_->GetBamboo().pos_;

	Vector2F vec = {};
	float dis = 0.0f;

	vec = runbooPos_ - b;
	dis = sqrtf(vec.x * vec.x + vec.y * vec.y);

	if (dis < SelectPlayer::BAMBOO_SPEED) {
		blast_->On(b);
		sMng.SetBossKinds(M::BOSS_KINDS::RUNBOO);
		sMng.ChangeScene(M::SCENE_ID::BATTLEDONE);
	}

	vec = bammoonPos_ - b;
	dis = sqrtf(vec.x * vec.x + vec.y * vec.y);

	if (dis < SelectPlayer::BAMBOO_SPEED) {
		blast_->On(b);
		sMng.SetBossKinds(M::BOSS_KINDS::BAMMOON);
		sMng.ChangeScene(M::SCENE_ID::BATTLEDONE);
	}

	vec = tutorialPos_ - b;
	dis = sqrtf(vec.x * vec.x + vec.y * vec.y);

	if (dis < SelectPlayer::BAMBOO_SPEED) {
		blast_->On(b);
		sMng.SetBossKinds(M::BOSS_KINDS::TUTORIAL);
		sMng.ChangeScene(M::SCENE_ID::BATTLEDONE);
	}

	vec = nokopyPos_ - b;
	dis = sqrtf(vec.x * vec.x + vec.y * vec.y);

	if (dis < SelectPlayer::BAMBOO_SPEED) {
		blast_->On(b);
		sMng.SetBossKinds(M::BOSS_KINDS::NOKOPY);
		sMng.ChangeScene(M::SCENE_ID::BATTLEDONE);
	}
}