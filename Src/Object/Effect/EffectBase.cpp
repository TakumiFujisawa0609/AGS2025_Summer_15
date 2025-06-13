#include "EffectBase.h"

EffectBase::EffectBase()
{
}

EffectBase::~EffectBase()
{
}

void EffectBase::Init(void)
{
}

void EffectBase::Init(EFFECT_TYPE type)
{
    type_ = type;
    isActive_ = true;
    // 画像やモデルなどのロード
    Load();
    // パラメータ設定
    SetParam();
}

void EffectBase::Update(void)
{
    // エフェクトが無効なら何もしない
    if (!isActive_) return;


    // 寿命が設定されていて、経過フレームが寿命を超えたら無効化
    if (lifeTime_ > 0 && currentFrame_ >= lifeTime_) {
        isActive_ = false;
    }
    // 経過フレームをカウント
    currentFrame_++;
}

void EffectBase::Draw(void)
{
}

void EffectBase::Release(void)
{
}
