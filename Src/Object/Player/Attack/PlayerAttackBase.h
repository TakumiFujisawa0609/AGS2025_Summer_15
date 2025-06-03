#pragma once
#include <vector>
#include "../../UnitBase.h"


class PlayerAttackBase :
    public UnitBase
{
public:
	PlayerAttackBase();
	~PlayerAttackBase();

	void Init(void)override;
	virtual void Init(Vector2F* movePos,Vector2F*drawPos);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);

	//派生クラスオブジェクトの構造体情報を取得
	virtual const std::vector<Base> GetStruct(void)const;


protected:

	Base attackObj_;

	Vector2F* pMovePos_;
	Vector2F* pDrawPos_;
	float* pSpeed_;

	//更新処理に使うカウンター
	int attackCounter_;

	//攻撃終了
	bool isattackEnd_;


};

