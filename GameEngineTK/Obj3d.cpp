#include "Obj3d.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


// 静的メンバ変数定義
//　デバイス
Microsoft::WRL::ComPtr<ID3D11Device>		Obj3d::m_d3dDevice;
//　デバイスコンテキスト
Microsoft::WRL::ComPtr<ID3D11DeviceContext>	Obj3d::m_d3dContext;
//　ファクトリー
std::unique_ptr<EffectFactory>		Obj3d::m_factory;
// 汎用ステート設定
std::unique_ptr<CommonStates>		Obj3d::m_states;
// カメラ
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

// コンストラクタ
Obj3d::Obj3d()
{
	// メンバ変数を初期化

	m_scale = Vector3(1.0f, 1.0f, 1.0f);
	m_pParent = nullptr;
	// デフォルトではオイラーを使用
	m_useQquaternion = false;
}

Obj3d::Obj3d(const Obj3d & obj)
{
}

void Obj3d::LoadModel(const wchar_t * fileName)
{
	// cmoファイルを読み込み
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
}

void Obj3d::Update()
{
	// ワールド行列の計算
	// >>拡大
	Matrix scalemat = Matrix::CreateScale(m_scale);

	// >>回転
	Matrix rotmat;

	if (m_useQquaternion)
	{
		// クォータニオンで回転計算
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{
		// オイラーで回転計算
		Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
		Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
		rotmat = rotmatZ * rotmatX * rotmatY;
	}

	// >>移動
	Matrix transmat = Matrix::CreateTranslation(m_translation);


	// ワールド座標に親のワールド座標をかける
	m_world = scalemat * rotmat * transmat;



	// 親が存在するとき親行列を掛ける
	if (m_pParent)
	{
		m_world *= m_pParent->GetWorldMatrix();
	}
}

void Obj3d::Draw()
{
	// モデルの描画
	if(m_model)
		m_model->Draw(m_d3dContext.Get(), *m_states, m_world, m_camera->GetView(), m_camera->GetProj());

}
