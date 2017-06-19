#include "Player.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// ファイルの読み込み
/// </summary>
void Player::Load()
{
	// プレイヤーパーツのロード

	m_parts.resize(PARTS_NUM);

	m_parts[PARTS_TANK].LoadModel(L"Resources\\Tank.cmo");
	m_parts[PARTS_BODY].LoadModel(L"Resources\\Body.cmo");
	m_parts[PARTS_ARM].LoadModel(L"Resources\\Arm.cmo");
	m_parts[PARTS_HEAD].LoadModel(L"Resources\\Head.cmo");
	m_parts[PARTS_ENGINE].LoadModel(L"Resources\\Engine.cmo");

	for (int i = PARTS_WEAPON_SWORD1; i <= PARTS_WEAPON_SWORD8; i++)
	{
		m_parts[i].LoadModel(L"Resources\\Sword.cmo");
	}
	m_parts[PARTS_BEAM].LoadModel(L"Resources\\Sphere.cmo");

}


/// <summary>
/// 初期化
/// </summary>
void Player::Init()
{
	// 親子関係の構築
	m_parts[PARTS_BODY].SetParent(&m_parts[PARTS_TANK]);
	m_parts[PARTS_HEAD].SetParent(&m_parts[PARTS_BODY]);
	m_parts[PARTS_ARM].SetParent(&m_parts[PARTS_BODY]);
	m_parts[PARTS_ENGINE].SetParent(&m_parts[PARTS_BODY]);
	m_parts[PARTS_WEAPON_PARENT].SetParent(&m_parts[PARTS_BODY]);
	m_parts[PARTS_BEAM].SetParent(&m_parts[PARTS_WEAPON_PARENT]);

	for (int i = PARTS_WEAPON_SWORD1; i <= PARTS_WEAPON_SWORD8; i++)
	{
		m_parts[i].SetParent(&m_parts[PARTS_WEAPON_PARENT]);
	}

	// 子パーツのオフセット
	m_parts[PARTS_BODY].SetTranslation(Vector3(0.0f, 0.5f, 0.0f));
	m_parts[PARTS_HEAD].SetTranslation(Vector3(-0.15f, 0.5f, 0.0f));
	m_parts[PARTS_ARM].SetTranslation(Vector3(0.4f, 0.2f, 0.0f));
	m_parts[PARTS_ENGINE].SetTranslation(Vector3(0.0f, 0.0f, 1.0f));

	for (int i = PARTS_WEAPON_SWORD1; i <= PARTS_WEAPON_SWORD8; i++)
	{
		int id = i - PARTS_WEAPON_SWORD1;
		float angle = XMConvertToRadians((360 / 8.0f)*id);
		m_parts[i].SetTranslation(Vector3(cosf(-angle), 0.5f, sinf(-angle)));
		m_parts[i].SetRotation(Vector3(0.0f, angle, 0.0f));
	}


	m_parts[PARTS_ARM].SetScale(Vector3(0.7f, 0.7f, 0.7f));


	m_parts[PARTS_BEAM].SetScale(Vector3::Zero);

	
	// 初期ステートの設定
	m_currentState = Standby::GetInstance();

	// 弾当たり判定ノードの設定
	{

		m_collisionNodeBullet.Initialize();
		m_collisionNodeBullet.SetParent(&m_parts[PARTS_ARM]);
		m_collisionNodeBullet.SetTrans(Vector3(0, 0, 0));
		m_collisionNodeBullet.SetRadius(0.5f);
	}
}

