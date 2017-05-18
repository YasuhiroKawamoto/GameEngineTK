/// <summary>
/// カメラを制御するクラス
/// </summary>
#pragma once		

#include <d3d11.h>
#include <SimpleMath.h>

class Camera
{
protected:
	// ==ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// 視点
	DirectX::SimpleMath::Vector3 m_eyePos;
	// 注視点
	DirectX::SimpleMath::Vector3 m_targetPos;
	// 上方向ベクトル
	DirectX::SimpleMath::Vector3 m_upVec;

	
	// ==プロジェクション行列
	DirectX::SimpleMath::Matrix m_proj;
	// 垂直方向視野角
	float m_fovY;
	// アスペクト比
	float m_aspect;
	// ニアクリップ
	float m_nearClip;
	// ファークリップ
	float m_farClip;

public:
	Camera();
	Camera(int width, int height);

	virtual ~Camera() {}

	// 更新
	virtual void Update();

	// ビュー行列取得
	const DirectX::SimpleMath::Matrix& GetView();

	// プロジェクション行列取得
	const DirectX::SimpleMath::Matrix& GetProj();

	// 視点座標設定
	void SetEyePos(const DirectX::SimpleMath::Vector3& eyePos)
	{
		m_eyePos = eyePos;
	}

	// 注視点座標設定
	void SetRefPos(const DirectX::SimpleMath::Vector3& targetPos)
	{
		m_targetPos = targetPos;
	}

	// 上ベクトル座標設定
	void SetUpVec(const DirectX::SimpleMath::Vector3& upVec)
	{
		m_upVec = upVec;
		m_upVec.Normalize();
	}


	void SetFovY(float fovY)
	{
		m_fovY = fovY;
	}

	void SetAspect(float aspect)
	{
		m_aspect = aspect;
	}

	void SetNearClip(float nearclip)
	{
		m_nearClip = nearclip;
	}

	void SetFarClip(float farclip)
	{
		m_farClip = farclip;
	}

};