#include"Stage1.h"

#include<fstream>
#include<string>

#include"../../../Application.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
}
void Stage1::Load(void)
{
	int load[STAGE_CHIP_ALL];

	int err = LoadDivGraph("Data/Image/Stage/ForestTile.png", STAGE_CHIP_ALL,
		STAGE_CHIP_X, STAGE_CHIP_Y,
		STAGE_CHIP_SIZE, STAGE_CHIP_SIZE, load);
	if (err == -1) {
		return;
	}

	chipId_.insert(chipId_.end(), load, load + STAGE_CHIP_ALL);

	if (!LoadMapData()) {
		return;
	}
}

bool Stage1::LoadMapData(void)
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