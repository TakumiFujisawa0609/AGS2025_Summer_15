#pragma once
#include"../../main.h"

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

	Unit GetPlayer(void) { return player; }
private:
	Unit player;

};



