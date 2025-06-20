#include "UiBase.h"

UiBase::UiBase()
{
}

UiBase::UiBase(Vector2F* generation)
{
    unit_.pos_ = *generation;

}

UiBase::~UiBase()
{
}

void UiBase::Init(void)
{
    unit_.isAlive_ = true;
    // 画像やモデルなどのロード
    Load();
    // パラメータ設定
    SetParam();
}

void UiBase::Update(void)
{
}

void UiBase::Draw(void)
{
}

void UiBase::Release(void)
{
}
