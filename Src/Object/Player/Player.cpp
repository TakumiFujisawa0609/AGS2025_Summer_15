#include<DxLib.h>
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::SystemInit()
{
	return true;
}

void Player::GameInit()
{
	player.alive = true;
	player.pos = { 64.0f,200.0f,0.0f };
	player.size = { SIZE_X,SIZE_Y,0.0f };
	player.radius = RADIUS;
	player.hp = HP_MAX;
}

void Player::Update()
{
}

void Player::Draw()
{
}

bool Player::Release()
{
	return true;
}
