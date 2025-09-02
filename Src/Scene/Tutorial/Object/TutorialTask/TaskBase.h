#pragma once

#include<vector>

#include"TutorialObject.h"

class TaskBase
{
public:
	TaskBase();
	virtual ~TaskBase() {};

	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);

	std::vector<TutorialObject*>GetTutorialObject(void) { return tutorialObj_; }
	virtual const bool End(void)const { return end_; };
	virtual void PowerEnd(void) { end_ = true; }

protected:
	std::vector<TutorialObject*>tutorialObj_;

	bool end_;
};
