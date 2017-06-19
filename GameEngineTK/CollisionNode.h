/// <summary>
/// 当たり判定ノード
/// @>当たり判定の計算及び可視化
/// </summary>

#pragma once
#include "Obj3d.h"
#include "Collision.h"

/// <summary>
/// 当たり判定ノードクラス
/// </summary>
class CollisionNode
{
protected:
	// デバッグ表示用オブジェクト
	Obj3d m_obj;
	DirectX::SimpleMath::Vector3 m_trans;
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Drwa() = 0;
	void SetParent(Obj3d* parent);
	void SetTrans(const DirectX::SimpleMath::Vector3& trans)
	{
		m_trans = trans;
	}
};

/// <summary>
/// 球当たり判定ノードクラス
/// </summary>
class SphereNode : public CollisionNode, public Sphere
{
protected:
	float m_radius;
public:
	SphereNode();
	void Initialize() override;
	void Update() override;
	void Drwa() override;
	void SetRadius(float radius)
	{
		m_radius = radius;
	}
};