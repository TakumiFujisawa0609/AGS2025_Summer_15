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

	static constexpr int HAIKEI_SIZE_X = 1827;
	static constexpr int HAIKEI_SIZE_Y = 790;

	enum TILE {
		WHITE,
		BLACK,
	};

	TutorialStage();
	~TutorialStage();

	void BackDraw(void)override;


private:
	void Load(void)override;
	bool LoadMapData(void)override;
	void AddRelease(void)override;

	int backImg_[8];
};
