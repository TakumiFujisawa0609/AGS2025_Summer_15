#include<string>

#include "Player.h"
#include"../../Manager/InputManager.h"
#include"../../Application.h"
#include"../../Manager/Camera.h"
#include"../../Manager/Collision.h"
#include"../../Manager/SceneManager.h"
#include"../Stage/Stage.h"
#include"../../Scene/TutorialScene.h"



Player::Player()
{
	LoadPlayerImage();
}

Player::~Player()
{
}

void Player::Init()
{
	// 定数値を設定
	unit_.size_ = { SIZE_X,SIZE_Y };
	unit_.speed_ = RUN_SPEED;

	// 変数の初期化
	unit_.pos_ = { 500.0f,500.0f };
	unit_.isAlive_ = true;
	unit_.hp_ = HP_MAX;



	// アニメーションカウンター
	animeCounter_ = 0;
	animeInterval_ = 0;


	// 向き
	dir_ = AsoUtility::DIRECTION::E_DIR_RIGHT;

	// ジャンプ関係
	for (int i = 0; i < JUMP_NUM; i++) {
		isJump_[i] = false;
		jumpKeyCounter_[i] = 0;
	}

	// 攻撃関係
	defaultAttack_ = new Default(&unit_.pos_, &dir_);
	defaultAttack_->Init();

	for (int i = 0; i < ATTACK::MAX; i++) { isAttack_[i] = false; }
	attack_ = NON;
	attackKeyCounter_ = 0;

	// 特殊攻撃関係
	BambooImg_ = LoadGraph("Data/Image/Player/The_Bamboo.png");


	bp_ = 100;
	bpConsCounter_ = 10.0f;

	//ガード関係
	// ガード関係
	guardCounter_ = 0;
	isGuard_ = false;
	isJustGuard_ = false;
	perGuardKey_ = false;
	nowGuardKey_ = false;

	// 回避関係
	evasionCounter_ = 0;

	evasionPossiFlg_ = true;

	// ダメージ関係
	knockBack_ = false;

	//状態
	ChangeState(Player::STATE::MOVE);

	// モーション
	ChangeMotion(MOTION::IDLE);
}

void Player::Update()
{
	if (unit_.inviCounter_ > 0)unit_.inviCounter_--;

	JoyPadInputManager();

	StateManager();

	Animation();

	(this->*stateFuncPtr)();

	for (auto t : BpAtIns_) {
		t->Update();
	}

	UnitBase::Update();
}

void Player::Draw()
{
	if (unit_.isAlive_ && (unit_.inviCounter_ / 5) % 2 == 0) {

		DrawPlayer();

		defaultAttack_->Draw();
	}
	for (auto t : BpAtIns_) {
		t->Draw();
	}

	DrawHpBarFixedSize(330, 290, 800,330, unit_.hp_, HP_MAX,RGB(0,255,0));
	DrawHpBarFixedSize(330, 335, 500, 350, bp_, BP_MAX, RGB(0, 0, 255));
}

void Player::Release()
{
	for (auto b : BpAtIns_) {
		b->Release();
		delete b;
	}
	BpAtIns_.clear();
	DeleteGraph(BambooImg_);

	defaultAttack_->Release();
	delete defaultAttack_;
	//画像解放
	for (int i = 0; i < (int)MOTION::MAX; i++) {
		for (auto id : image_[i]) {
			DeleteGraph(id);
		}
		image_[i].clear();
	}
}



// 状態遷移を一元管理する
void Player::StateManager(void)
{
	//各状態から遷移可能にさせたい状態の、遷移条件関数 ( DoState～～() ) を呼び出す
	switch (state_)
	{
	case Player::STATE::MOVE:
		DoStateAttack();
		DoStateBPAttack();
		DoStateEvasion();
		DoStateGuard();
		break;
	case Player::STATE::ATTACK:
		break;
	case Player::STATE::GUARD:

		break;
	case Player::STATE::EVASION:

		break;
	case Player::STATE::DAMAGE:
		break;
	}

}

//各状態に遷移する条件--------------------------------------------------------------------------

// それぞれの状態で使うキーの中のいずれかのダウントリガーでその状態に遷移

