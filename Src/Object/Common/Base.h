#pragma once
#include"../../Common/Vector2.h"


struct Base
{
	Vector2F pos_;		//座標
	Vector2F disppos_;
	Vector2F prevpos_;

	float radius_;		//半径
	Vector2F size_;		//大きさ

	int modelId_;		//ハンドル番号

	float speed_;		//移動速度

	bool isAlive_;		//生存判定(true=生存/false=死んでいる！！！)

	int hp_;			//HP
};
