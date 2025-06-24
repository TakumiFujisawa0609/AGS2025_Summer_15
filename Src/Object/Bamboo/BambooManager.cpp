#include"BambooManager.h"

BambooManager::BambooManager()
{
}

BambooManager::~BambooManager()
{
}

void BambooManager::Init(Vector2F* pPos, int* bp)
{
	this->pPos_ = pPos;
	this->playerBp_ = bp;

	image_ = LoadGraph("Data/Image/DropBamboo.png");
	if (image_ == -1) {
		return;
	}
}

void BambooManager::Update(void)
{
	for (auto b : bamboos_) {
		b->Update();
	}
}

void BambooManager::Draw(void)
{
	for (auto b : bamboos_) {
		b->Draw();
	}
}

void BambooManager::Release(void)
{
	for (auto b : bamboos_) {
		b->Release();
	}
	DeleteGraph(image_);
}

void BambooManager::Create(Vector2F pos, int num)
{
	for (int i = 0; i < num; i++) {

		bool reciycle = false;

		for (auto b : bamboos_) {
			if (!b->GetUnit().isAlive_) {
				b->Set(pos);
				reciycle = true;
				break;
			}
		}
		if (reciycle)continue;

		bamboos_.emplace_back(new Bamboo());
		bamboos_[bamboos_.size() - 1]->Set(pos, pPos_, playerBp_, image_);
	}
}

