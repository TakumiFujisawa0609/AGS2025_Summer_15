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
/// 波形のポジションを返す
/// </summary>
/// <param name="startX">開始座標</param>
/// <param name="startY">開始座標</param>
/// <param name="amplitude">振幅</param>
/// <param name="wavelength">波長</param>
/// <param name="phase">位相(開始角度)</param>
/// <param name="numPoints">生成する点の数</param>
/// <param name="interval">点と点の間隔</param>
/// <returns></returns>
std::vector<Vector2F> ShapesPosition::GetPositionWave(float startX, float startY, float amplitude, float wavelength, float phase, int numPoints, float interval)
{
	std::vector<Vector2F> positions;
	for (int i = 0; i < numPoints; ++i) {
		float x = startX + i * interval;
		float rad = (x / wavelength) * 2.0f * DX_PI_F + phase;
		float y = startY + amplitude * sinf(rad);
		positions.push_back(Vector2F(x,y));
	}
	return positions;
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