//移動状態
void Player::DoStateMove()
{
	auto& ins = InputManager::GetInstance();


	if (ins.IsTrgDown(KEY_INPUT_W) ||
		ins.IsTrgDown(KEY_INPUT_A) ||
		ins.IsTrgDown(KEY_INPUT_S) ||
		ins.IsTrgDown(KEY_INPUT_D) ||
		ins.IsTrgDown(KEY_INPUT_SPACE)) {

		ChangeState(Player::STATE::MOVE);
	}

	if ((!prevLeftKey_ && nowLeftKey_) ||
		(!prevRightKey_ && nowRightKey_) ||
		(!prevJumpKey_ && nowJumpKey_)) {
		ChangeState(Player::STATE::MOVE);
	}

}

// 攻撃状態
void Player::DoStateAttack()
{
	auto& ins = InputManager::GetInstance();
	int input = GetJoypadInputState(DX_INPUT_PAD1);


	if (!(ins.IsTrgDown(KEY_INPUT_J))&& !(!prevAttackKey_ && nowAttackKey_)) return;

	// 攻撃状態に遷移する
	ChangeState(Player::STATE::ATTACK);

	// 最終段までいっている または 前の段の攻撃から一定時間過ぎていたら フラグリセット
	if ((isAttack_[ATTACK::MAX - 1]) || (attackKeyCounter_ > INPUT_ATTACK_FRAME)) {
		for (int i = 0; i < ATTACK::MAX; i++) { isAttack_[i] = false; }
	}

	// １段目から探索して適切な段数をattack_に代入する
	for (int i = 0; i < ATTACK::MAX; i++) {
		if (!isAttack_[i]) {

			isAttack_[i] = true;

			attackKeyCounter_ = 0;

			attack_ = (ATTACK)i;

			break;
		}
	}

}

// 特殊攻撃状態
void Player::DoStateBPAttack(void)
{
	auto& ins = InputManager::GetInstance();
	if (ins.IsNew(KEY_INPUT_H)||nowBambooKey_) {
		bpConsCounter_+=0.25;
		if (bpConsCounter_ > bp_)bpConsCounter_ = bp_;
		if (bpConsCounter_ > MAX_BP_CONS)bpConsCounter_ = MAX_BP_CONS;
	}

	if ((ins.IsTrgUp(KEY_INPUT_H)) || (prevBambooKey_ && !nowBambooKey_)) {
		ChangeState(Player::STATE::BP_ATTACK);
	}
}

// ガード状態
void Player::DoStateGuard()
{
	auto& ins = InputManager::GetInstance();
	perGuardKey_ = nowGuardKey_;
	nowGuardKey_ = ins.IsNew(KEY_INPUT_L);
	if (nowGuardKey_ && (perGuardKey_ != nowGuardKey_)) {
		ChangeState(Player::STATE::GUARD);
		ChangeMotion(MOTION::GUARD_PER,false);
		guardState_ = Player::GUARD_STATE::GUARD_PER;
		guardCounter_ = GUARD_PER_RECOVERY_FRAME;
		isJustGuard_ = true;
	}
}
// 回避状態
void Player::DoStateEvasion()
{
	auto& ins = InputManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_K)&&evasionPossiFlg_) {
		ChangeState(Player::STATE::EVASION);
		evasionPossiFlg_ = false;
	}
}

//----------------------------------------------------------------------------------------------

// 状態変更
void Player::ChangeState(STATE st)
{
	unit_.isGravity_ = true;
	defaultAttack_->Off();			
	guardState_ = Player::GUARD_STATE::GUARD_POST; 

	switch (st)
	{
	case Player::STATE::MOVE:
		state_ = Player::STATE::MOVE;
		stateFuncPtr = &Player::Move;
		break;
	case Player::STATE::ATTACK:
		state_ = Player::STATE::ATTACK;
		stateFuncPtr = &Player::Attack;
		break;
	case Player::STATE::BP_ATTACK:
		state_ = Player::STATE::BP_ATTACK;
		stateFuncPtr = &Player::BambooAttack;
		break;
	case Player::STATE::GUARD:
		state_ = Player::STATE::GUARD;
		stateFuncPtr = &Player::Guard;
		break;
	case Player::STATE::EVASION:
		state_ = Player::STATE::EVASION;
		stateFuncPtr = &Player::Evasion;
		break;
	case Player::STATE::DAMAGE:
		state_ = Player::STATE::DAMAGE;
		stateFuncPtr = &Player::Damage;
		break;
	}
}

// 関数ポインタに格納する状態ごとの関数---------------------------------------------------------------

//移動状態
void Player::Move()
{
	Run();
	Jump();
	if (unit_.yAccel_ > 0.0f)ChangeMotion(MOTION::FALL);

	if (attackKeyCounter_ <= INPUT_ATTACK_FRAME) attackKeyCounter_++;
}

