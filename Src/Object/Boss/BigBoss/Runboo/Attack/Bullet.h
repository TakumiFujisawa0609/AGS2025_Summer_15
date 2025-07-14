#pragma once
#include<DxLib.h>
#include"../../../../../Common/Vector2.h"

struct BulletStruct {
	Vector2F pos;
	Vector2F vel;
	bool isActive;

	void Update() {
		if (!isActive) return;
		pos += vel;
	}

	void Draw() {
		if (!isActive) return;
		DrawCircle((int)pos.x, (int)pos.y, 5, GetColor(255, 255, 0), true);
	}
};