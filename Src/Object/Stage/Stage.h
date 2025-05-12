#pragma once
#include<DxLib.h>
#include"../../Utility/AsoUtility.h"

class Stage
{
public:
	
	static constexpr int STAGE_CHIP_ALL = 2;		//ステージのマップチップの数
	static constexpr int STAGE_CHIP_SIZE = 32;		//ステージのマップチップのサイズ
	static constexpr int STAGE_CHIP_WIDTH = 2;		//ステージのマップチップの幅
	static constexpr int STAGE_CHIP_HEIGHT = 1;		//ステージのマップチップの高さ

	static constexpr int STAGE_NUM_X = 128;
	static constexpr int STAGE_NUM_Y = 24;
	static constexpr int STAGE_NUM_MAX = STAGE_NUM_X * STAGE_NUM_Y;

	enum TILE {
		WHITE,
		BLACK,
	};

	Stage();
	~Stage();
	bool Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	bool Release(void);


	float Getfoot(Vector2F pos);

private:

	bool LoadMapData(void);


	int stageArrayId[STAGE_CHIP_ALL] ;	//ステージのマップチップのハンドル番号
	int mapDataArray[STAGE_NUM_Y][STAGE_NUM_X];
};
