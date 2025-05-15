#include "ShapesPosition.h"


/// <summary>
/// 円周上にポジションを設定する
/// </summary>
/// <param name="centerX">中心座標</param>
/// <param name="centerY">中心座標</param>
/// <param name="radius">半径</param>
/// <param name="angle">描画初期角度</param>
/// <param name="numPoints">頂点数</param>
/// <returns></returns>
std::vector<Vector2F> ShapesPosition::GetPositionCircle(float centerX, float centerY, float radius, float startAngle, int numPoints)
{
	std::vector<Vector2F>pos;
	float angleStep = 2.0f * DX_PI_F / numPoints;
		float angle = startAngle;

	for (int i = 0; i < numPoints; i++) {
		angle += angleStep;
		pos.push_back(GetOnePositionCircle(centerX, centerY, radius, angle));
	}
	return pos;
}

/// <summary>
/// 円周上に一点のポジションを設定する
/// </summary>
/// <param name="centerX">中心座標</param>
/// <param name="centerY">中心座標</param>
/// <param name="radius">半径</param>
/// <param name="angle">角度</param>
/// <returns></returns>
Vector2F ShapesPosition::GetOnePositionCircle(float centerX, float centerY, float radius, float angle)
{
	Vector2F pos;
	pos.x = centerX + radius * cos(angle);
	pos.y = centerY + radius * sin(angle);
	return pos;
}
