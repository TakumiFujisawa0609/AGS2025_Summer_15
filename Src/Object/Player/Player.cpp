#include<string>

#include "Player.h"
#include"../../Manager/InputManager.h"
#include"../../Application.h"
#include"../../Manager/Camera.h"
#include"../../Manager/Collision.h"
#include"../../Manager/SceneManager.h"
#include"../Stage/Stage.h"
#include"../../Scene/GameScene.h"
#include"Attack/ArialSweep.h"

Player::Player()
{
	LoadPlayerImage();
}

Player::~Player()
{
}



void Player::Init()
{

	unit_.isAlive_ = true;
	unit_.pos_ = { Application::MAIN_SCREEN_SIZE_X / 2,Application::MAIN_SCREEN_SIZE_Y / 2 };
	unit_.nextpos_ = unit_.pos_;
	unit_.size_ = { SIZE_X,SIZE_Y, };
	unit_.radius_ = RADIUS;
	unit_.hp_ = HP_MAX;
	unit_.speed_ = MOVE_POW;
	motionType_ = MOTION_TYPE::E_MOTION_IDLE;		//モーションタイプ
	animCounter_ = 0.0f;

	attackStat_ = ATTACK_STAT::E_ATTACK_STAT_NON;

	animLoop_ = true;

	//攻撃
	isAttack_ = false;
	attackCounter_ = 0;
	arialSweepCounter_ = 0;

	//ジャンプ
	unit_.yAccel_ = 0;
	jumpPower_ = 0;
	isJump_ = false;
	firstJumpFlg_ = true;
	secondJumpFlg_ = true;
	thirdJumpFlg_ = true;
	inputJumpKeyCounter_ = 0;

	playerDir_ = AsoUtility::DIRECTION::E_DIR_RIGHT;
	isMove_ = true;

	//回避
	isEvasion_ = false;
	isEvasionCoolDown_ = false;
	isEvasionInbincible_ = false;
	evasionCounter_ = 0;
	evasionCoolDown_ = 0;
	workDir_ = AsoUtility::DIRECTION::E_DIR_LEFT;

	// ガード用変数の初期化
	isGuard_ = false;           // ガード中
	guardMaxCounter_ = 0;      // 最大ガード時間
	perStiffness_ = 0;          // 前硬直
	postStiffness_ = 0;        // 後硬直
	perGuardKey_ = false;           // トリガーアップ用変数
	nowGuardKey_ = false;           // トリガーアップ用変数
	guardKeyUpBuffer_ = 0;		//ジャストガード受付猶予カウンター
	guardStat_ = GUARD_STAT::E_GUARD_NON;


	arialSweep_ = new ArialSweep();
	arialSweep_->Init(&unit_.nextpos_, &unit_.disppos_);

	Collision::CreateInstance();
}

void Player::Update()
{
	if (isMove_) {
		Move();
		ProcessJump();
	}

	ProcessAtatck();
	ProcessGuard();

	AnimationUpdate();

	UnitBase::Update();
}

void Player::Draw()
{
	//DrawOval(unit_.disppos_.x, unit_.disppos_.y, unit_.size_.x / 2, unit_.size_.y / 2, 0xff0000, true);

	DrawFormatString(0, 64, 0x0000ff, "プレイヤー座標(%.2f,%.2f)", unit_.nextpos_.x, unit_.nextpos_.y);
	DrawFormatString(0, 80, 0x0000ff, "プレイヤーの向き%d", playerDir_);
	DrawFormatString(0, 96, 0x00ff00, "プレイヤーの攻撃%d", attackStat_);
	//DrawFormatString(0.112, 0xff00ff, "プレイヤーのでぃすぷぽす(%.2f,%.2f)", unit_.disppos_.x,unit_.disppos_.y);
	// 修正されたコード
	DrawFormatString(0, 112, 0xff00ff, _T("プレイヤーのでぃすぷぽす(%.2f,%.2f)"), unit_.disppos_.x, unit_.disppos_.y);

	switch (attackStat_)
	{
	case Player::ATTACK_STAT::E_ATTACK_STAT_NON:
		break;
	case Player::ATTACK_STAT::E_ATTACK_STAT_ARIALSWEEP:
		break;
	}
	arialSweep_->Draw();

	if (isGuard_) {

		DrawCircle(unit_.disppos_.x, unit_.disppos_.y, 50, 0x0000ff, true);
	}
	//if (playerDir_ == AsoUtility::DIRECTION::E_DIR_LEFT) {
	//	DrawCircle(unit_.disppos_.x-20, unit_.disppos_.y, 6, 0x00ff00);
	//}
	//else if (playerDir_ == AsoUtility::DIRECTION::E_DIR_RIGHT) {
	//	DrawCircle(unit_.disppos_.x + 20, unit_.disppos_.y, 6, 0x00ff00);
	//}

	SetDrawPlayer();
}

