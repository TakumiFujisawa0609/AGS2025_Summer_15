#pragma once
#include<DxLib.h>
#include"../../../Common/Base.h"

class Weakness
{
public:
	static constexpr float SIZE_X = 100;
	static constexpr float SIZE_Y = 100;

	static constexpr float AMPLITUDE = 10.0f;          // 振幅（上下の幅）
	static constexpr float MOVE_Y_SPEED = 0.05f;              // 動く速さ（角度の進み）


	Weakness();
	~Weakness();

	void Init(Vector2F disppos);
	void Update();
	void Draw();
	void Release();

private:
	Base unit_;

	float cnt_ = 0.0f;                 


};