// 攻撃状態
void Player::Attack()
{
	switch (attack_)
	{
	case Player::FIRST:
		// モーション更新
		ChangeMotion(MOTION::FIRST_ATTACK, false);
		break;
	case Player::SECONDE:
		// モーション更新
		ChangeMotion(MOTION::SECOND_ATTACK, false);
		break;
	}

	defaultAttack_->Off();

	if (GetAnimeRatio() > 0.4f && GetAnimeRatio() < 0.6f) {
		defaultAttack_->On();
	}

	defaultAttack_->Update();
}

// 特殊攻撃状態
void Player::BambooAttack(void)
{
	bp_ -= (int)bpConsCounter_;

	bool recycll = false;

	for (int i = 0; i < BpAtIns_.size(); i++) {
		if (!BpAtIns_[i]->GetObj().isAlive_) {
			BpAtIns_[i]->On(unit_.pos_, dir_, bpConsCounter_);
			recycll = true;
			break;
		}
	}
	
	if (!recycll) {
		BpAtIns_.emplace_back(new BPAttack());
		BpAtIns_[BpAtIns_.size()-1]->Init(BambooImg_);
		BpAtIns_[BpAtIns_.size() - 1]->On(unit_.pos_, dir_, bpConsCounter_);
	}

	bpConsCounter_ = 10.0f;

	ChangeState(Player::STATE::MOVE);
}

// ガード状態
void Player::Guard()
{
	auto& ins = InputManager::GetInstance();
	perGuardKey_ = nowGuardKey_;
	nowGuardKey_ = ins.IsNew(KEY_INPUT_L);

	guardCounter_--;
	switch (guardState_)
	{
	case Player::GUARD_STATE::GUARD_PER:
		//前硬直が終了したらガードに遷移
		if (guardCounter_ <= 0) {
			isJustGuard_ = false;
			isGuard_ = true;
			guardCounter_ = GUARD_FRAME;
			guardState_ = Player::GUARD_STATE::GUARD;
			ChangeMotion(Player::MOTION::GUARD);
		}
		//ガードキーを離したらジャストガードに遷移
		if (perGuardKey_ != nowGuardKey_) {
			isGuard_ = false;
			isJustGuard_ = true;
			guardCounter_ = GUARD_JUST_FRAME;
			guardState_ = Player::GUARD_STATE::GUARD_JUST;
		}
		break;
	case Player::GUARD_STATE::GUARD:
		//ガード時間が終了したら後硬直に遷移
		if (guardCounter_<=0) {
			isGuard_ = false;
			guardCounter_ = GUARD_POST_RECOVERY_FRAME;
			guardState_ = Player::GUARD_STATE::GUARD_POST;
			ChangeMotion(MOTION::GUARD_POST, false);
		}
		//ガードキーを離したらジャストガードに遷移
		if (perGuardKey_ != nowGuardKey_) {
			isGuard_ = false;
			isJustGuard_ = true;
			guardCounter_ = GUARD_JUST_FRAME;
			guardState_ = Player::GUARD_STATE::GUARD_JUST;
		}
		break;
	case Player::GUARD_STATE::GUARD_JUST:
		//ジャストガードが終了したら後硬直に遷移
		if (guardCounter_ <= 0) {
			isJustGuard_ = false;
			guardCounter_ = GUARD_POST_RECOVERY_FRAME;
			guardState_ = Player::GUARD_STATE::GUARD_POST;
			ChangeMotion(MOTION::GUARD_POST, false);
		}
		break;
	case Player::GUARD_STATE::GUARD_POST:
		//後硬直が終了したら動けるようにする
		if (guardCounter_ <= 0) {
			//初期化
			guardCounter_ = 0;
			isGuard_ = false;
			isJustGuard_ = false;
			guardState_ = Player::GUARD_STATE::GUARD_PER;
			//ChangeState(Player::STATE::MOVE);
		}
		break;
	}

}

// 回避状態
void Player::Evasion()
{
	ChangeMotion(MOTION::EVASION);

	unit_.isGravity_ = false;

	unit_.yAccel_ = 0.0f;
	unit_.nextpos_.x += (dir_ == AsoUtility::DIRECTION::E_DIR_LEFT) ? -(EVASION_SPEED) : EVASION_SPEED;

	evasionCounter_++;
	if (evasionCounter_ > EVASION_TIME) {
		evasionCounter_ = 0;
		unit_.isGravity_ = true;
		ChangeState(Player::STATE::MOVE);
	}
}

