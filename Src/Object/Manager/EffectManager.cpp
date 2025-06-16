#include "EffectManager.h"

EffectManager* EffectManager::instance_ = nullptr;

EffectManager::EffectManager(void) {}
EffectManager::~EffectManager(void) {}

void EffectManager::AddEffect( std::unique_ptr<EffectBase> effect, const Vector2F* generatePos)
{
    effect->SetPos(*generatePos);
    effects_.emplace_back(std::move(effect));
}


void EffectManager::Init()
{
    for (auto& effect : effects_) {
        effect->Init();
    }
}

void EffectManager::Update(void)
{
    for (auto& effect : effects_) {
        effect->Update();
    }
    // isActive_がfalseのエフェクトを削除
    effects_.erase(
        std::remove_if(effects_.begin(), effects_.end(),
            [](const std::unique_ptr<EffectBase>& effect) {
                return !effect->IsActive();
            }),
        effects_.end()
    );
}

void EffectManager::Draw()
{
    for (auto& effect : effects_) {
        effect->Draw();
    }
}

void EffectManager::Release()
{
    for (auto& effect : effects_) {
        effect->Release();
    }
    effects_.clear();
}
