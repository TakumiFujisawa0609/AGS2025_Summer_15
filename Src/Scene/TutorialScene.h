#pragma once
#include<memory>
#include "SceneBase.h"

class Player;
class Stage;
class EnemyManager;
class BossTutorial;
class BambooManager;

class TutorialScene :
    public SceneBase
{
public:
	// コンストラクタ
	TutorialScene(void);

	// デストラクタ
	~TutorialScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;



private:
	//プレイヤークラスのインスタンス
	Player* player_;
	Stage* stage_;
	EnemyManager* enemy_ ;
	BossTutorial* boss_;
	BambooManager* bamboo_;

	void Scroll(void);

	void ObjCollision(void);

	void PlayerToBamboo(void);

	void PlayerToEnemyBamboo(void);
	void PlayerAttackToEnemyBamboo(void);

	void PlayerToBoss(void);
	void PlayerToBossAttack(void);
	void PlayerAttackToBoss(void);

	float x;

};

