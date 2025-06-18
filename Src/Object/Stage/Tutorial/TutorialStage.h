#pragma once
#include<DxLib.h>
#include"../../../Utility/AsoUtility.h"

class TutorialStage
{
public:

	static constexpr int STAGE_CHIP_SIZE = 32;		//ステージのマップチップのサイズ
	static constexpr int STAGE_CHIP_X = 10;		//ステージのマップチップの幅
	static constexpr int STAGE_CHIP_Y = 6;		//ステージのマップチップの高さ
	static constexpr int STAGE_CHIP_ALL = STAGE_CHIP_X * STAGE_CHIP_Y;		//ステージのマップチップの数

	static constexpr int STAGE_NUM_X = 150;
	static constexpr int STAGE_NUM_Y = 40;
	static constexpr int STAGE_NUM_MAX = STAGE_NUM_X * STAGE_NUM_Y;

	static constexpr int HAIKEI_SIZE_X = 1500;
	static constexpr int HAIKEI_SIZE_Y = 900;
	static constexpr int HAIKEI_MAX = (STAGE_CHIP_SIZE * STAGE_NUM_X) / HAIKEI_SIZE_X + 1;

	enum TILE {
		WHITE,
		BLACK,
	};

	TutorialStage();
	~TutorialStage();
	bool Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	bool Release(void);


	int GetMapData(int y, int x) { return mapDataArray[y][x]; }

private:

	bool LoadMapData(void);
	int haikei_;


	int stageArrayId[STAGE_CHIP_ALL];	//ステージのマップチップのハンドル番号
	int mapDataArray[STAGE_NUM_Y][STAGE_NUM_X];
};
