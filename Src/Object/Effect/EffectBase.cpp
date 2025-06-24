#include "EffectBase.h"

EffectBase::EffectBase()
{
}

EffectBase::EffectBase(Vector2F* generation)
{
    unit_.pos_ = *generation;
}

EffectBase::~EffectBase()
{
}

void EffectBase::Init()
{
    isActive_ = false;
    // 画像やモデルなどのロード
    Load();
    // パラメータ設定
    SetParam();
}

void EffectBase::Update(void)
{
    // エフェクトが無効なら何もしない
    if (isActive_==false) return;

    // 寿命が設定されていて、経過フレームが寿命を超えたら無効化
    if (currentFrame_ >= lifeTime_) {
         isActive_ = false;
    }
    // 経過フレームをカウント
    currentFrame_++;
}

void EffectBase::Draw(void)
{
    if (!isActive_)return;
}

void EffectBase::Release(void)
{
}