/// <summary>
/// 発射
/// </summary>
void Player::FireBullet()
{
	// 発射するパーツのワールド行列を取得
	Matrix worldm = m_parts[Player::PARTS_ARM].GetWorldMatrix();

	// 抽出した情報(ワールド基準)
	Vector3 scale;
	Quaternion rotation;
	Vector3 translation;

	// ワールド座標から各要素を抽出
	worldm.Decompose(scale, rotation, translation);

	// 親パーツから独立させる
	m_parts[Player::PARTS_ARM].SetParent(nullptr);
	m_parts[Player::PARTS_ARM].SetScale(scale);
	m_parts[Player::PARTS_ARM].SetRotationQ(rotation);
	m_parts[Player::PARTS_ARM].SetTranslation(translation);

	m_bulletVel = Vector3(0.0f, 0.0f, -0.3f);
	// パーツの向きに合わせて速度ベクトルを回転
	m_bulletVel = Vector3::Transform(m_bulletVel, rotation);

	m_isShoot = true;
	 

}

/// <summary>
/// リセット
/// </summary>
void Player::ResetBullet()
{
	m_parts[Player::PARTS_ARM].SetParent(&m_parts[PARTS_BODY]);
	m_parts[PARTS_ARM].SetRotationQ(Quaternion::Identity);
	m_parts[PARTS_ARM].SetTranslation(Vector3(0.4f, 0.2f, 0.0f));


}


/// <summary>
/// 移動処理
/// </summary>
void Player::Move()
{
	// キー更新
	auto key = m_keyboard->GetState();


	// 角度変更
	if (key.A)
	{
		float angle = m_parts[PARTS_TANK].GetRotation().y;
		m_parts[PARTS_TANK].SetRotation(Vector3(0, angle + 0.03f, 0));
	}

	if (key.D)
	{
		float angle = m_parts[PARTS_TANK].GetRotation().y;
		m_parts[PARTS_TANK].SetRotation(Vector3(0, angle - 0.03f, 0));
	}

	// 前進
	if (key.W)
	{
		Vector3 moveV(0.0f, 0.0f, -0.1f);

		// 移動ベクトルを回転
		Matrix rotmat = Matrix::CreateRotationY(m_parts[0].GetRotation().y);
		moveV = Vector3::TransformNormal(moveV, rotmat);

		m_parts[0].SetTranslation(m_parts[0].GetTranslation() + moveV);
	}

	//　後退
	if (key.S)
	{
		Vector3 moveV(0.0f, 0.0f, 0.1f);

		// 移動ベクトルを回転
		Matrix rotmat = Matrix::CreateRotationY(m_parts[0].GetRotation().y);
		moveV = Vector3::TransformNormal(moveV, rotmat);

		m_parts[0].SetTranslation(m_parts[0].GetTranslation() + moveV);
	}
}

Player::Player()
{
	
}

Player::Player(DirectX::Keyboard * keybord, DirectX::Keyboard::KeyboardStateTracker * keyTracker)
	:m_keyboard(keybord),
	m_keyboardTracker(keyTracker)
{
	m_isShoot = false;
	m_cnt = 0;
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	// メモリの解放
	delete m_currentState;
}

/// <summary>
/// 更新
/// </summary>
void Player::Update()
{
	// 現在のアクションを実行
	m_currentState->Action(this);

	// パーツの更新
	std::vector<Obj3d>::iterator itr;
	for (itr = this->GetParts().begin(); itr != this->GetParts().end(); itr++)
	{
		itr->Update();
	}

	// 弾当たり判定ノードの更新
	m_collisionNodeBullet.Update();

	// 移動処理
	Move();

	auto key = m_keyboard->GetState();
	m_keyboardTracker->Update(key);
	if (m_keyboardTracker->pressed.Space)
	{
		m_isShoot = false;
		ResetBullet();
		
		FireBullet();
	}


	if (m_isShoot)
	{
		m_parts[PARTS_ARM].SetTranslation(m_parts[PARTS_ARM].GetTranslation() + m_bulletVel);
		m_cnt++;
	}

	if (m_cnt > 120)
	{
		m_cnt = 0;
		m_isShoot = false;
		ResetBullet();
	}

}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	// パーツの描画
	std::vector<Obj3d>::iterator itr;
	for (itr = m_parts.begin(); itr != m_parts.end(); itr++)
	{
		itr->Draw();
	}

	// 弾当たり判定ノードの描画
	m_collisionNodeBullet.Drwa();
}
