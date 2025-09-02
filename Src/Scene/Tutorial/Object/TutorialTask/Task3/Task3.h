#pragma once

#include"../TaskBase.h"

#include"Object/Mato.h"
#include"Object/Kakashi3.h"

#include"../../../../../Application.h"

class Task3 : public TaskBase
{
public:
	static constexpr int MATO_NUM = 3;
	const Vector2F POSS[MATO_NUM] = {
		{Mato::RADIUS + 10.0f,150.0f},
		{Application::SCREEN_SIZE_X / 2.0f,150.0f},
		{(Application::SCREEN_SIZE_X - Mato::RADIUS - 10.0f),150.0f}
	};

	Task3();
	~Task3();

	void Load(void)override;
	void Init(void)override;
	const bool End(void)const override;
};
