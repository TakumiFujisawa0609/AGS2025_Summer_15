#pragma once
#include<memory>
#include <vector> 
#include "SceneBase.h"

class Player;
class Stage;
class EnemyManager;
class BossTutorial;
class EffectManager;
class EffectBase;

class GameScene :
    public SceneBase
{
public:
	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

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

	void Scroll(void);

	void ObjCollision(void);
	void PlayerToBoss(void);
	void PlayerToBossAttack(void);
	void PlayerToEnemyBamboo(void);
	void PlayerAttackToBoss(void);

	float x;

};

