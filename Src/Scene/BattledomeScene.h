#pragma once

#include"SceneBase.h"

class StageBase;
class BossBase;
class Player;
class BambooManager;
class Runboo;

class BattledomeScene : public SceneBase
{
public:
	BattledomeScene();
	~BattledomeScene();

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void UnitCollision(void);
	
private:
	Player* player_;
	BambooManager* bamboo_;
	StageBase* stage_;
	BossBase* boss_;
	Runboo* runboo_;


	void Scroll(void);
};


