#pragma once

/// <summary>
///  �Փ˔��胉�C�u����
/// </summary>

#include <d3d11_1.h>
#include <SimpleMath.h>


class Sphere
{
public:
	// ���S���W
	DirectX::SimpleMath::Vector3 center;
	// ���a
	float radius;

	// �R���X�g���N�^
	Sphere()
	{
		// �f�t�H���g�̔��a1m
		radius = 1.0f;
	}
};

class Segment
{
public:
	// �n�_���W
	DirectX::SimpleMath::Vector3 start;
	// �I�_���W
	DirectX::SimpleMath::Vector3 end;
};


bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB);


