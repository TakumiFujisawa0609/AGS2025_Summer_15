#pragma once
#include "../StageBase.h"
class NokoPyStage :
    public StageBase
{
public:
	static constexpr int STAGE_CHIP_X = 10;		//ステージのマップチップの幅
	static constexpr int STAGE_CHIP_Y = 6;		//ステージのマップチップの高さ
	static constexpr int STAGE_CHIP_ALL = STAGE_CHIP_X * STAGE_CHIP_Y;		//ステージのマップチップの数

	static constexpr int HAIKEI_SIZE_X = 1827;
	static constexpr int HAIKEI_SIZE_Y = 790;

	NokoPyStage();
	~NokoPyStage();

	void Draw(void)override;


private:
	void Load(void)override;
	bool LoadMapData(void)override;
	void AddRelease(void)override;

	int backImg_[8];
};

