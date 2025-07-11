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

	const Vector2F S_POS[NUM] =
	{
		{SIZE_X,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 2,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 3,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 4,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 5,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 6,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 7,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 8,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 9,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 10,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 11,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 12,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 13,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 14,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 15,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 16,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 17,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 18,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)},
		{SIZE_X * 19,(float)(Application::SCREEN_SIZE_Y + SIZE_Y) },
		{SIZE_X * 20,(float)(Application::SCREEN_SIZE_Y + SIZE_Y)}
	};
};

