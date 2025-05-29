#include<string>

#include "Player.h"
#include"../../Manager/InputManager.h"
#include"../../Application.h"
#include"../../Manager/Camera.h"
#include"../../Manager/Collision.h"
#include"../../Manager/SceneManager.h"
#include"../Stage/Stage.h"
#include"../../Scene/GameScene.h"

Player::Player()
{
}

Player::~Player()
{
}



void Player::Init()
{
	//LoadPlayerImage();

	unit_.isAlive_ = true;
	unit_.pos_ = { SceneManager::MAIN_SCREEN_SIZE_X / 2,SceneManager::MAIN_SCREEN_SIZE_Y / 2 };
	unit_.size_ = { /*SIZE_X,SIZE_Y,*/33.0f,65.0f };
	unit_.radius_ = RADIUS;
	unit_.hp_ = HP_MAX;
	unit_.speed_ = MOVE_POW;
	motionType_ = MOTION_TYPE::E_MOTION_IDLE;		//モーションタイプ
	animCounter_ = 0.0f;

	attackStat_ = ATTACK_STAT::E_ATTACK_STAT_NON;

	//攻撃
	isAttack_ = false;
	attackCounter_ = 0;

	//ジャンプ
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
	isEvasionInbincible_ = false;
	evasionCounter_ = 0;
	evasionCoolDown_ = 0;
	
	Collision::CreateInstance();
}

void Player::Update()
{
	Move();

	ProcessEvasion();
	CollisionStageX();



	ProcessJump();

	UpdatePositionY();
	CollisionStageY();




	ProcessAtatck();




	ChangeDispPos();
}

void Player::Draw()
{
	//DrawCircle(player_.disppos_.x, player_.disppos_.y, 10, GetColor(255, 0, 0), true);
	DrawCircle(unit_.disppos_.x, unit_.disppos_.y, 2, 0x00ffff, true);
	if (isAttack_) {
		DrawOval(unit_.disppos_.x, unit_.disppos_.y, 48,32, 0x00f0f0, true);
	}
	DrawOval(unit_.disppos_.x, unit_.disppos_.y, unit_.size_.x / 2, unit_.size_.y / 2, 0xff0000, true);

	DrawFormatString(0, 64, 0x0000ff, "プレイヤー座標(%.2f,%.2f)", unit_.pos_.x, unit_.pos_.y);
	DrawFormatString(0, 80, 0x0000ff, "プレイヤーの向き%d", playerDir_);
	DrawFormatString(0, 96, 0x00ff00, "プレイヤーの攻撃%d", attackStat_);

	auto& inp = InputManager::GetInstance();
		Vector2 mP = inp.GetMousePos();
		DrawFormatString(0, 120, 0xff00ff, "マウス左クリック: (%d, %d)", mP.x, mP.y);
	if (inp.IsTrgMouseLeft()) {
	}

	//SetDrawPlayer();
}

void Player::Release()
{
}

void Player::Move(void)
{
	auto&InpMng= InputManager::GetInstance();

	//モーションタイプの初期化を行う
	motionType_ = MOTION_TYPE::E_MOTION_IDLE;

	// コントローラー（PAD1の左スティック
	auto padState = InpMng.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
	const int stickThreshold = 500; // スティックのしきい値

	if (InpMng.IsNew(KEY_INPUT_D)||padState.AKeyLX>stickThreshold) {
		unit_.pos_.x += unit_.speed_;
		playerDir_ =AsoUtility::DIRECTION::E_DIR_RIGHT;
		//モーションを変更
		motionType_ = MOTION_TYPE::E_MOTION_RUN;
	}
	if (InpMng.IsNew(KEY_INPUT_A)||padState.AKeyLX<-stickThreshold) {
		unit_.pos_.x -= unit_.speed_;
		playerDir_ =AsoUtility::DIRECTION::E_DIR_LEFT;
		//モーションを変更
		motionType_ = MOTION_TYPE::E_MOTION_RUN;
	}
}

void Player::Evasion(void)
{
	switch (playerDir_)
	{
	case AsoUtility::DIRECTION::E_DIR_RIGHT:
		unit_.pos_.x += EVASION_LENGTH;
		break;
	case AsoUtility::DIRECTION::E_DIR_LEFT:
		unit_.pos_.x -= EVASION_LENGTH;
		break;
	}
}

