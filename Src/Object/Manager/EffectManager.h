#pragma once
#include <memory>
#include<map>
#include "../Effect/EffectBase.h"
class EffectBase;
class EffectTakeDrop;

class EffectManager
{
public:
    EffectManager();
    ~EffectManager();


    // エフェクト追加（ID指定）
    void AddEffect(int id, std::shared_ptr<EffectBase> effect);

    // 全エフェクトの更新・描画・解放
    void Init(EffectBase::EFFECT_TYPE type);
    void Update();
    void Draw();
    void Release();

    // ID指定でエフェクト削除
    void RemoveEffect(int id);

private:
    std::map<int, std::shared_ptr<EffectBase>> effects_;
    EffectTakeDrop* takeDrop_;
};