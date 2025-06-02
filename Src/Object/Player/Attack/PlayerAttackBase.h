#pragma once
#include <vector>
#include "../../UnitBase.h"


class PlayerAttackBase :
    public UnitBase
{
public:
	PlayerAttackBase();
	~PlayerAttackBase();

	virtual void Init(Vector2F* pos);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);

	//派生クラスオブジェクトの構造体情報を取得
	virtual const std::vector<Base> GetStruct(void)const;


protected:

	Base attackObj_;

	Vector2F* playerPos_;

	//更新処理に使うカウンター
	int attackCounter_;

	//攻撃終了
	bool isattackEnd_;


};

