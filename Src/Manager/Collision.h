#pragma once
#include"../Utility/AsoUtility.h"
#include"../Object/Stage/Stage.h"


class Collision
{
private:
	Collision();
	~Collision();
public:
	static void CreateInstance(void) { if (instance == nullptr)instance = new Collision(); instance->Init(); }
	static Collision& GetInstance(void) { return *instance; }
	static void DeleteInstance(void) { if (instance != nullptr)delete instance; instance = nullptr; }

	void Init();
	void SetStage(int map,int y,int x){ mapData_[y][x] = map; }


	enum DIR {
		UP,
		DOWN,
		LEFT,
		RIGHT,

		MAX
	};
	//ìnÇ≥ÇÍÇΩç¿ïWÇÃè∞ÇÃçÇÇ≥
 	const float GetStageFoot(const Vector2F pos,const Vector2F size ,const DIR dir) const;

private:
	static Collision* instance;

	int mapData_[Stage::STAGE_NUM_Y][Stage::STAGE_NUM_X];
};