void Player::Release()
{
	arialSweep_->Release();
	delete arialSweep_;
	arialSweep_ = nullptr;

	//画像解放
	for (int i = 0; i < (int)MOTION_TYPE::E_MOTION_MAX; i++) {
		for (auto id : image_[i]) {
			DeleteGraph(id);
		}
		image_[i].clear();
	}

}


void Player::Move(void)
{
	auto& InpMng = InputManager::GetInstance();

	//モーションタイプの初期化を行う
	motionType_ = MOTION_TYPE::E_MOTION_IDLE;

	// コントローラー（PAD1の左スティック
	auto padState = InpMng.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
	const int stickThreshold = 500; // スティックのしきい値

	if (InpMng.IsNew(KEY_INPUT_D) || padState.AKeyLX > stickThreshold) {
		unit_.nextpos_.x += unit_.speed_;
		playerDir_ = AsoUtility::DIRECTION::E_DIR_RIGHT;
		//モーションを変更
		motionType_ = MOTION_TYPE::E_MOTION_RUN;
	}
	if (InpMng.IsNew(KEY_INPUT_A) || padState.AKeyLX < -stickThreshold) {
		unit_.nextpos_.x -= unit_.speed_;
		playerDir_ = AsoUtility::DIRECTION::E_DIR_LEFT;
		//モーションを変更
		motionType_ = MOTION_TYPE::E_MOTION_RUN;
	}
}


