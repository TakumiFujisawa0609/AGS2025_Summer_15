#include"BPAttack.h"
#include"../Player.h"
#include"ThrowBamboo.h"
#include"GrowBamboo.h"
#include"Firecracker.h"

BPAttack::BPAttack() : PlayerAttackBase()
{
}

BPAttack::~BPAttack()
{
}


void BPAttack::Init(int image)
{
	this->image_ = image;
	if (attack_) {
		attack_->Init(image);
	}
}

void BPAttack::Update(void)
{
	if (attack_) {
		attack_->Update();
	}
	// オブジェクトが生存していなければ処理しない
	if (!obj_.isAlive_) return;

	// 生存カウンタまたはヒット回数が0以下なら消滅
	if (aliveCounter_-- <= 0 || aliveHit_ <= 0) obj_.isAlive_ = false;

	// 方向に応じて座標を移動
	switch (dir_)
	{
	case AsoUtility::DIRECTION::E_DIR_RIGHT:
		obj_.pos_.x += DEFAULT_SPEED / bp_;
		break;
	case AsoUtility::DIRECTION::E_DIR_LEFT:
		obj_.pos_.x -= DEFAULT_SPEED / bp_;
		break;
	}

	// 表示座標を更新
	ChangeDispPos();

	// 画面外に出たら消滅
	if (obj_.disppos_.x < -DEFAULT_SIZE_X * bp_ || obj_.disppos_.x > Application::SCREEN_SIZE_X + DEFAULT_SIZE_X * bp_)
		obj_.isAlive_ = false;
}

void BPAttack::Draw(void)
{
	if (!obj_.isAlive_)return;

	if (attack_) {
		attack_->Draw();
	}
	DrawRotaGraph(obj_.disppos_.x, obj_.disppos_.y, (float)bp_, 0, image_, true);

}

void BPAttack::Release(void)
{
	if (attack_) {
		attack_->Release();
	}
}


// 攻撃タイプを切り替えるメソッド
void BPAttack::SetAttackType(BP_ATTACK_TYPE type)
{
	bpAttackType_ = type;
	if (attack_) {
		delete attack_;
		attack_ = nullptr;
	}
}


void BPAttack::On(Vector2F pPos, AsoUtility::DIRECTION dir, int bp)
{
	// 攻撃オブジェクトを有効化し、初期パラメータを設定
	obj_.isAlive_ = true;

	this->dir_ = dir;

	obj_.pos_ = pPos;
	// 方向に応じて初期位置を調整
	obj_.pos_.x += (dir == AsoUtility::DIRECTION::E_DIR_RIGHT) ? Player::SIZE_X : -Player::SIZE_X;

	aliveCounter_ = ALIVE_TIME; // 生存時間カウンタ初期化
	aliveHit_ = bp;             // ヒット回数初期化

	this->bp_ = bp;             // BP値設定

	obj_.radius_ = DEFAULT_RADIUS * bp; // 半径設定

	obj_.size_ = { DEFAULT_SIZE_X * bp, DEFAULT_SIZE_Y * bp }; // サイズ設定
	if (attack_) {
		delete attack_;
		attack_ = nullptr;
	}
	switch (bpAttackType_) {
	case BP_ATTACK_TYPE::THROW_BAMBOO:
		attack_ = new ThrowBamboo();
		break;
	case BP_ATTACK_TYPE::GROW_BAMBOO:
		attack_ = new GrowBamboo();
		break;
	case BP_ATTACK_TYPE::FIRECRACKER:
		attack_ = new Firecracker();
		break;
	}
	if (attack_) {
		attack_->Init(image_);
		//	attack_->On(pPos, dir, bp);
	}
}

