#pragma once

#include"../../../../Object/UnitBase.h"

class TutorialObject
{
public:
	TutorialObject() :
		unit_()
	{}

	virtual ~TutorialObject() {};

	virtual void Load(void) = 0;
	virtual void Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Release(void) = 0;

	virtual void Action(void) {};

	const Base& GetUnit(void)const { return unit_; }

protected:
	Base unit_;
};