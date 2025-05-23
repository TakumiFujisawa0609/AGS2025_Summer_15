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

	static void Slow(void) { slowCounter_ = SLOW_TIME; }
	static void HitStop(void) { hitStopCounter_ = HIT_STOP_TIME; }

private:
	//プレイヤークラスのインスタンス
	Player* player_;
	Stage* stage_;
	EnemyManager* enemy_ ;

	float x;


	static constexpr int SLOW_TIME = 40;
	static int slowCounter_;

	static constexpr int HIT_STOP_TIME = 20;
	static int hitStopCounter_;

};

