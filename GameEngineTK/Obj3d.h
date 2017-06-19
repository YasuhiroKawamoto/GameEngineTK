/// <summary>
/// 3Dオブジェクトクラス
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
	// ==========静的メンバ変数==========

	//　デバイス
	static Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
	//　デバイスコンテキスト
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
	//　ファクトリー
	static std::unique_ptr<DirectX::EffectFactory> m_factory;
	// 汎用ステート設定
	static std::unique_ptr<DirectX::CommonStates> m_states;
	// カメラ
	static Camera* m_camera;

public:
	// ==========静的メンバ関数==========
	static void InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext,
		Camera* camera);

private:
	// ==========メンバ変数==========

	// モデル
	std::unique_ptr<DirectX::Model> m_model;
	// 拡大(XYZ)
	DirectX::SimpleMath::Vector3 m_scale;
	// 回転(XYZ)[オイラー]
	DirectX::SimpleMath::Vector3 m_rotation;
	// 回転[クォータニオン]
	DirectX::SimpleMath::Quaternion m_rotationQ;
	//クォータニオン使用フラグ
	bool m_useQquaternion;
	// 移動(XYZ)
	DirectX::SimpleMath::Vector3 m_translation;
	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;
	// 親のObj3dオブジェクトへのポインタ
	Obj3d* m_pParent;

public:
	// ==========メンバ関数==========
	Obj3d();
	Obj3d(const Obj3d & obj);

	// cmoモデルを読み込む
	void LoadModel(const wchar_t* fileName);

	void Update();

	void Draw();

	// Set拡大(XYZ)
	void SetScale(const DirectX::SimpleMath::Vector3& scale)
	{
		m_scale = scale;
	}
	// Set回転(XYZ)
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation)
	{
		m_rotation = rotation;
		m_useQquaternion = false;	// クォータニオン使用フラグをOFF

	}
	// Set回転(クォータニオン)
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& rotationq)
	{
		m_rotationQ = rotationq;
		m_useQquaternion = true;	// クォータニオン使用フラグをON
	}
	// Set移動(XYZ)
	void SetTranslation(const DirectX::SimpleMath::Vector3& translation)
	{
		m_translation = translation;
	}
	// Set親オブジェクト(Obj3d)
	void SetParent(Obj3d* parent)
	{
		m_pParent = parent;
	}

	// Get拡大(XYZ)
	DirectX::SimpleMath::Vector3 GetScale()
	{
		return m_scale;
	}

	// Get回転(XYZ)
	DirectX::SimpleMath::Vector3 GetRotation()
	{
		return m_rotation;
	}
	// Get移動(XYZ))
	DirectX::SimpleMath::Vector3 GetTranslation()
	{
		return m_translation;
	}
	// Getワールド行列
	DirectX::SimpleMath::Matrix GetWorldMatrix()
	{
		return m_world;
	}

};