// ダメージ処理
void Player::Damage(void)
{
	if (!knockBack_)ChangeState(Player::STATE::MOVE);

	ChangeMotion(Player::MOTION::DAMAGE);

	if (knockBackDir_ == AsoUtility::DIRECTION::E_DIR_LEFT) 
	{
		unit_.nextpos_.x -= KNOCK_SPEED;
	}
	else if (knockBackDir_==AsoUtility::DIRECTION::E_DIR_RIGHT)
	{
		unit_.nextpos_.x += KNOCK_SPEED;
	}

}

//----------------------------------------------------------------------------------------------------




//状態ごとの関数内で使う機能をまとめた関数---------------------------------------------------------------------------------------



//移動処理関係----------------------------------------------------------------------
void Player::Run()
{
	auto& ins = InputManager::GetInstance();

	bool isMove = false;

	if (ins.IsNew(KEY_INPUT_A) || ins.IsNew(KEY_INPUT_LEFT) || nowLeftKey_) {
		unit_.nextpos_.x -= RUN_SPEED;
		dir_ = AsoUtility::DIRECTION::E_DIR_LEFT;
		isMove = true;
	}
	if (ins.IsNew(KEY_INPUT_D) || ins.IsNew(KEY_INPUT_RIGHT) || nowRightKey_) {
		unit_.nextpos_.x += RUN_SPEED;
		dir_ = AsoUtility::DIRECTION::E_DIR_RIGHT;
		isMove = true;
	}

	// モーション更新
	if (isMove)ChangeMotion(MOTION::RUN);
	else ChangeMotion(MOTION::IDLE);
}

void Player::Jump()
{
	auto& ins = InputManager::GetInstance();


	for (int i = 0; i < JUMP_NUM; i++) {

		// ダウントリガーでジャンプ開始
		if ((ins.IsTrgDown(KEY_INPUT_SPACE)) || (!prevJumpKey_ && nowJumpKey_))isJump_[i] = true;

		// ジャンプしていなかったらループから抜ける
		if (!isJump_[i])break;

		//ジャンプキーを離したら、ジャンプキー入力判定を終了
		if ((isJump_[i] && ins.IsTrgUp(KEY_INPUT_SPACE)) ||
			(prevJumpKey_ && !nowJumpKey_))jumpKeyCounter_[i] = INPUT_JUMPKEY_FRAME;

		//入力時間に応じてジャンプ量を変更する
		if (isJump_[i] && (ins.IsNew(KEY_INPUT_SPACE) || nowJumpKey_) && jumpKeyCounter_[i] < INPUT_JUMPKEY_FRAME) {
			//ジャンプキーの入力カウンターを増やす
			jumpKeyCounter_[i]++;

			//ジャンプ力を分配加算する
			unit_.yAccel_ = -(MAX_JUMP_POWER / (float)INPUT_JUMPKEY_FRAME);

			// その回のジャンプ処理をしたのでそれ以降のループに入らないようにする
			break;
		}
	}

	// モーション更新
	if (isJump_[0])ChangeMotion(MOTION::JUMP);
}


//-------------------------------------------------------------------移動処理ここまで




// 攻撃処理関係--------------------------------------------------------------------




//-------------------------------------------------------------------攻撃処理ここまで





// ガード処理関係--------------------------------------------------------------------

//-------------------------------------------------------------------ガード処理ここまで





// 回避処理関係--------------------------------------------------------------------

//-------------------------------------------------------------------回避処理ここまで


// ダメージ処理関係--------------------------------------------------------------------


//-------------------------------------------------------------------ダメージ処理ここまで

//-----------------------------------------------------------------------------------------------------------------------------





// 接地している時の数値の代入などをまとめた関数
void Player::IsGround(Collision::DIR dir)
{
	switch (dir)
	{
	case Collision::UP:
		//天井に衝突していたら行う処理

		unit_.yAccel_ = 0.0f;

		break;
	case Collision::DOWN:
		//地面に接地していたら行う処理

		unit_.yAccel_ = 0.0f;
		unit_.isGround_ = true;
		//unit_.isGravity_ = false;
		evasionPossiFlg_ = true;
		knockBack_ = false;

		for (int i = 0; i < JUMP_NUM; i++) {
			isJump_[i] = false;
			jumpKeyCounter_[i] = 0;
		}

		break;
	case Collision::LEFT:
		//左側の壁に衝突していたら行う処理

		unit_.xAccel_ = 0.0f;

		break;
	case Collision::RIGHT:
		//右側の壁に衝突していたら行う処理

		unit_.xAccel_ = 0.0f;

		break;
	}
}


