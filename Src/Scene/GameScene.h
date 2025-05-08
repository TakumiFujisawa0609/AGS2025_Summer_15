#pragma once
#include<memory>
#include "SceneBase.h"

class Player;

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
};