void Player::ProcessEvasion(void)
{
#pragma region	キーボード操作
	//回避
	auto& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_A) && !isEvasionCoolDown_) {
		isEvasion_ = true;
		isEvasionInbincible_ = true;
		playerDir_ = AsoUtility::DIRECTION::E_DIR_LEFT;
		workDir_ = playerDir_;
	}
	else
	if (ins.IsTrgDown(KEY_INPUT_D) && !isEvasionCoolDown_) {
		isEvasion_ = true;
		isEvasionInbincible_ = true;
		playerDir_ = AsoUtility::DIRECTION::E_DIR_RIGHT;
		workDir_ = playerDir_;
	}
	else
	if (ins.IsTrgDown(KEY_INPUT_S) && !isEvasionCoolDown_) {
		isEvasion_ = true;
		isEvasionInbincible_ = true;
		workDir_ = playerDir_;
		if (playerDir_ == AsoUtility::DIRECTION::E_DIR_RIGHT) {
			playerDir_ = AsoUtility::DIRECTION::E_DIR_LEFT;
		}
		else if (playerDir_ == AsoUtility::DIRECTION::E_DIR_LEFT) {
			playerDir_ = AsoUtility::DIRECTION::E_DIR_RIGHT;
		}
	}
	//回避時の無敵時間
	if (isEvasion_) {
		evasionCounter_++;
		Evasion();
		//無敵処理
		if (evasionCounter_ >= EVASION_INVINCIBLE) {
			isEvasionInbincible_ = false;		//無敵時間の終了
		}
		//回避処理
		if (evasionCounter_ >= EVASION_TIME) {
			evasionCounter_ = 0;
			isEvasion_ = false;				//回避の終了
			playerDir_ = workDir_;
			isEvasionCoolDown_ = true;	//回避のクールダウン突入
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
#pragma endregion

#pragma region コントローラー操作
	//auto& inpMng = InputManager::GetInstance();
	//inpMng.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
	////回避
	//if (inpMng.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::R_TRIGGER)
	//	&& !isEvasionCoolDown_) {
	////	SceneManager::GetInstance().Slow();
	//	isEvasion_ = true;
	//	isEvasionCoolDown_ = true;
	//	isEvasionInbincible_ = true;
	//}
	////回避時の無敵時間
	//if (isEvasion_) {
	//	evasionCounter_++;
	//	Evasion();
	//	//無敵処理
	//	if (evasionCounter_ >= EVASION_INVINCIBLE) {
	//		isEvasionInbincible_ = false;
	//	}
	//	//回避処理
	//	if (evasionCounter_ >= EVASION_TIME) {
	//		evasionCounter_ = 0;
	//		isEvasion_ = false;			//無敵時間の終了
	//	}
	//}
	////回避のクールダウン
	//if (isEvasionCoolDown_) {
	//	evasionCoolDown_++;
	//	if (evasionCoolDown_ >= EVASION_COOLDOWN) {
	//		evasionCoolDown_ = 0;
	//		isEvasionCoolDown_ = false;		//クールタイムの終了
	//	}
	//}
#pragma endregion

}


void Player::Evasion(void)
{
	switch (playerDir_)
	{
	case AsoUtility::DIRECTION::E_DIR_RIGHT:
		unit_.nextpos_.x += EVASION_LENGTH;
		break;
	case AsoUtility::DIRECTION::E_DIR_LEFT:
		unit_.nextpos_.x -= EVASION_LENGTH;
		break;
	case AsoUtility::DIRECTION::E_DIR_DOWN:
		break;
	}
}




void Player::ProcessJump(void)
{
#pragma region キーボード操作
	//ジャンプ判定
	if (InputManager::GetInstance().IsNew(KEY_INPUT_SPACE)) {
		isJump_ = true;
	}
	//一回目のジャンプ
	if (InputManager::GetInstance().IsNew(KEY_INPUT_SPACE)
		&& inputJumpKeyCounter_ < INPUT_JUMPKEY_FRAME
		&& firstJumpFlg_) {
		inputJumpKeyCounter_++;
		jumpPower_ = jumpPower_ + (MAX_JUMP_POWER / static_cast<float>(INPUT_JUMPKEY_FRAME));

		Jump();
	}
	//二段ジャンプ
	if (InputManager::GetInstance().IsNew(KEY_INPUT_SPACE)
		&& inputJumpKeyCounter_ < INPUT_JUMPKEY_FRAME
		&& secondJumpFlg_) {
		inputJumpKeyCounter_++;
		jumpPower_ = jumpPower_ + (MAX_JUMP_POWER / static_cast<float>(INPUT_JUMPKEY_FRAME));

		Jump();
	}
	//三弾ジャンプ
	if (InputManager::GetInstance().IsNew(KEY_INPUT_SPACE)
		&& inputJumpKeyCounter_ < INPUT_JUMPKEY_FRAME
		&& thirdJumpFlg_) {
		inputJumpKeyCounter_++;
		jumpPower_ = jumpPower_ + (MAX_JUMP_POWER / static_cast<float>(INPUT_JUMPKEY_FRAME));
		Jump();

	}

	//ジャンプキーを離したらカウンターをリセット
	if (InputManager::GetInstance().IsTrgUp(KEY_INPUT_SPACE)) {
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
#pragma endregion


#pragma region コントローラー操作
	//ジャンプ判定
	auto& InpMng = InputManager::GetInstance();
	InpMng.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
	if (InpMng.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN)) {
		isJump_ = true;
	}
	//一回目のジャンプ
	if (InpMng.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN)
		&& inputJumpKeyCounter_ < INPUT_JUMPKEY_FRAME
		&& firstJumpFlg_) {
		inputJumpKeyCounter_++;
		jumpPower_ = jumpPower_ + (MAX_JUMP_POWER / static_cast<float>(INPUT_JUMPKEY_FRAME));

		Jump();
	}
	//二段ジャンプ
	if (InpMng.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN)
		&& inputJumpKeyCounter_ < INPUT_JUMPKEY_FRAME
		&& secondJumpFlg_) {
		inputJumpKeyCounter_++;
		jumpPower_ = jumpPower_ + (MAX_JUMP_POWER / static_cast<float>(INPUT_JUMPKEY_FRAME));

		Jump();
	}
	//三弾ジャンプ
	if (InpMng.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN)
		&& inputJumpKeyCounter_ < INPUT_JUMPKEY_FRAME
		&& thirdJumpFlg_) {
		inputJumpKeyCounter_++;
		jumpPower_ = jumpPower_ + (MAX_JUMP_POWER / static_cast<float>(INPUT_JUMPKEY_FRAME));
		Jump();

	}

	//ジャンプキーを離したらカウンターをリセット
	if (InpMng.IsPadBtnTrgUp(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN)) {
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
#pragma endregion

}


void Player::Jump(void)
{
	//Y軸加速度にジャンプ力を加える
	unit_.yAccel_ += jumpPower_;
	//Y軸加速度が最大ジャンプ力を超えたら最大ジャンプ量に設定
	unit_.yAccel_ = (unit_.yAccel_ < MAX_JUMP_POWER) ? MAX_JUMP_POWER : unit_.yAccel_;
}


