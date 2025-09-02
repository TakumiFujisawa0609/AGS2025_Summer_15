#include"Task4.h"

Task4::Task4()
{
}

Task4::~Task4()
{
}

void Task4::Load(void)
{
	tutorialObj_.emplace_back(new Kakashi4());
	TaskBase::Load();
}