void Player::LoadPlayerImage(void)
{
	std::string basePath = Application::PATH_PLAYER;

	int motion = 0;

	//待機状態の画像を読み込み-----------------------------------------------
	motion = (int)MOTION::IDLE;

	int idleLoad[IDLE_LOAD_NUM];

	LoadDivGraph((basePath + "Idle.png").c_str(),
		IDLE_LOAD_NUM, IDLE_LOAD_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y, idleLoad);

	image_[motion].insert(image_[motion].end(), idleLoad, idleLoad + IDLE_LOAD_NUM);
	//-----------------------------------------------------------------------

	//走り状態の画像を読み込み-----------------------------------------------
	motion = (int)MOTION::RUN;

	int runLoad[RUN_LOAD_NUM];

	LoadDivGraph((basePath + "Run.png").c_str(),
		RUN_LOAD_NUM, RUN_LOAD_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y, runLoad);

	image_[motion].insert(image_[motion].end(), runLoad, runLoad + RUN_LOAD_NUM);
	//-----------------------------------------------------------------------

	//ジャンプ状態の画像を読み込み-------------------------------------------
	motion = (int)MOTION::JUMP;

	int jumpLoad[JUMP_LOAD_NUM];

	LoadDivGraph((basePath + "Jump.png").c_str(),
		JUMP_LOAD_NUM, JUMP_LOAD_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y, jumpLoad);

	image_[motion].insert(image_[motion].end(), jumpLoad, jumpLoad + JUMP_LOAD_NUM);
	//-----------------------------------------------------------------------

	//落下状態の画像を読み込み------------------------------------------------------
	motion = (int)MOTION::FALL;

	int fallLoad[FALL_LOAD_NUM];

	LoadDivGraph((basePath + "Fall.png").c_str(),
		FALL_LOAD_NUM, FALL_LOAD_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y, fallLoad);

	image_[motion].insert(image_[motion].end(), fallLoad, fallLoad + JUMP_LOAD_NUM);
	//------------------------------------------------------------------------------

	//攻撃１段目状態の画像を読み込み-----------------------------------------------
	motion = (int)MOTION::FIRST_ATTACK;

	int FirstAttaclLoad[FIRST_ATTACK_LOAD_NUM];

	LoadDivGraph((basePath + "FirstAttack.png").c_str(),
		FIRST_ATTACK_LOAD_NUM, FIRST_ATTACK_LOAD_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y, FirstAttaclLoad);

	image_[motion].insert(image_[motion].end(), FirstAttaclLoad, FirstAttaclLoad + FIRST_ATTACK_LOAD_NUM);
	//-----------------------------------------------------------------------------

	//攻撃２段目状態の画像を読み込み-----------------------------------------------
	motion = (int)MOTION::SECOND_ATTACK;

	int SecondeAttaclLoad[SECONDE_ATTACK_LOAD_NUM];

	LoadDivGraph((basePath + "SecondeAttack.png").c_str(),
		SECONDE_ATTACK_LOAD_NUM, SECONDE_ATTACK_LOAD_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y, SecondeAttaclLoad);

	image_[motion].insert(image_[motion].end(), SecondeAttaclLoad, SecondeAttaclLoad + SECONDE_ATTACK_LOAD_NUM);
	//-----------------------------------------------------------------------------

	//被ダメ状態の画像を読み込み-----------------------------------------------
	motion = (int)MOTION::DAMAGE;

	int DamageLoad[DAMAGE_LOAD_NUM];

	LoadDivGraph((basePath + "Damage.png").c_str(),
		DAMAGE_LOAD_NUM, DAMAGE_LOAD_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y, DamageLoad);

	image_[motion].insert(image_[motion].end(), DamageLoad, DamageLoad + DAMAGE_LOAD_NUM);
	//-----------------------------------------------------------------------------

	// ガード状態の画像を読み込み--------------------------------------------------
	motion = (int)MOTION::GUARD_PER;
	int guardPerLoad[GUARD_PER_LOAD_NUM];
	LoadDivGraph((basePath+"GuardPer.png").c_str(),
		GUARD_PER_LOAD_NUM, GUARD_PER_LOAD_NUM,1,
		LOAD_SIZE_X, LOAD_SIZE_Y, guardPerLoad);
	image_[motion].insert(image_[motion].end(), guardPerLoad, guardPerLoad + GUARD_PER_LOAD_NUM);

	motion = (int)MOTION::GUARD;
	int GuardLoad[GUARD_LOAD_NUM];
	LoadDivGraph((basePath + "Guard.png").c_str(),
		GUARD_LOAD_NUM, GUARD_LOAD_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y, GuardLoad);
	image_[motion].insert(image_[motion].end(), GuardLoad, GuardLoad + GUARD_LOAD_NUM);

	motion = (int)MOTION::GUARD_POST;
	int guardPostLoad[GUARD_POST_LOAD_NUM];
	LoadDivGraph((basePath+"GuardPost.png").c_str(),
		GUARD_POST_LOAD_NUM, GUARD_POST_LOAD_NUM,1,
		LOAD_SIZE_X, LOAD_SIZE_Y, guardPostLoad);
	image_[motion].insert(image_[motion].end(), guardPostLoad, guardPostLoad + GUARD_POST_LOAD_NUM);
	//-----------------------------------------------------------------------------


	//回避状態の画像を読み込み-----------------------------------------------
	motion = (int)MOTION::EVASION;

	int evasionlLoad[EVASION_LOAD_NUM];

	LoadDivGraph((basePath + "Evasion.png").c_str(),
		EVASION_LOAD_NUM, EVASION_LOAD_NUM, 1,
		LOAD_SIZE_X, LOAD_SIZE_Y, evasionlLoad);

	image_[motion].insert(image_[motion].end(), evasionlLoad, evasionlLoad + EVASION_LOAD_NUM);
	//-----------------------------------------------------------------------
}

