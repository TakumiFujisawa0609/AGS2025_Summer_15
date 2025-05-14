#include "EnemyBamboo.h"

EnemyBamboo::EnemyBamboo()
{
	enemy_.pos_ = { 0,0 };
	enemy_.radius_ = ENEMYBAMBOO_RADIUS;
}

EnemyBamboo::~EnemyBamboo()
{
}

void EnemyBamboo::Init()
{
}

void EnemyBamboo::Update()
{
}

void EnemyBamboo::Draw()
{
	DrawCircle(enemy_.pos_.x, enemy_.pos_.y, enemy_.radius_, 0x00ff00, true);
}

void EnemyBamboo::Release()
{
}
