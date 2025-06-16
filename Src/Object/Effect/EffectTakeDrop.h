#pragma once
#include "EffectBase.h"
class EffectTakeDrop :
    public EffectBase
{
public:
    static constexpr int LIFE_TIME = 60;        //生存フレーム
    //static constexpr int SHOW_TIME = 60;        //エフェクトを見せるフレーム
    EffectTakeDrop();
    EffectTakeDrop(Vector2F* generation);
    ~EffectTakeDrop()override;

    void Init(void);
    // 更新
    void Update(void);
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

