#include "Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


	/// <summary>
	/// 球と球の当たり判定
	/// </summary>
	/// <param name="sphereA">球1</param>
	/// <param name="sphereB">球2</param>
	/// <returns>true:当たっている/false:当たっていない</returns>
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	// A →　B(ベクトル)
	Vector3 sub = sphereA.center - sphereB.center;

	// AとBの距離の2乗を計算
	float distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	// 半径の和の2乗を計算
	float radiusSquare = sphereA.radius + sphereB.radius;
	radiusSquare *= radiusSquare;

	// 2点間距離が半径の和よりも長いと当たっていない
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	// 当たっている
	return true;
}

