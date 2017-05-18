/// <summary>
/// 自機に追従するカメラのクラス
/// </summary>
#pragma once		
#include "Camera.h"

class FollowCamera : public Camera
{
private:
	// 対象の座標
	DirectX::SimpleMath::Vector3 m_targetPos;

	// 対象の回転角
	float m_targetAngle;
public:
	static const float CAMERA_DISTANCE;

	// コンストラクタ
	FollowCamera(int width, int height);

	// 更新
	void Update() override;

	// 追従対象の座標をセット
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetpos);
	// 追従対象の回転角をセット
	void SetTargetAngle(float targetangle);

};