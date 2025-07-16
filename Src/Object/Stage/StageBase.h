#pragma once

#include<vector>
#include<map>

#include"../../Common/Vector2.h"

class StageBase
{
public:
	static constexpr int STAGE_CHIP_SIZE = 32;		//ステージのマップチップのサイズ

	StageBase();
	~StageBase();

	void Init(void);
	virtual void BackDraw(void);
	virtual void Draw(void);
	void Release(void);

	std::map<int, std::map<int, int>> GetMapData(void) { return mapData_; }

	Vector2 GetMapNum(void);

protected:
	virtual void Load(void) = 0;
	virtual bool LoadMapData(void) = 0;
	virtual void AddRelease(void) = 0;

	int haikei_;

	std::vector<int> chipId_;
	std::map<int,std::map<int,int>> mapData_;
};

