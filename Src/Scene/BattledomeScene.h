#pragma once

#include"SceneBase.h"

class StageBase;
class BossBase;
class Player;
class BambooManager;

class BattledomeScene : public SceneBase
{
public:
	BattledomeScene();
	~BattledomeScene();

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	
private:
	Player* player_;
	BambooManager* bamboo_;
	StageBase* stage_;
	BossBase* boss_;


	void Scroll(void);
};


