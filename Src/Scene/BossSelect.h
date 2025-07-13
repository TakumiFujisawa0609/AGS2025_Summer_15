#pragma once

#include"SceneBase.h"

class SelectStage;
class Player;

class BossSelect : public SceneBase
{
public:
	BossSelect();
	~BossSelect();

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;


private:
	SelectStage* stage_;
	Player* player_;

	int haveBcou_;

	int tutorialImg_;
	int nokopyImg_;
	int runbooImg_;
	int bammoonImg_;



	void Collision(void);
};