void Player::ProcessEvasion(void)
{
	//回避
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_S)
		&&!isEvasionCoolDown_) {
		SceneManager::GetInstance().Slow();
		isEvasion_ = true;
		isEvasionCoolDown_ = true;
		isEvasionInbincible_ = true;
	}
	//回避時の無敵時間
	if (isEvasion_) {
		evasionCounter_++;
		Evasion();
		//無敵処理
		if (evasionCounter_ >= EVASION_INVINCIBLE) {
			isEvasionInbincible_ = false;
		}
		//回避処理
		if (evasionCounter_ >= EVASION_TIME) {
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
	unit_.pos_.y += verticalAcceleration_;
}

void Player::ProcessJump(void)
{
	//ジャンプ判定
	if (InputManager::GetInstance().IsNew(KEY_INPUT_J)) {
		isJump_ = true;
	}
	//一回目のジャンプ
	if (InputManager::GetInstance().IsNew(KEY_INPUT_J)
		&& inputJumpKeyCounter_ < INPUT_JUMPKEY_FRAME
		&& firstJumpFlg_) {
		inputJumpKeyCounter_++;
		jumpPower_ = jumpPower_ + (MAX_JUMP_POWER / static_cast<float>(INPUT_JUMPKEY_FRAME));

		Jump();
	}
	//二段ジャンプ
	if (InputManager::GetInstance().IsNew(KEY_INPUT_J)
		&& inputJumpKeyCounter_ < INPUT_JUMPKEY_FRAME
		&& secondJumpFlg_) {
		inputJumpKeyCounter_++;
		jumpPower_ = jumpPower_ + (MAX_JUMP_POWER / static_cast<float>(INPUT_JUMPKEY_FRAME));

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
		}
		else if (!firstJumpFlg_) {
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
	verticalAcceleration_ = (verticalAcceleration_ < MAX_GRAVITY) ? verticalAcceleration_ + gravity_ : verticalAcceleration_;
}

void Player::CollisionStageY(void)
{
	Collision& ins = Collision::GetInstance();

	////天井
	if ((unit_.pos_.y - unit_.size_.y / 2) <= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::UP)) {
		inputJumpKeyCounter_ = INPUT_JUMPKEY_FRAME;
		unit_.pos_.y = ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::UP) + unit_.size_.y / 2;
	}

	//空中にいるなら重力を加える
	if (unit_.pos_.y + unit_.size_.y / 2 >= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::DOWN)) {
		//地面に接地
		unit_.pos_.y = (ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::DOWN)) - unit_.size_.y / 2;
		verticalAcceleration_ = 0;
		isJump_ = false;
		firstJumpFlg_ = true;
		secondJumpFlg_ = true;
		thirdJumpFlg_ = true;
		jumpPower_ = 0;
		inputJumpKeyCounter_ = 0;
	}
	else {
		Gravity();
	}
}

void Player::CollisionStageX(void)
{
	Collision& ins = Collision::GetInstance();

	//右
	if ((unit_.pos_.x + unit_.size_.x / 2) >= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::RIGHT)) {
		unit_.pos_.x = (ins.GetStageLine(unit_.pos_, unit_.size_, Collision::RIGHT)) - unit_.size_.x / 2;
	}

	//左
	if ((unit_.pos_.x - unit_.size_.x / 2) <= ins.GetStageLine(unit_.pos_, unit_.size_, Collision::DIR::LEFT)) {
		unit_.pos_.x = (ins.GetStageLine(unit_.pos_, unit_.size_, Collision::LEFT)) + unit_.size_.x / 2;
	}
}

