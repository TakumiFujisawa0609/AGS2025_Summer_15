#pragma once

#include"SceneBase.h"

#include"../Object/Boss/BigBoss/BossBase.h"

class StageBase;
class Player;
class BambooManager;
class BlastEffectManager;

class BossTutorial;
class Nokopy;
class Runboo;
class Bammoon;

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

	BossTutorial* tutorial_;
	Nokopy* nokopy_;
	Runboo* runboo_;
	Bammoon* bammoon_;

	BlastEffectManager* blastMng_;
	//“–‚½‚è”»’è
	void PlayerToBoss(void);
	void PlayerAttackToBoss(void);
	void PlayerToBossAttack(void);
	void PlayerAttackToBossAttack(void);

	void PlayerToBamboo(void);

	void Scroll(void);
};


