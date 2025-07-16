#pragma once
#include"../StageBase.h"

class SelectStage :public StageBase
{
public:
	static constexpr int STAGE_CHIP_X = 10;		//ステージのマップチップの幅
	static constexpr int STAGE_CHIP_Y = 6;		//ステージのマップチップの高さ
	static constexpr int STAGE_CHIP_ALL = STAGE_CHIP_X * STAGE_CHIP_Y;		//ステージのマップチップの数

	SelectStage();
	~SelectStage();

	void BackDraw(void)override;


private:
	void Load(void)override;
	bool LoadMapData(void)override;
	void AddRelease(void)override;
};