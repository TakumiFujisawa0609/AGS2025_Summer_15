#pragma once
#include "EffectBase.h"
class EffectTakeDrop :
    public EffectBase
{
public:
    static constexpr int LIFE_TIME = 120;        //生存フレーム
    static constexpr int SHOW_TIME = 60;        //エフェクトを見せるフレーム

    EffectTakeDrop();
    ~EffectTakeDrop();

    // 更新
    void Update(Vector2F* playerPos, Vector2F* generatePos);
    // 描画
    void Draw(void) override;
    // 解放
    void Release(void) override;
protected:
    // 画像やモデルなどのロード
    void Load(void) override;
    // パラメータ設定
    void SetParam(void) override;
};

