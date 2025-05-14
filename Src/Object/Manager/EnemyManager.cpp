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

}

void EnemyManager::Update()
{
}

void EnemyManager::Draw()
{
}

void EnemyManager::Relese()
{
	
}