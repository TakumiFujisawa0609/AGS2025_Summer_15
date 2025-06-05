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
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;


	//派生クラスオブジェクトの構造体情報を取得
	virtual const std::vector<Base> Get(void)const;


protected:

	Base obj_;

	Vector2F* pMovePos_;
	Vector2F* pDrawPos_;
	AsoUtility::DIRECTION* direction_;
	float* pSpeed_;

	//更新処理に使うカウンター
	int attackCounter_;

	//攻撃終了
	bool isattackEnd_;


};

