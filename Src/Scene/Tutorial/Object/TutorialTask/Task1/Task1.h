#pragma once

#include"../TaskBase.h"

#include"Object/Kakashi.h"

class Task1 : public TaskBase
{
public:
	Task1();
	~Task1();

	void Load(void)override;

	const bool End(void)const override;

};