// 接地している時の数値の代入などをまとめた関数
void Player::IsGround(Collision::DIR dir)
{
	switch (dir)
	{
	case Collision::UP:

		//天井に衝突していたら行う処理
		inputJumpKeyCounter_ = INPUT_JUMPKEY_FRAME;
		unit_.yAccel_ = 0;

		break;

	case Collision::DOWN:

		//地面に接地していたら行う処理
		unit_.yAccel_ = 0;
		isJump_ = false;
		firstJumpFlg_ = true;
		secondJumpFlg_ = true;
		thirdJumpFlg_ = true;
		jumpPower_ = 0;
		inputJumpKeyCounter_ = 0;
		unit_.isGround_ = true;

		break;

	case Collision::LEFT:

		//左側の壁に衝突していたら行う処理

		break;

	case Collision::RIGHT:

		//右側の壁に衝突していたら行う処理

		break;

	}
}



void Player::ProcessAtatck(void)
{

	auto& ins = InputManager::GetInstance();
	if (ins.IsClickMouseLeft()) {
		attackStat_ = ATTACK_STAT::E_ATTACK_STAT_ARIALSWEEP;
		GetMousePoint(&mPos_.x, &mPos_.y);
	}

	switch (attackStat_)
	{
	case Player::ATTACK_STAT::E_ATTACK_STAT_NON:
		Attack();
		break;
	case Player::ATTACK_STAT::E_ATTACK_STAT_ARIALSWEEP:
		ArialSweepAttack();
		break;
	}

}

void Player::Attack(void)
{





}

void Player::ArialSweepAttack(void)
{
	//重力を一時的になくす
	unit_.isGravity_ = false;
	unit_.yAccel_ = 0;
	//移動できなくする
	isMove_ = false;

	arialSweep_->Update(&mPos_);
	//描画時のずれを補正
	mapMousePos_.x = mPos_.x + ((Application::MAIN_SCREEN_SIZE_X - Application::SCREEN_SIZE_X) / 2);
	mapMousePos_.y = mPos_.y + ((Application::MAIN_SCREEN_SIZE_Y - Application::SCREEN_SIZE_Y) / 2);
	//プレイヤーの描画座標とマウスのマップ座標とのベクトルを求める
	Vector2F vec = GetMoveVec(unit_.disppos_, { (float)mapMousePos_.x,(float)mapMousePos_.y });
	arialSweepCounter_++;
	if (arialSweepCounter_ < 15) {
		unit_.nextpos_ += vec * 2;
	}
	else {
		unit_.yAccel_ = 0;		//かかりすぎている重力をなくす
		//初期化
		unit_.isGravity_ = true;
		attackStat_ = ATTACK_STAT::E_ATTACK_STAT_NON;
		arialSweepCounter_ = 0;
		isMove_ = true;
	}
}

void Player::ProcessGuard(void)
{
	auto& ins = InputManager::GetInstance();
	perGuardKey_ = nowGuardKey_;
	nowGuardKey_ = ins.IsClickMouseRight();
	if (!perGuardKey_ && nowGuardKey_)guardStat_ = GUARD_STAT::E_GUARD_PER;

	switch (guardStat_)
	{
	case Player::GUARD_STAT::E_GUARD_PER:		//前硬直
		isMove_ = false;					//ガード中は動けない
		if (perStiffness_ <= GUARD_PER_TIME) {
			perStiffness_++;
			break;
		}
		else {
			guardStat_ = GUARD_STAT::E_GUARD;	//ガードに遷移
		}
	case Player::GUARD_STAT::E_GUARD:
		if (!nowGuardKey_ && isGuard_) {
			guardStat_ = GUARD_STAT::E_GUARD_POST;		//後硬直へ遷移
			isGuard_ = false;
		}
		else {
			Guard();
			break;
		}
	case Player::GUARD_STAT::E_GUARD_POST:		//後硬直
		//猶予カウント中
		if (guardKeyUpBuffer_ < GUARD_JUST_TIME) {			//ジャストガード判定処理中
			JustGuard();
			guardKeyUpBuffer_++;
		}
		if (postStiffness_ < GUARD_POST_TIME) {				//後硬直中
			postStiffness_++;
		}
		else {									//後硬直終了
			//初期化
			perStiffness_ = 0;
			guardKeyUpBuffer_ = 0;
			postStiffness_ = 0;
			guardMaxCounter_ = 0;
			isMove_ = true;
			guardStat_ = GUARD_STAT::E_GUARD_NON;	//非ガード状態へ遷移
		}
		break;
	}
}

void Player::Guard(void)
{
	auto& ins = InputManager::GetInstance();
	guardMaxCounter_++;
	isGuard_ = true;
	ProcessEvasion();


	if (guardMaxCounter_ > GUARD_TIME_MAX) {
		guardStat_ = GUARD_STAT::E_GUARD_POST;
		guardKeyUpBuffer_ = GUARD_JUST_TIME;//最大までガードした場合
		//ジャストガードは発生しない
		isGuard_ = false;
	}
}

