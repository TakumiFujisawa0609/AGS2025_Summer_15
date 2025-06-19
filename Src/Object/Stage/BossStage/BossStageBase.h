#pragma once

#include<vector>
#include<map>

class BossStageBase
{
public:
	static constexpr int STAGE_CHIP_SIZE = 32;		//ステージのマップチップのサイズ

	BossStageBase();
	~BossStageBase();

	void Init(void);
	void Draw(void);
	void Release(void);

protected:
	virtual void Load(void) = 0;
	virtual bool LoadMapData(void) = 0;

	int haikei_;

	std::vector<int> chipId_;
	std::map<int,std::map<int,int>> mapData_;
};

