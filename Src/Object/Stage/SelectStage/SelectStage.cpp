#include "SelectStage.h"

#include<DxLib.h>
#include <string>
#include<fstream>

#include"../../../Utility/AsoUtility.h"

SelectStage::SelectStage()
{
}

SelectStage::~SelectStage()
{
}


void SelectStage::BackDraw() 
{
	DrawGraph(0, 0, haikei_, true);
}

void SelectStage::Load()
{
    int load[STAGE_CHIP_ALL];

    int err = LoadDivGraph("Data/Image/Stage/ForestTile.png", STAGE_CHIP_ALL,
        STAGE_CHIP_X, STAGE_CHIP_Y,
        STAGE_CHIP_SIZE, STAGE_CHIP_SIZE, load);
    if (err == -1) {
        return;
    }
    chipId_.insert(chipId_.end(), load, load + STAGE_CHIP_ALL);

	haikei_ = LoadGraph("Data/Image/Stage/Select/–é‹ó”wŒi.png");
}

bool SelectStage::LoadMapData()
{
    std::ifstream ifs = std::ifstream("Data/CSV/Select.csv");
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

void SelectStage::AddRelease(void)
{
}