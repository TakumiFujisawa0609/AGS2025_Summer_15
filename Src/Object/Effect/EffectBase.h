#pragma once
#include "../UnitBase.h"
#include"../../Common/Vector2.h"

class EffectBase :
    public UnitBase
{
public:
    //エフェクト種別
    enum class EFFECT_TYPE
    {
        TAKE_DROP,
    };

    // コンストラクタ
    EffectBase();
    EffectBase(Vector2F* generation);
    // デストラクタ
    virtual ~EffectBase();

    // 初期化
     void Init(void);
    // 更新
    virtual void Update(void);
    // 描画
    virtual void Draw(void);
    // 解放
    virtual void Release(void);
    bool IsActive() const { return isActive_; }  

protected:

    // エフェクトの寿命（フレーム数）
    int lifeTime_ = 0;
    // 現在の経過フレーム
    int currentFrame_ = 0;
    // エフェクトの有効フラグ
    bool isActive_ = true;

    // 画像やモデルなどのロード(純粋仮想関数)
    virtual void Load(void) = 0;
    // パラメータ設定(純粋仮想関数)
    virtual void SetParam(void) = 0;
};