void Player::JustGuard(void)
{
	//	SceneManager::GetInstance().Slow();
	postStiffness_ = GUARD_POST_TIME;		//ジャストガード成功時後硬直削除
}




void Player::AnimationUpdate(void)
{
	if (isJump_) {
		//ジャンプ中
		motionType_ = MOTION_TYPE::E_MOTION_JUMP;
		if (unit_.yAccel_ > 0.0f)motionType_ = MOTION_TYPE::E_MOTION_FALL;
	}
	if (isEvasion_) {
		motionType_ = MOTION_TYPE::E_MOTION_EVASION;
	}

	animCounter_ += 0.5;
	if (animCounter_ >= image_[(int)motionType_].size()) {
		animCounter_ = (animLoop_) ? 0.0f : image_[(int)motionType_].size() - 1;
	}
}

void Player::LoadPlayerImage(void)
{
	std::string basePath = Application::PATH_PLAYER;

	int motion = 0;

	//待機状態の画像を読み込み-----------------------------------------------
	motion = (int)MOTION_TYPE::E_MOTION_IDLE;

	int idleLoad[IDLE_LOAD_NUM];

	LoadDivGraph((basePath + "Idle.png").c_str(),
		IDLE_LOAD_NUM, IDLE_LOAD_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y,idleLoad);

	image_[motion].insert(image_[motion].end(), idleLoad, idleLoad + IDLE_LOAD_NUM);
	//-----------------------------------------------------------------------

	//走り状態の画像を読み込み-----------------------------------------------
	motion = (int)MOTION_TYPE::E_MOTION_RUN;

	int runLoad[RUN_LOAD_NUM];

	LoadDivGraph((basePath + "Run.png").c_str(),
		RUN_LOAD_NUM, RUN_LOAD_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y, runLoad);

	image_[motion].insert(image_[motion].end(), runLoad, runLoad + RUN_LOAD_NUM);
	//-----------------------------------------------------------------------

	//ジャンプ状態の画像を読み込み-------------------------------------------
	motion = (int)MOTION_TYPE::E_MOTION_JUMP;

	int jumpLoad[JUMP_LOAD_NUM];

	LoadDivGraph((basePath + "Jump.png").c_str(),
		JUMP_LOAD_NUM, JUMP_LOAD_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y, jumpLoad);

	image_[motion].insert(image_[motion].end(), jumpLoad, jumpLoad + JUMP_LOAD_NUM);
	//-----------------------------------------------------------------------

	//落下状態の画像を読み込み-----------------------------------------------
	motion = (int)MOTION_TYPE::E_MOTION_FALL;

	int fallLoad[FALL_LOAD_NUM];

	LoadDivGraph((basePath + "Fall.png").c_str(),
		FALL_LOAD_NUM, FALL_LOAD_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y, fallLoad);
		
	image_[motion].insert(image_[motion].end(), fallLoad, fallLoad + JUMP_LOAD_NUM);
	//-----------------------------------------------------------------------

	//回避状態の画像を読み込み-----------------------------------------------
	motion = (int)MOTION_TYPE::E_MOTION_EVASION;

	int evasionlLoad[EVASION_LOAD_NUM];

	LoadDivGraph((basePath + "Roll.png").c_str(),
		EVASION_LOAD_NUM, EVASION_LOAD_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y, evasionlLoad);

	image_[motion].insert(image_[motion].end(), evasionlLoad, evasionlLoad + EVASION_LOAD_NUM);
	//-----------------------------------------------------------------------
}


void Player::DrawPlayer(std::vector<int> modelId)
{
	//プレイヤーの向き
	bool isLeft = true;
	if (playerDir_ == AsoUtility::DIRECTION::E_DIR_RIGHT) isLeft = false;



	DrawRotaGraph(unit_.disppos_.x, unit_.disppos_.y - SIZE_Y / 2,
		SIZE_SCALE, 0, modelId[(int)animCounter_], true, isLeft);
}



void Player::SetDrawPlayer(void)
{
	//if (isJump_) {
	//	//ジャンプ中
	//	motionType_ = MOTION_TYPE::E_MOTION_JUMP;
	//	if (unit_.yAccel_ > 0.0f)motionType_ = MOTION_TYPE::E_MOTION_FALL;
	//}
	//if (isEvasion_) {
	//	motionType_ = MOTION_TYPE::E_MOTION_EVASION;
	//}
	if (!(motionType_ == MOTION_TYPE::E_MOTION_DAMAGE)) {
		//現在のモーション
		int nowMotion = (int)motionType_;
		DrawPlayer(image_[nowMotion]);
	}
}




