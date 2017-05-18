#include "Camera.h"

Camera::Camera()
	:Camera(800, 600)
{
}
	
using namespace DirectX;
using namespace DirectX::SimpleMath;


Camera::Camera(int width, int height)
{
	//メンバ変数の初期化

	// 視点
	m_eyePos = Vector3(0.0f, 0.0f, 5.0f);
	// 注視点
	m_targetPos = Vector3(0.0f, 0.0f, 0.0f);
	// 上方向ベクトル
	m_upVec = Vector3(0.0f, 1.0f, 0.0f);


	// 垂直方向視野角
	m_fovY = XMConvertToRadians(60.0f);

	// アスペクト比(横×縦の画面比率)
	m_aspect = (float)width / height;

	// ニアクリップ
	m_nearClip = 0.1f;

	// ファークリップ
	m_farClip = 1000.0f;

	// ビュー行列生成
	m_view = Matrix::CreateLookAt(m_eyePos, m_targetPos, m_upVec);
	// プロジェクション行列生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}

void Camera::Update()
{
	// ビュー行列生成
	m_view = Matrix::CreateLookAt(m_eyePos, m_targetPos, m_upVec);

	// プロジェクション行列生成 
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}

const DirectX::SimpleMath::Matrix& Camera::GetView()
{
	return m_view;
}

const DirectX::SimpleMath::Matrix& Camera::GetProj()
{
	return m_proj;
}


//// カメラの位置(視点座標)
//Vector3 eyePos(m_headPos.x, m_headPos.y+ 2.0f, m_headPos.z + 5.0f);

//// カメラの見ている先(注視点)
//Vector3 targetPos(m_headPos);

//// カメラの上方向ベクトル
//Vector3 upVec(0.0f, 1.0f, 0.0f);
//upVec.Normalize();


//m_view = Matrix::CreateLookAt(eyePos, targetPos, upVec);

//// 垂直方向視野角
//float fovT = XMConvertToRadians(60);

//// アスペクト比(横×縦の画面比率)
//float aspect = (float)m_outputWidth / m_outputHeight;

//// ニアクリップ
//float nearClip = 0.1f;

//// ファークリップ
//float farClip = 1000.0f;

//// プロジェクション行列を生成
//m_proj = Matrix::CreatePerspectiveFieldOfView(
//	fovT,aspect,nearClip,farClip);