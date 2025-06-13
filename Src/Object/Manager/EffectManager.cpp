#include "EffectManager.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}


void EffectManager::AddEffect(int id, std::shared_ptr<EffectBase> effect)
{
    effects_[id] = effect;
}

void EffectManager::Init()
{
}

void EffectManager::Update()
{
    for (auto& pair : effects_)
    {
        if (pair.second) 
            pair.second->Update();
    }
}

void EffectManager::Draw()
{
    for (auto& pair : effects_)
    {
        if (pair.second) pair.second->Draw();
    }
}

void EffectManager::Release()
{
    for (auto& pair : effects_)
    {
        if (pair.second) pair.second->Release();
    }
    effects_.clear();
}

void EffectManager::RemoveEffect(int id)
{
    effects_.erase(id);
}