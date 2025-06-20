#pragma once
#include"../UnitBase.h"
#include"../../Common/Vector2.h"

class UiBase:
    public UnitBase
{
public:
    // コンストラクタ
    UiBase();
    UiBase(Vector2F*generation);
    // デストラクタ
    virtual ~UiBase();

    // 初期化
    void Init(void);
    // 更新
    virtual void Update(void);
    // 描画
    virtual void Draw(void);
    // 解放
    virtual void Release(void);

protected:
    // 画像やモデルなどのロード(純粋仮想関数)
    virtual void Load(void) = 0;
    // パラメータ設定(純粋仮想関数)
    virtual void SetParam(void) = 0;
};
