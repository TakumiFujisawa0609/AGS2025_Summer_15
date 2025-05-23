#pragma once
#include<memory>
#include "SceneBase.h"

class Player;
class Stage;
class EnemyManager;

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
};

