#pragma once

#include<vector>
#include<map>

class StageBase
{
public:
	static constexpr int STAGE_CHIP_SIZE = 32;		//ステージのマップチップのサイズ

	StageBase();
	~StageBase();

	void Init(void);
	virtual void Draw(void);
	void Release(void);

	std::map<int, std::map<int, int>> GetMapData(void) { return mapData_; }

protected:
	virtual void Load(void) = 0;
	virtual bool LoadMapData(void) = 0;

	int haikei_;

	std::vector<int> chipId_;
	std::map<int,std::map<int,int>> mapData_;
};

