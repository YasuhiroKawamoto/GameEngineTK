#include "Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


	/// <summary>
	/// ���Ƌ��̓����蔻��
	/// </summary>
	/// <param name="sphereA">��1</param>
	/// <param name="sphereB">��2</param>
	/// <returns>true:�������Ă���/false:�������Ă��Ȃ�</returns>
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	// A ���@B(�x�N�g��)
	Vector3 sub = sphereA.center - sphereB.center;

	// A��B�̋�����2����v�Z
	float distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	// ���a�̘a��2����v�Z
	float radiusSquare = sphereA.radius + sphereB.radius;
	radiusSquare *= radiusSquare;

	// 2�_�ԋ��������a�̘a���������Ɠ������Ă��Ȃ�
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	// �������Ă���
	return true;
}

