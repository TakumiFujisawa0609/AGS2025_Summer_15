#pragma once

#include"BossStageBase.h"

class Stage1 :public BossStageBase
{
public:
	static constexpr int STAGE_CHIP_X = 10;		//ステージのマップチップの幅
	static constexpr int STAGE_CHIP_Y = 6;		//ステージのマップチップの高さ
	static constexpr int STAGE_CHIP_ALL = STAGE_CHIP_X * STAGE_CHIP_Y;		//ステージのマップチップの数

	Stage1();
	~Stage1();



private:
	void Load(void)override;
	bool LoadMapData(void)override;
};

