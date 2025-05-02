#include "Player.h"
#include"../../Manager/InputManager.h"

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
	player_.isAlive_ = true;
	player_.pos_ = { 64.0f,200.0f, };
	player_.size_ = { SIZE_X,SIZE_Y, };
	player_.radius_ = RADIUS;
	player_.hp_ = HP_MAX;
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
