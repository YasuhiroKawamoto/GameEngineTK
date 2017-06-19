/// <summary>
/// 3D�I�u�W�F�N�g�N���X
/// </summary>

#pragma once

#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>

#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <Model.h>

#include "Camera.h"

class Obj3d
{
private:
	// ==========�ÓI�����o�ϐ�==========

	//�@�f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
	//�@�f�o�C�X�R���e�L�X�g
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
	//�@�t�@�N�g���[
	static std::unique_ptr<DirectX::EffectFactory> m_factory;
	// �ėp�X�e�[�g�ݒ�
	static std::unique_ptr<DirectX::CommonStates> m_states;
	// �J����
	static Camera* m_camera;

public:
	// ==========�ÓI�����o�֐�==========
	static void InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext,
		Camera* camera);

private:
	// ==========�����o�ϐ�==========

	// ���f��
	std::unique_ptr<DirectX::Model> m_model;
	// �g��(XYZ)
	DirectX::SimpleMath::Vector3 m_scale;
	// ��](XYZ)[�I�C���[]
	DirectX::SimpleMath::Vector3 m_rotation;
	// ��][�N�H�[�^�j�I��]
	DirectX::SimpleMath::Quaternion m_rotationQ;
	//�N�H�[�^�j�I���g�p�t���O
	bool m_useQquaternion;
	// �ړ�(XYZ)
	DirectX::SimpleMath::Vector3 m_translation;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
	// �e��Obj3d�I�u�W�F�N�g�ւ̃|�C���^
	Obj3d* m_pParent;

public:
	// ==========�����o�֐�==========
	Obj3d();
	Obj3d(const Obj3d & obj);

	// cmo���f����ǂݍ���
	void LoadModel(const wchar_t* fileName);

	void Update();

	void Draw();

	// Set�g��(XYZ)
	void SetScale(const DirectX::SimpleMath::Vector3& scale)
	{
		m_scale = scale;
	}
	// Set��](XYZ)
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation)
	{
		m_rotation = rotation;
		m_useQquaternion = false;	// �N�H�[�^�j�I���g�p�t���O��OFF

	}
	// Set��](�N�H�[�^�j�I��)
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& rotationq)
	{
		m_rotationQ = rotationq;
		m_useQquaternion = true;	// �N�H�[�^�j�I���g�p�t���O��ON
	}
	// Set�ړ�(XYZ)
	void SetTranslation(const DirectX::SimpleMath::Vector3& translation)
	{
		m_translation = translation;
	}
	// Set�e�I�u�W�F�N�g(Obj3d)
	void SetParent(Obj3d* parent)
	{
		m_pParent = parent;
	}

	// Get�g��(XYZ)
	DirectX::SimpleMath::Vector3 GetScale()
	{
		return m_scale;
	}

	// Get��](XYZ)
	DirectX::SimpleMath::Vector3 GetRotation()
	{
		return m_rotation;
	}
	// Get�ړ�(XYZ))
	DirectX::SimpleMath::Vector3 GetTranslation()
	{
		return m_translation;
	}
	// Get���[���h�s��
	DirectX::SimpleMath::Matrix GetWorldMatrix()
	{
		return m_world;
	}

};
