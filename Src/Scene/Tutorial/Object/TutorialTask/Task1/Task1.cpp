#include"Task1.h"


Task1::Task1()
{
}

Task1::~Task1()
{
}

void Task1::Load(void)
{
	tutorialObj_.emplace_back(new Kakashi());
	TaskBase::Load();
}

const bool Task1::End(void)const
{
	if (tutorialObj_[0]->GetUnit().isAlive_ == false) { return true; }
	return false;
}