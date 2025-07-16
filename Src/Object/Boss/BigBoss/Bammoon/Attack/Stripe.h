#pragma once

#include<vector>

#include"../../../../../Common/Vector2.h"
#include"../../../../Common/Base.h"
#include"../../../../../Application.h"

class Stripe
{
public:
	static constexpr int NUM = 20;

	static constexpr float SIZE_X = 51.0f;
	static constexpr float SIZE_Y = 800.0f;

	static constexpr float SPEED = 30.0f;

	Stripe();
	~Stripe();

	void Init(const Vector2F* pos);
	void Update(void);
	void Draw(void);
	void Release(void);

	std::vector<Base>Get(void) { return obj_; }

	void On(int i);

	bool End(void) { return end_ >= NUM; }

private:
	int image_;
	int nokoImg_;

	std::vector<Base> obj_;

	const Vector2F* bossPos_;

	int end_;

	bool side_;

	static constexpr float POS_Y = (float)(Application::SCREEN_SIZE_Y + SIZE_Y);
};

