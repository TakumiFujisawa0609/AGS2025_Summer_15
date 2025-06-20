#include "TutorialStage.h"
#include<sstream>
#include<fstream>
#include<iostream>
#include<vector>
#include<string>

#include"../../../Utility/AsoUtility.h"
#include"../../../Application.h"
#include"../../../Manager/Camera.h"

TutorialStage::TutorialStage()
{

}

TutorialStage::~TutorialStage()
{
}

void TutorialStage::Draw(void)
{
	DrawBox(0, 0, STAGE_CHIP_SIZE * mapData_.at(0).size(), STAGE_CHIP_SIZE * mapData_.size(), RGB(255, 100, 100),true);

	for (int i = 0; i < HAIKEI_MAX; i++) {
		int dx = HAIKEI_SIZE_X * i - Camera::GetInstance().GetPos().x;
		int dy = (Application::MAIN_SCREEN_SIZE_Y - Application::SCREEN_SIZE_Y) / 2 - Camera::GetInstance().GetPos().y;
		DrawGraph(dx, dy, haikei_, true);
	}
	StageBase::Draw();
}

void TutorialStage::Load(void)
{
	int load[STAGE_CHIP_ALL];

	int err = LoadDivGraph("Data/Image/Stage/ForestTile.png", STAGE_CHIP_ALL,
		STAGE_CHIP_X, STAGE_CHIP_Y,
		STAGE_CHIP_SIZE, STAGE_CHIP_SIZE, load);
	if (err == -1) {
		return;
	}

	chipId_.insert(chipId_.end(), load, load + STAGE_CHIP_ALL);

	haikei_ = LoadGraph("Data/Image/Stage/BackGround.png");

	if (!LoadMapData()) {
		return;
	}
}

bool TutorialStage::LoadMapData(void)
{
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

			mapData_[yy][xx] = chipNo;
		}
		yy++;
	}

	return true;
}
