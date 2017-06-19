#include "Obj3d.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


// �ÓI�����o�ϐ���`
//�@�f�o�C�X
Microsoft::WRL::ComPtr<ID3D11Device>		Obj3d::m_d3dDevice;
//�@�f�o�C�X�R���e�L�X�g
Microsoft::WRL::ComPtr<ID3D11DeviceContext>	Obj3d::m_d3dContext;
//�@�t�@�N�g���[
std::unique_ptr<EffectFactory>		Obj3d::m_factory;
// �ėp�X�e�[�g�ݒ�
std::unique_ptr<CommonStates>		Obj3d::m_states;
// �J����
Camera* Obj3d::m_camera;


void Obj3d::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera * camera)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	m_camera = camera;

	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	m_factory->SetDirectory(L"Resources");


}

// �R���X�g���N�^
Obj3d::Obj3d()
{
	// �����o�ϐ���������

	m_scale = Vector3(1.0f, 1.0f, 1.0f);
	m_pParent = nullptr;
	// �f�t�H���g�ł̓I�C���[���g�p
	m_useQquaternion = false;
}

Obj3d::Obj3d(const Obj3d & obj)
{
}

void Obj3d::LoadModel(const wchar_t * fileName)
{
	// cmo�t�@�C����ǂݍ���
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
}

void Obj3d::Update()
{
	// ���[���h�s��̌v�Z
	// >>�g��
	Matrix scalemat = Matrix::CreateScale(m_scale);

	// >>��]
	Matrix rotmat;

	if (m_useQquaternion)
	{
		// �N�H�[�^�j�I���ŉ�]�v�Z
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{
		// �I�C���[�ŉ�]�v�Z
		Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
		Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
		rotmat = rotmatZ * rotmatX * rotmatY;
	}

	// >>�ړ�
	Matrix transmat = Matrix::CreateTranslation(m_translation);


	// ���[���h���W�ɐe�̃��[���h���W��������
	m_world = scalemat * rotmat * transmat;



	// �e�����݂���Ƃ��e�s����|����
	if (m_pParent)
	{
		m_world *= m_pParent->GetWorldMatrix();
	}
}

void Obj3d::Draw()
{
	// ���f���̕`��
	if(m_model)
		m_model->Draw(m_d3dContext.Get(), *m_states, m_world, m_camera->GetView(), m_camera->GetProj());

}
