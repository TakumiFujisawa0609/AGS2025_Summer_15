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
    // デストラクタ
    virtual ~EffectBase();

    // 初期化
     void Init(void);
     void Init(EFFECT_TYPE type);
    // 更新
     void Update(void);
    // 描画
    virtual void Draw(void);
    // 解放
    virtual void Release(void);

protected:
    EFFECT_TYPE type_;

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

