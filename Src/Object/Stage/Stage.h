#pragma once
#include"DxLib.h"

class Stage
{
public:

	
	static constexpr int STAGE_CHIP_ALL = 2;		//ステージのマップチップの数
	static constexpr int STAGE_CHIP_SIZE = 32;		//ステージのマップチップのサイズ
	static constexpr int STAGE_CHIP_WIDTH = 2;		//ステージのマップチップの幅
	static constexpr int STAGE_CHIP_HEIGHT = 1;		//ステージのマップチップの高さ

	Stage();
	~Stage();
	bool Init();
	void Update();
	void Draw();
	bool Release();

private:
	int stageArrayId[STAGE_CHIP_ALL] ;	//ステージのマップチップのハンドル番号


};
