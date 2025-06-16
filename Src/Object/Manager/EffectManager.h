#pragma once
#include <memory>
#include<map>
#include "../Effect/EffectBase.h"
class EffectBase;
class EffectTakeDrop;

class EffectManager
{
public:
    // シングルトン（生成・取得・削除）
    static void CreateInstance(void) { if (instance_ == nullptr) { instance_ = new EffectManager(); } };
    static EffectManager* GetInstance(void) { return instance_; };
    static void DeleteInstance(void) { if (instance_ != nullptr) { delete instance_; instance_ = nullptr; } }

    // エフェクト追加（ID指定）
    void AddEffect(std::unique_ptr<EffectBase>effect, const Vector2F* generatePos);

    // 全エフェクトの更新・描画・解放
    void Init(void);
    void Update(void);
    void Draw(void);
    void Release(void);


private:
    // デフォルトコンストラクタをprivateにして、外部から生成できない様にする
    EffectManager(void);
    // デストラクタも同様
    ~EffectManager(void);

    // コピー・ムーブ操作を禁止
    EffectManager(const EffectManager&) = delete;
    EffectManager& operator=(const EffectManager&) = delete;
    EffectManager(EffectManager&&) = delete;
    EffectManager& operator=(EffectManager&&) = delete;
    static EffectManager* instance_;
    std::vector<std::unique_ptr<EffectBase>>effects_;

    Vector2F generatePos_;      //生成用座標
};