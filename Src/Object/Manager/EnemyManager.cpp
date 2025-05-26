#include "EnemyManager.h"
#include"../Enemy/EnemyBamboo.h"
#include"cmath"

EnemyManager::EnemyManager()
{

}

EnemyManager::~EnemyManager()
{
}
void EnemyManager::Init(int ii)
{
	bamboo_[ii] = new EnemyBamboo();
	bamboo_[ii]->Init();
}

void EnemyManager::Update(int ii)
{
	bamboo_[ii]->Update();
}

void EnemyManager::Draw(int ii)
{
	bamboo_[ii]->Draw();
}

void EnemyManager::Relese(int ii)
{
	bamboo_[ii]->Release();
	delete bamboo_[ii];
	bamboo_[ii] = nullptr;
}

