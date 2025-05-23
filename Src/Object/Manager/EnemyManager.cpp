#include "EnemyManager.h"
#include"../Enemy/EnemyBamboo.h"

EnemyManager::EnemyManager()
{
	for (int ii = 0; ii < ENEMY_MAX; ii++)
	{
		bamboo_[ii] = new EnemyBamboo();
		bamboo_[ii]->Init();

	}
}

EnemyManager::~EnemyManager()
{
	for (int ii = 0; ii < ENEMY_MAX; ii++)
	{
		bamboo_[ii]->Release();
		delete bamboo_[ii];
		bamboo_[ii] = nullptr;

	}
}
void EnemyManager::Init()
{
	for (int ii = 0; ii < ENEMY_MAX; ii++)
	{
		bamboo_[ii]->Init();
	}
}

void EnemyManager::Update()
{
	for (int ii = 0; ii < ENEMY_MAX; ii++)
	{
		bamboo_[ii]->Update();
	}
}

void EnemyManager::Draw()
{
	for (int ii = 0; ii < ENEMY_MAX; ii++)
	{
		bamboo_[ii]->Draw();
	}
}

void EnemyManager::Relese()
{
	for (int ii = 0; ii < ENEMY_MAX; ii++)
	{
		bamboo_[ii]->Release();
	}
}