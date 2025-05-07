#pragma once
#include"../Common/Base.h"

class Player
{
public:
	static constexpr int SIZE_X = 64;
	static constexpr int SIZE_Y = 96;
	static constexpr float RADIUS = 64.0f;
	static constexpr int HP_MAX = 100;

	Player();
	~Player();

	bool SystemInit();
	void GameInit();
	void Update();
	void Draw();
	bool Release();


	//ゲッター関数
	Base GetPlayer(void) { return player_; }
	
	//セッター関数
	void SetAliveOff(void) { player_.isAlive_ = false; }

private:
	Base player_;

};



