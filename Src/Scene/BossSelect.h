#pragma once

#include"SceneBase.h"

class SelectStage;
class SelectPlayer;
class BlastEffectManager;

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
	SelectPlayer* player_;

	BlastEffectManager* blast_;

	int haveBcou_;

	int tutorialImg_;
	Vector2F tutorialPos_;
	int nokopyImg_;
	Vector2F nokopyPos_;
	int runbooImg_;
	Vector2F runbooPos_;
	int bammoonImg_;
	Vector2F bammoonPos_;



	void Collision(void);
};

