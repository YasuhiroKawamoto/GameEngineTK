/// <summary>
/// 追従カメラクラスの定義
/// </summary>
#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 静的メンバ変数の初期化
const float FollowCamera::CAMERA_DISTANCE = 5.0f;
const float EYE_DELAY = 0.05f;
const float REF_DELAY = 0.2f;


FollowCamera::FollowCamera(int width, int height)
	:Camera(width, height)
{
	m_targetPos = Vector3::Zero;
	m_targetAngle = 0.0f;
	m_mode = 2;
	m_player = nullptr;
}

void FollowCamera::Update()
{
	// カメラ視点座標、参照点座標
	Vector3 eyepos, refpos;

	//FPS カメラ処理
	if (m_mode == FPS)
	{
		Vector3 eyePoint;
		// 始点座標を計算
		eyePoint = m_targetPos + Vector3(0.0f, 1.3f, 0.0f);
		// 自機からカメラ座標への差分
		Vector3 cameraV(0, 0, -CAMERA_DISTANCE);
		// 自機の後ろに回り込む為の回転行列
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		// カメラへのベクトルを回転
		cameraV = Vector3::TransformNormal(cameraV, rotmat);

		// カメラ座標を調整 
		eyepos = eyePoint + cameraV*0.1f;

		// 視点座標を計算
		refpos = eyePoint + cameraV;
	}

	
	//TPS カメラ処理
	if(m_mode == TPS)
	{
		// 参照点座標を計算
		refpos = m_targetPos + Vector3(0.0f, 2, 0.0f);
		// 自機からカメラ座標への差分
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);
		// 自機の後ろに回り込む為の回転行列
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		// カメラへのベクトルを回転
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		// カメラ座標を計算
		eyepos = refpos + cameraV;

	

		// 視点を補間
		eyepos = m_eyePos + (eyepos - m_eyePos)*EYE_DELAY;
		// 注視点を補間
		refpos = m_targetPos + (refpos - m_targetPos)*REF_DELAY;
	}
		
	// カメラ更新
	if (m_player)
	{
		SetTargetAngle(m_player->GetParts()[0].GetRotation().y);
		SetTargetPos(m_player->GetParts()[0].GetTranslation());
	}



	SetEyePos(eyepos);
	SetRefPos(refpos);

	// 基底クラスの更新
	Camera::Update();
}

// 追従対象の座標をセット
void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetpos)
{
	m_targetPos = targetpos;
}

// 追従対象の回転角をセット
void FollowCamera::SetTargetAngle(float targetangle)
{
	m_targetAngle = targetangle;
}
