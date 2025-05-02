#pragma once
class Vector2
{
public:

	int x;
	int y;

	// コンストラクタ
	Vector2(void);

	// コンストラクタ
	Vector2(int vX, int vY);

	// デストラクタ
	~Vector2(void);

};

class Vector2F
{
public:


	float x;
	float y;

	//コンストラクタ
	Vector2F(void);

	//コンストラクタ
	Vector2F(float vX, float vY);

	//デストラクタ
	~Vector2F(void);
};