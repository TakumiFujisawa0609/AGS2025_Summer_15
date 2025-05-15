#pragma once
#include<vector>
#include<DxLib.h>
#include "../Common/Vector2.h"


class ShapesPosition
{
public:


	static std::vector<Vector2F>GetPositionCircle(float centerX, float centerY, float radius, float startAngle, int numPoints);



private:
	static	Vector2F GetOnePositionCircle(float centerX, float centerY, float radius, float angle);


};

