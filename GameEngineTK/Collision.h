#pragma once

/// <summary>
///  衝突判定ライブラリ
/// </summary>

#include <d3d11_1.h>
#include <SimpleMath.h>


class Sphere
{
public:
	// 中心座標
	DirectX::SimpleMath::Vector3 center;
	// 半径
	float radius;

	// コンストラクタ
	Sphere()
	{
		// デフォルトの半径1m
		radius = 1.0f;
	}
};

class Segment
{
public:
	// 始点座標
	DirectX::SimpleMath::Vector3 start;
	// 終点座標
	DirectX::SimpleMath::Vector3 end;
};


bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB);


