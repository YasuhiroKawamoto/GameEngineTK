#include "Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


	/// <summary>
	/// ‹…‚Æ‹…‚Ì“–‚½‚è”»’è
	/// </summary>
	/// <param name="sphereA">‹…1</param>
	/// <param name="sphereB">‹…2</param>
	/// <returns>true:“–‚½‚Á‚Ä‚¢‚é/false:“–‚½‚Á‚Ä‚¢‚È‚¢</returns>
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	// A ¨@B(ƒxƒNƒgƒ‹)
	Vector3 sub = sphereA.center - sphereB.center;

	// A‚ÆB‚Ì‹——£‚Ì2æ‚ðŒvŽZ
	float distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	// ”¼Œa‚Ì˜a‚Ì2æ‚ðŒvŽZ
	float radiusSquare = sphereA.radius + sphereB.radius;
	radiusSquare *= radiusSquare;

	// 2“_ŠÔ‹——£‚ª”¼Œa‚Ì˜a‚æ‚è‚à’·‚¢‚Æ“–‚½‚Á‚Ä‚¢‚È‚¢
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	// “–‚½‚Á‚Ä‚¢‚é
	return true;
}

