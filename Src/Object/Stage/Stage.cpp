#include "Stage.h"
#include<sstream>
#include<fstream>
#include<iostream>
#include<vector>
#include<string>

#include"../../Utility/AsoUtility.h"
#include"../../Application.h"
#include"../../Manager/Camera.h"

Stage::Stage()
{

}

Stage::~Stage()
{
}

bool Stage::Load(void)
{
	if (LoadMapData() == false)return false;

	int err = LoadDivGraph("Data/Image/Stage/ForestTile.png", STAGE_CHIP_ALL,
		STAGE_CHIP_X, STAGE_CHIP_Y,
		STAGE_CHIP_SIZE, STAGE_CHIP_SIZE, stageArrayId);
	if (err == -1)return false;

	haikei_ = LoadGraph("Data/Image/Stage/BackGround.png");

	return true;
}

//初期化処理
void Stage::Init()
{
	Camera::CreateInstance();
	Camera& camera = Camera::GetInstance();

	Load();
	LoadMapData();

}

//更新処理
void Stage::Update()
{

}
//描画処理
void Stage::Draw()
{
	DrawBox(0, 0, Application::MAIN_SCREEN_SIZE_X, Application::MAIN_SCREEN_SIZE_Y, GetColor(70, 70, 255), true);
	
	for (int i = 0; i < HAIKEI_MAX; i++) {
		int dx = HAIKEI_SIZE_X * i-Camera::GetInstance().GetPos().x;
		int dy = (Application::MAIN_SCREEN_SIZE_Y - Application::SCREEN_SIZE_Y) / 2 - Camera::GetInstance().GetPos().y;
		DrawGraph(dx, dy, haikei_, true);
	}


	//マップチップ画像を表示
	for (int yy = 0; yy < STAGE_NUM_Y; yy++) {
		for (int xx = 0; xx < STAGE_NUM_X; xx++) {

			int chip = mapDataArray[yy][xx];

			int dx = STAGE_CHIP_SIZE * xx - Camera::GetInstance().GetPos().x;
			int dy = STAGE_CHIP_SIZE * yy - Camera::GetInstance().GetPos().y;

			DrawGraph(dx, dy, stageArrayId[chip], true);
		}
	}

}

//解放処理
bool Stage::Release()
{
	for (int ii = STAGE_CHIP_ALL; ii > 0; ii--)
	{
		if (DeleteGraph(stageArrayId[ii - 1]) == -1)
			return false;
	}

	return true;
}


bool Stage::LoadMapData()
{
	memset((int*)&mapDataArray[0], -1, sizeof(int) * STAGE_NUM_MAX);

	//ファイストリームの取得
	std::ifstream ifs = std::ifstream("Data/CSV/ForestStage.csv");
	if (!ifs)return false;

	std::string line;
	std::vector<std::string> strrSplit;
	int chipNo = 0;
	int yy = 0;

	while (getline(ifs, line))
	{
		strrSplit = AsoUtility::Split(line, ',');
		for (int xx = 0; xx < strrSplit.size(); xx++) {
			chipNo = stoi(strrSplit[xx]);

			mapDataArray[yy][xx] = chipNo;
		}
		yy++;
	}

	return true;
}