void Player::Attack(void)
{
#pragma region MyRegion

	//switch (attackStat_)
	//{
	//case Player::ATTACK_STAT::E_ATTACK_STAT_KATTO:
	//	break;
	//case Player::ATTACK_STAT::E_ATTACK_STAT_NUGRU:
	//	break;
	//}
	//if (isAttack_) {
	//	attackCounter_++;
	//	if (attackCounter_ >= ATTACK_TIME) {
	//		attackStat_ = ATTACK_STAT::E_ATTACK_STAT_NON;
	//		isAttack_ = false;
	//		attackCounter_ = 0;
	//		isAttackCoolDown_ = true;
	//		attackCoolDown_ = 0;
	//	}
	//}
	// if (isAttackCoolDown_) {
	//	attackCoolDown_++;
	//	if (attackCoolDown_ >= ATTACK_COOLDOWN) {
	//		isAttackCoolDown_ = false;
	//		attackCoolDown_ = 0;
	//	}
	//}
#pragma endregion
}

void Player::ProcessAtatck(void)
{
#pragma region MyRegion


	//auto& ins = InputManager::GetInstance();
	//if (!isAttack_) {

	//if (ins.IsNew(KEY_INPUT_Q)) {
	//	attackStat_ = ATTACK_STAT::E_ATTACK_STAT_KATTO;
	//	isAttack_ = true;
	//}
	//else if (ins.IsNew(KEY_INPUT_E)) {
	//	attackStat_ = ATTACK_STAT::E_ATTACK_STAT_NUGRU;
	//	isAttack_ = true;
	//}
	//}
#pragma endregion
	Attack();
}

void Player::ChangeDispPos(void)
{
	unit_.disppos_.x = unit_.pos_.x - Camera::GetInstance().GetPos().x;
	unit_.disppos_.y = unit_.pos_.y - Camera::GetInstance().GetPos().y;
}

//void Player::LoadPlayerImage(void)
//{
//	std::string basePath = Application::PATH_PLAYER;
//
//	int motion = 0;
//	int motion_max = static_cast<int>(MOTION_TYPE::E_MOTION_MAX);
//
//	//画像ハンドル番号のテーブルの初期化
//	for (int i = 0; i < motion_max; i++) {
//		for (int j = 0; j < 15; j++) {
//			img[i][j] = -1;
//		}
//	}
//	//待機モーション
//	int err;
//	motion = static_cast<int>(MOTION_TYPE::E_MOTION_IDLE);
//	err=LoadDivGraph((basePath+"IDLE.png").c_str(),3,3,1,
//		SIZE_X, SIZE_Y, &img[motion][4]);
//	int img= LoadGraph("Data/Image/Player/IDLE.png");
//	////走りモーション
//	//motion = static_cast<int>(MOTION_TYPE::E_MOTION_RUN);
//	//err = LoadDivGraph((basePath+"RUN.png").c_str(), MAX_ANIM_NUM, MAX_ANIM_NUM, 1,
//	//	SIZE_X, SIZE_Y, &img[motion]);
//	////ジャンプモーション
//	//motion = static_cast<int>(MOTION_TYPE::E_MOTION_JUMP);
//	//err=LoadDivGraph((basePath+"JUMP.png").c_str(), MAX_ANIM_NUM, MAX_ANIM_NUM, 1,
//	//	SIZE_X, SIZE_Y, &img[motion]);
//
//	
//}
//
//void Player::DrawPlayer(int modelId)
//{
//	//プレイヤーの向き
//	bool isLeft = true;
//	if (playerDir_ == AsoUtility::DIRECTION::E_DIR_RIGHT) {
//		isLeft = false;
//	}
//	DrawRotaGraph(player_.disppos_.x, player_.disppos_.y-SIZE_Y/2,
//		10.0, 0.0, modelId, true, isLeft);
//}
//
//void Player::SetDrawPlayer(void)
//{
//	if (isJump_) {
//		//ジャンプ中
//		motionType_ = MOTION_TYPE::E_MOTION_JUMP;
//	}
//
//	//現在のモーション
//	int nowMotion = static_cast<int>(motionType_);
//	switch (motionType_)
//	{
//	case Player::MOTION_TYPE::E_MOTION_IDLE:
//		DrawPlayer(img[nowMotion][0]);
//	case Player::MOTION_TYPE::E_MOTION_RUN:
//	case Player::MOTION_TYPE::E_MOTION_JUMP:
//	case Player::MOTION_TYPE::E_MOTION_DAMAGE:
//	case Player::MOTION_TYPE::E_MOTION_EVASION:
//		break;
//	}
//
//
//}



