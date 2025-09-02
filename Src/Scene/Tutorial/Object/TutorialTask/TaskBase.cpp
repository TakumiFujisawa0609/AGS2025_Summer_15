#include"TaskBase.h"

TaskBase::TaskBase():
	tutorialObj_(),
	end_(true)
{
}

void TaskBase::Load(void)
{
	for (auto& obj : tutorialObj_) { obj->Load(); }
}

void TaskBase::Init(void)
{
	end_ = false;
	for (auto& obj : tutorialObj_) { obj->Init(); }
}

void TaskBase::Update(void)
{
	for (auto& obj : tutorialObj_) { obj->Update(); }
}

void TaskBase::Draw(void)
{
	for (auto& obj : tutorialObj_) { obj->Draw(); }
}

void TaskBase::Release(void)
{
	for (auto& obj : tutorialObj_) {
		if (!obj) { continue; }
		obj->Release();
		delete obj;
		obj = nullptr;
	}
	tutorialObj_.clear();
}

