#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	bamboo_ = new EnemyBamboo();
	bamboo_->Init();
}

EnemyManager::~EnemyManager()
{
	bamboo_->Release();
	delete bamboo_;
	bamboo_ = nullptr;
}
void EnemyManager::Init()
{
	bamboo_->Init();
}

void EnemyManager::Update()
{
	bamboo_->Update();
}

void EnemyManager::Draw()
{
	bamboo_->Draw();
}

void EnemyManager::Relese()
{
	bamboo_->Release();
}