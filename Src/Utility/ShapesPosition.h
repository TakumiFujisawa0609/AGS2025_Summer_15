#pragma once
#include<vector>
#include<DxLib.h>
#include "../Common/Vector2.h"


class ShapesPosition
{
public:

	/// <summary>
/// 円周上にポジションを設定する
/// </summary>
/// <param name="centerX">中心座標</param>
/// <param name="centerY">中心座標</param>
/// <param name="radius">半径</param>
/// <param name="angle">描画初期角度</param>
/// <param name="numPoints">頂点数</param>
/// <returns></returns>
	static std::vector<Vector2F>GetPositionCircle(float centerX, float centerY, float radius, float startAngle, int numPoints);

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
	static std::vector<Vector2F>GetPositionWave(float startX, float startY, float amplitude, float wavelength, float phase, int numPoints, float interval);

private:
	static	Vector2F GetOnePositionCircle(float centerX, float centerY, float radius, float angle);


};

