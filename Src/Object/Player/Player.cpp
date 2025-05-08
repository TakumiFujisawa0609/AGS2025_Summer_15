#include "Player.h"
#include"../../Manager/InputManager.h"
#include"../../Application.h"
#include"../../Manager/Camera.h"

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
	player_.pos_ = { Application::SCREEN_SIZE_X/2,Application::SCREEN_SIZE_Y/2 };
	player_.size_ = { SIZE_X,SIZE_Y, };
	player_.radius_ = RADIUS;
	player_.hp_ = HP_MAX;
	player_.speed_ = MOVE_POW;
}

void Player::Update()
{
	Move();

}

void Player::Draw()
{
	DrawCircle(player_.pos_.x, player_.pos_.y,10, GetColor(255,0,0), true);

	DrawFormatString(0, 64, 0xffffff, "プレイヤー座標(%.2f,%.2f)", player_.pos_.x, player_.pos_.y);
}

bool Player::Release()
{
	return true;
}

void Player::Move()
{
	auto&InpMng= InputManager::GetInstance();

	if (InpMng.IsNew(KEY_INPUT_D)) {
		player_.pos_.x += player_.speed_;
	}
	if (InpMng.IsNew(KEY_INPUT_A)) {
		player_.pos_.x -= player_.speed_;
	}
}
