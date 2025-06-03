#pragma once
#include"../Utility/AsoUtility.h"
#include"../Object/Stage/Stage.h"
#include"../Object/Common/Base.h"

class Collision
{
private:
	Collision();
	~Collision();
public:
	static void CreateInstance(void) { if (instance == nullptr)instance = new Collision(); instance->Init(); }
	static Collision& GetInstance(void) { return *instance; }
	static void DeleteInstance(void) { if (instance != nullptr)delete instance; instance = nullptr; }

	void Init();
	void SetStage(int map,int y,int x){ mapData_[y][x] = map; }

	enum DIR {
		UP,
		DOWN,
		LEFT,
		RIGHT,

		MAX
	};

	/// <summary>
	/// 指定した位置、サイズ、方向に基づいて、ステージ上の床や壁の座標（ライン）を取得
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="size">判定する範囲のサイズ</param>
	/// <param name="dir">探索する方向（UP, DOWN, LEFT, RIGHT のいずれか）</param>
	/// <returns>指定した方向における最も近い床または壁の座標（float値、ピクセル単位）。</returns>
	const float GetStageLine(const Vector2F& pos, const Vector2F& size, const DIR dir) const;


	/// <summary>
	/// 円形同士の当たり判定
	/// </summary>
	/// <param name="u1"></param>
	/// <param name="u2"></param>
	/// <returns></returns>
	const bool Circle(const Base& u1, const Base& u2)const;

	/// <summary>
	/// 矩形同士の当たり判定
	/// </summary>
	/// <param name="u1"></param>
	/// <param name="u2"></param>
	/// <returns></returns>
	const bool Rect(const Base& u1, const Base& u2)const;

	/// <summary>
	/// 楕円同士の当たり判定
	/// </summary>
	/// <param name="u1"></param>
	/// <param name="u2"></param>
	/// <returns></returns>
	const bool Ellipse(const Base& u1, const Base& u2) const;

	/// <summary>
	/// 円形と矩形の当たり判定
	/// </summary>
	/// <param name="circle">円形</param>
	/// <param name="rect">矩形</param>
	/// <returns></returns>
	const bool CircleAndRect(const Base& circle, const Base& rect)const;

private:
	static Collision* instance;

	int mapData_[Stage::STAGE_NUM_Y][Stage::STAGE_NUM_X];





	//円形の情報をまとめる構造体(引数で使う)
	struct CIRCLE
	{
		Vector2F pos;
		float radius;
	};

	/// <summary>
	/// 円形と点の当たり判定
	/// </summary>
	/// <param name="circle"></param>
	/// <param name="pixel"></param>
	/// <returns></returns>
	const bool CircleAndPixel(const CIRCLE& circle, const Vector2F& pixel)const;



	//矩形の情報をまとめる構造体(引数で使う)
	struct RECT
	{
		Vector2F pos;
		Vector2F size;
	};

	/// <summary>
	/// 矩形と点の当たり判定
	/// </summary>
	/// <param name="rect">矩形</param>
	/// <param name="pixel">点</param>
	/// <returns></returns>
	const bool RectAndPixel(const RECT& rect, const Vector2F& pixel)const;


};

