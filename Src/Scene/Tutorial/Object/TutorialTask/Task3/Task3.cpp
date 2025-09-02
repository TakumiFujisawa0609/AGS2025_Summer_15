#include"Task3.h"

Task3::Task3()
{
}

Task3::~Task3()
{
}

void Task3::Load(void)
{
	for (int i = 0; i < MATO_NUM; i++) {
		tutorialObj_.emplace_back(new Mato());
	}
	tutorialObj_.emplace_back(new Kakashi3());
	TaskBase::Load();
}

void Task3::Init(void)
{
	TaskBase::Init();

	for (int i = 0; i < MATO_NUM; i++) {
		dynamic_cast<Mato*>(tutorialObj_[i])->SetPos(POSS[i]);
	}
}

const bool Task3::End(void)const 
{
	for (auto& obj : tutorialObj_) {
		if (!dynamic_cast<Mato*>(obj)) { continue; }
		if (obj->GetUnit().isAlive_) { return false; }
	}
	return true;
}