void Player::Animation()
{
	animeInterval_++;
	if (!(animeInterval_ > ANIMATION_SPEED))return;
	else animeInterval_ = 0;

	animeCounter_++;
	if (animeCounter_ >= image_[(int)motion_].size()) {
		if (animeLoop_) {
			animeCounter_ = 0;
		}
		else {
			ChangeMotion(MOTION::IDLE);
			ChangeState(Player::STATE::MOVE);
		}
	}
}


void Player::ChangeMotion(MOTION mo, bool loop)
{
	if (mo == motion_)return;

	motion_ = mo;
	animeCounter_ = 0;
	animeLoop_ = loop;

}


void Player::DrawPlayer(void)
{
	bool Trance = (dir_ == AsoUtility::DIRECTION::E_DIR_LEFT) ? true : false;
	DrawRotaGraphF(unit_.disppos_.x, unit_.disppos_.y - SIZE_Y / 2, SIZE_SCALE, 0, image_[(int)motion_][animeCounter_], true, Trance);
}

const float Player::GetAnimeRatio(void) const
{
	return ((float)animeCounter_ / (float)image_[(int)motion_].size());
}

void Player::JoyPadInputManager(void)
{
	int input = GetJoypadInputState(DX_INPUT_PAD1);

	prevJumpKey_ = nowJumpKey_;
	nowJumpKey_ = ((input & PAD_INPUT_A) == 0) ? false : true;

	prevLeftKey_ = nowLeftKey_;
	nowLeftKey_ = ((input & PAD_INPUT_LEFT) == 0) ? false : true;

	prevRightKey_ = nowRightKey_;
	nowRightKey_ = ((input & PAD_INPUT_RIGHT) == 0) ? false : true;

	prevAttackKey_ = nowAttackKey_;
	nowAttackKey_ = ((input & 0x40) == 0) ? false : true;

	prevBambooKey_ = nowBambooKey_;
	nowBambooKey_ = (((input & 0x200) == 0) && ((input & 0x80)==0)) ? false : true;
}



void Player::Hit(int damage, Vector2F bPos)
{
	if (guardState_ == GUARD_STATE::GUARD) {

		return;
	}
	else if (guardState_ == GUARD_STATE::GUARD_JUST||guardState_==GUARD_STATE::GUARD_PER) {
		SceneManager::GetInstance().SHAKE();
		SceneManager::GetInstance().Slow();
		unit_.inviCounter_ = 100;
		return;
	}


	ChangeState(Player::STATE::DAMAGE);

	unit_.hp_ -= damage;

	if (unit_.hp_ <= 0)unit_.isAlive_ = false;

	unit_.inviCounter_ = 100;

	unit_.yAccel_ = -(KNOCK_POWER);

	knockBack_ = true;
	knockBackDir_ = (unit_.pos_.x < bPos.x) ? AsoUtility::DIRECTION::E_DIR_LEFT : AsoUtility::DIRECTION::E_DIR_RIGHT;
}