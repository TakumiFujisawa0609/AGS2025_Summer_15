#pragma once
#include"../../Common/Vector2.h"

struct Base
{
	//変数
	bool isAlive_;			//生存判定(true=生存/false=死んでいる！！！)
	bool isDraw_;

	Vector2F pos_;			//ワールド座標
	Vector2F nextpos_;		//座標更新用変数
	Vector2F disppos_;		//マップ座標

	float xAccel_;			//横方向の移動量計算用変数
	float yAccel_;			//縦方向の移動量計算用変数

	bool isXAttenu;			//横軸加速度の減衰の有無(true = 有 / false = 無)
	bool isGravity_;		//重力をかけるかどうか(true = かける / false = かけない)
	bool isGround_;			//接地判定	(true = 接地している / false = 接地していない)

	bool isStageCollision_;	//ステージとの当たり判定を実行するかどうか　(true = する / false = しない)

	int hp_;				//ヒットポイント

	bool isInvincible_;		//無敵
	int inviCounter_;
	//パラメータ(定数扱い)
	float speed_;		//移動速度

	bool isCircle_;		//true=円形 false=矩形
	float radius_;		//半径
	Vector2F size_;		//大きさ
};
