#pragma once
#include<DxLib.h>
#include"../../../Utility/AsoUtility.h"

#include"../StageBase.h"

class TutorialStage : public StageBase
{
public:

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

	void Draw(void)override;

private:
	void Load(void)override;
	bool LoadMapData(void)override;
};
