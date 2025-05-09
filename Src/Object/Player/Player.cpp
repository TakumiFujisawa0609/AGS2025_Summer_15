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

	verticalAcceleration_ = 0;
	jumpPower_ = 0;
	isJump_ = false;
	firstJumpFlg_ = true;
	secondJumpFlg_ = true;
	thirdJumpFlg_ = true;
	inputJumpKeyCounter_ = 0;
	gravity_ = GRAVITY;

	playerDir_ = AsoUtility::DIRECTION::E_DIR_RIGHT;

	isEvasion_ = false;
	isEvasionCoolDown_ = false;
	evasionCounter_ = 0;
	evasionCoolDown_ = 0;
}

void Player::Update()
{
	Move();
	ProcessJump();
	UpdatePositionY();

	ProcessEvasion();

	CollisionStage();
}

void Player::Draw()
{
	DrawCircle(player_.pos_.x, player_.pos_.y,10, GetColor(255,0,0), true);

	DrawFormatString(0, 64, 0xffffff, "プレイヤー座標(%.2f,%.2f)", player_.pos_.x, player_.pos_.y);
	DrawFormatString(0, 80, 0xffffff, "プレイヤーの向き%d", playerDir_);
}

bool Player::Release()
{
	return true;
}

void Player::Move(void)
{
	auto&InpMng= InputManager::GetInstance();

	if (InpMng.IsNew(KEY_INPUT_D)) {
		player_.pos_.x += player_.speed_;
		playerDir_ =AsoUtility::DIRECTION::E_DIR_RIGHT;
	}
	if (InpMng.IsNew(KEY_INPUT_A)) {
		player_.pos_.x -= player_.speed_;
		playerDir_ =AsoUtility::DIRECTION::E_DIR_LEFT;
	}
}

void Player::Evasion(void)
{
	switch (playerDir_)
	{
	case AsoUtility::DIRECTION::E_DIR_RIGHT:
		player_.pos_.x += EVASION_LENGTH;
		break;
	case AsoUtility::DIRECTION::E_DIR_LEFT:
		player_.pos_.x -= EVASION_LENGTH;
		break;
	}
}

void Player::ProcessEvasion(void)
{
	//回避
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_S)
		&&!isEvasionCoolDown_) {
		Evasion();
		isEvasion_ = true;
		isEvasionCoolDown_ = true;
	}
	//回避時の無敵時間
	if (isEvasion_) {
		evasionCounter_++;
		if (evasionCounter_ >= EVASION_INVINCIBLE) {
			evasionCounter_ = 0;
			isEvasion_ = false;			//無敵時間の終了
		}
	}
	//回避のクールダウン
	if (isEvasionCoolDown_) {
		evasionCoolDown_++;
		if (evasionCoolDown_ >= EVASION_COOLDOWN) {
			evasionCoolDown_ = 0;
			isEvasionCoolDown_ = false;		//クールタイムの終了
		}
	}
}

void Player::UpdatePositionY(void)
{
	player_.pos_.y += verticalAcceleration_;
}

void Player::ProcessJump(void)
{
	//ジャンプ判定
	if (InputManager::GetInstance().IsNew(KEY_INPUT_J)) {
		isJump_ = true;		
	}
	//一回目のジャンプ
	if (InputManager::GetInstance().IsNew(KEY_INPUT_J) 
		&&inputJumpKeyCounter_<INPUT_JUMPKEY_FRAME
		&&firstJumpFlg_) {
		inputJumpKeyCounter_++;
		jumpPower_ = jumpPower_ + (MAX_JUMP_POWER / static_cast<float>(INPUT_JUMPKEY_FRAME));

		Jump();
	}
	//二段ジャンプ
	if (InputManager::GetInstance().IsNew(KEY_INPUT_J)
		&& inputJumpKeyCounter_ < INPUT_JUMPKEY_FRAME
		&& secondJumpFlg_) {
		inputJumpKeyCounter_++;
		jumpPower_=jumpPower_+ (MAX_JUMP_POWER / static_cast<float>(INPUT_JUMPKEY_FRAME));

		Jump();
	}
	//三弾ジャンプ
	if (InputManager::GetInstance().IsNew(KEY_INPUT_J)
		&& inputJumpKeyCounter_ < INPUT_JUMPKEY_FRAME
		&& thirdJumpFlg_) {
		inputJumpKeyCounter_++;
		jumpPower_ = jumpPower_ + (MAX_JUMP_POWER / static_cast<float>(INPUT_JUMPKEY_FRAME));
		Jump();

	}

	//ジャンプキーを離したらカウンターをリセット
	if (InputManager::GetInstance().IsTrgUp(KEY_INPUT_J)) {
		inputJumpKeyCounter_ = 0;
		if (!secondJumpFlg_) {
			thirdJumpFlg_ = false;
		}else if (!firstJumpFlg_) {
			secondJumpFlg_ = false;
			jumpPower_ = 0;
		}
		else {
			firstJumpFlg_ = false;
			jumpPower_ = 0;
		}
	}
}


void Player::Jump(void)
{
	//Y軸加速度にジャンプ力を加える
	verticalAcceleration_ += jumpPower_;
	//Y軸加速度が最大ジャンプ力を超えたら最大ジャンプ量に設定
	verticalAcceleration_ = (verticalAcceleration_ < MAX_JUMP_POWER) ? MAX_JUMP_POWER : verticalAcceleration_;
}

void Player::Gravity(void)
{
	//Y軸加速度に重力を加える
	verticalAcceleration_ += gravity_;
}

void Player::CollisionStage(void)
{
	//空中にいるなら重力を加える
	if (player_.pos_.y <= 500) {
		Gravity();
	}
	//地面に接地
	else {
		player_.pos_.y = 500;
		verticalAcceleration_ = 0;
		isJump_ = false;
		firstJumpFlg_ = true;
		secondJumpFlg_ = true;
		thirdJumpFlg_ = true;
		jumpPower_ = 0;
		inputJumpKeyCounter_ = 0;

	}

}

