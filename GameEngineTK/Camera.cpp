#include "Camera.h"

Camera::Camera()
	:Camera(800, 600)
{
}
	
using namespace DirectX;
using namespace DirectX::SimpleMath;


Camera::Camera(int width, int height)
{
	//�����o�ϐ��̏�����

	// ���_
	m_eyePos = Vector3(0.0f, 0.0f, 5.0f);
	// �����_
	m_targetPos = Vector3(0.0f, 0.0f, 0.0f);
	// ������x�N�g��
	m_upVec = Vector3(0.0f, 1.0f, 0.0f);


	// ������������p
	m_fovY = XMConvertToRadians(60.0f);

	// �A�X�y�N�g��(���~�c�̉�ʔ䗦)
	m_aspect = (float)width / height;

	// �j�A�N���b�v
	m_nearClip = 0.1f;

	// �t�@�[�N���b�v
	m_farClip = 1000.0f;

	// �r���[�s�񐶐�
	m_view = Matrix::CreateLookAt(m_eyePos, m_targetPos, m_upVec);
	// �v���W�F�N�V�����s�񐶐�
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}

void Camera::Update()
{
	// �r���[�s�񐶐�
	m_view = Matrix::CreateLookAt(m_eyePos, m_targetPos, m_upVec);

	// �v���W�F�N�V�����s�񐶐� 
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


//// �J�����̈ʒu(���_���W)
//Vector3 eyePos(m_headPos.x, m_headPos.y+ 2.0f, m_headPos.z + 5.0f);

//// �J�����̌��Ă����(�����_)
//Vector3 targetPos(m_headPos);

//// �J�����̏�����x�N�g��
//Vector3 upVec(0.0f, 1.0f, 0.0f);
//upVec.Normalize();


//m_view = Matrix::CreateLookAt(eyePos, targetPos, upVec);

//// ������������p
//float fovT = XMConvertToRadians(60);

//// �A�X�y�N�g��(���~�c�̉�ʔ䗦)
//float aspect = (float)m_outputWidth / m_outputHeight;

//// �j�A�N���b�v
//float nearClip = 0.1f;

//// �t�@�[�N���b�v
//float farClip = 1000.0f;

//// �v���W�F�N�V�����s��𐶐�
//m_proj = Matrix::CreatePerspectiveFieldOfView(
//	fovT,aspect,nearClip,farClip);