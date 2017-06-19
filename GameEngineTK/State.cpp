#include "State.h"
#include "Player.h"


// 静的メンバ変数の初期化
State* Standby::pState = nullptr;
State* ConvergenceAttack::pState = nullptr;
State* ThrowingAttack::pState = nullptr;

using namespace DirectX;
using namespace DirectX::SimpleMath;


State* Standby::GetInstance()
{
	if (pState == nullptr)
		pState = new Standby();
	return pState;
}

void Standby::Action(Character* pl)
{
	static float angle = 0.0f;

	DirectX::Keyboard* key = dynamic_cast<Player*>(pl)->GetKey();
	DirectX::Keyboard::State kb = key->GetState();





	pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetRotation(Vector3(0.0f, angle += 0.05f, 0.0f));



	// Zキーで収束攻撃
	if (kb.Z)
	{
		pl->ChangeState(ConvergenceAttack::GetInstance());
	}

	// Xキーで投擲攻撃
	if (kb.X)
	{
		pl->ChangeState(ThrowingAttack::GetInstance());
	}

}

State* ConvergenceAttack::GetInstance()
{
	if (pState == nullptr)
		pState = new ConvergenceAttack();
	return pState;
}

void ConvergenceAttack::Action(Character* pl)
{
	static int phese = 0;
	static float cnt = 0;
	Vector3 scale;

	Vector3 angle;
	Vector3 scalemat;
	Vector3 translate;

	static float anglef = 0.0f;
	switch (phese)
	{
		// 剣を一点に集める
	case 0:
		// 親オブジェクトをX軸で360°回転させる
		angle = pl->GetParts()[Player::PARTS_WEAPON_PARENT].GetRotation();
		anglef = (XMConvertToRadians(-90) - angle.x) / 20.0f;
		angle.y = 0.0f;
		angle.x += anglef;

		pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetRotation(angle);
		// 親オブジェクトを前に出す
		pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetTranslation(Vector3(0.0f, 2.0f, -2.0f));



		for (int i = Player::PARTS_WEAPON_SWORD1; i <= Player::PARTS_WEAPON_SWORD8; i++)
		{
			//子オブジェクトをX軸回転
			angle = pl->GetParts()[i].GetRotation();

			angle.z += (XMConvertToRadians(180) - angle.z) / 20.0f;
			pl->GetParts()[i].SetRotation(angle);

			// 子オブジェクトどうしを離す
			int id = i - Player::PARTS_WEAPON_SWORD1;
			float angle = XMConvertToRadians((360 / 8.0f)*id);
			pl->GetParts()[i].SetTranslation(Vector3(cosf(-angle)*3.5, 0.5f, sinf(-angle)*3.5));
		}


		cnt++;
		if (cnt >= 120)
		{
			phese = 1;
			cnt = 0;

			pl->GetParts()[Player::PARTS_BEAM].SetTranslation(Vector3(0, 0.5f, 0));

		}
		break;
	case 1:

		scale = pl->GetParts()[Player::PARTS_BEAM].GetScale();
		scalemat = (Vector3(0.25f - scale.x, 0.25f - scale.y, 0.25f - scale.z) / 50.0f);

		pl->GetParts()[Player::PARTS_BEAM].SetScale(scale + scalemat);
		cnt++;
		if (cnt >= 120)
		{
			phese = 2;
			cnt = 0;


		}
		break;
	case 2:
		translate = pl->GetParts()[Player::PARTS_BEAM].GetTranslation();

		translate.y += 0.5f;
		pl->GetParts()[Player::PARTS_BEAM].SetTranslation(translate);

		for (int i = Player::PARTS_WEAPON_SWORD1; i <= Player::PARTS_WEAPON_SWORD8; i++)
		{
			//子オブジェクトをX軸回転
			angle = pl->GetParts()[i].GetRotation();

			angle.z += (XMConvertToRadians(0) - angle.z) / 20.0f;
			pl->GetParts()[i].SetRotation(angle);

			// 子オブジェクトどうしを離す
			int id = i - Player::PARTS_WEAPON_SWORD1;
			float angle = XMConvertToRadians((360 / 8.0f)*id);
			pl->GetParts()[i].SetTranslation(Vector3(cosf(-angle), 0.5f, sinf(-angle)));
		}

		cnt++;
		if (cnt >= 150)
		{
			pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetScale(Vector3::Zero);
			pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetTranslation(Vector3::Zero);
			pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetRotation(Vector3::Zero);



			pl->GetParts()[Player::PARTS_BEAM].SetTranslation(Vector3(0, 0.5f, 0));
			pl->GetParts()[Player::PARTS_BEAM].SetScale(Vector3::Zero);
			for (int i = Player::PARTS_WEAPON_SWORD1; i <= Player::PARTS_WEAPON_SWORD8; i++)
			{
				pl->GetParts()[i].SetTranslation(Vector3(Vector3::Zero));
			}
			cnt = 0;
			phese = 3;
		}
		break;

	case 3:

		Vector3 scale = pl->GetParts()[Player::PARTS_WEAPON_PARENT].GetScale();
		Vector3 Scalemat = Vector3(1 - scale.x, 1 - scale.y, 1 - scale.z);

		Vector3 translate = pl->GetParts()[Player::PARTS_WEAPON_PARENT].GetTranslation();
		Vector3 transmat;
		for (int i = Player::PARTS_WEAPON_SWORD1; i <= Player::PARTS_WEAPON_SWORD8; i++)
		{
			int id = i - Player::PARTS_WEAPON_SWORD1;
			float angle = XMConvertToRadians((360 / 8.0f)*id);

			pl->GetParts()[i].SetTranslation(Vector3(cosf(-angle), 0.5f, sinf(-angle)));
		}

		scale += Scalemat / 20.0f;
		pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetScale(scale);
		cnt++;
		if (cnt >= 120)
		{
			pl->ChangeState(Standby::GetInstance());
			phese = 0;
			cnt = 0;
		}
		break;
	}
}


State* ThrowingAttack::GetInstance()
{
	if (pState == nullptr)
		pState = new ThrowingAttack();
	return pState;
}

void ThrowingAttack::Action(Character* pl)
{
	static int phese = 0;
	static float cnt = 0;
	Vector3 angle;
	float rotateX;
	static float angleZ = 0.0f;
	static float spd = 0.0f;


	switch (phese)
	{
		// 剣を一点に集める
	case 0:

		// 親オブジェクトをX軸で360°回転させる
		angle = pl->GetParts()[Player::PARTS_WEAPON_PARENT].GetRotation();
		rotateX =( XMConvertToRadians(-360) - angle.x)/20.0f;
		angle.x += rotateX;


		pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetRotation(angle);

		// 親オブジェクトを前に出す
		pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetTranslation(Vector3(0.0f, 2.0f, -2.0f));

		// 子オブジェクトを集める
		for (int i = Player::PARTS_WEAPON_SWORD1; i <= Player::PARTS_WEAPON_SWORD8; i++)
		{

			Vector3 pos = pl->GetParts()[i].GetTranslation();

			float moveX = (0 - pos.x)/20.0f;
			float moveZ = (0 - pos.z)/20.0f;
			pos.x += moveX;
			pos.z += moveZ;
			pl->GetParts()[i].SetTranslation(pos);
		}

		cnt++;
		if (cnt >= 90)
		{
			for (int i = Player::PARTS_WEAPON_SWORD1; i <= Player::PARTS_WEAPON_SWORD8; i++)
			{
				pl->GetParts()[i].SetTranslation(Vector3::Zero);
			}

			pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetRotation(Vector3(XMConvertToRadians(-360.0f), 0.0f, 0.0f));


			phese = 1;
			cnt = 0;
		}
		break;
	case 1:
		angle = pl->GetParts()[Player::PARTS_WEAPON_PARENT].GetRotation();
		

		spd += 0.0025f;
		if (spd > 0.15f)
			spd = 0.15f;


		angle.y += spd;
		pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetRotation(angle);

		cnt++;
		if (cnt >= 180)
		{
			phese = 2;
			cnt = 0;
			angleZ = 0.0f;
		}
		break;
	case 2:
		
		spd = -0.78f;
		
		angle = pl->GetParts()[Player::PARTS_WEAPON_PARENT].GetRotation();
		angle.y += -0.15f;
		pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetRotation(angle);

		angle = pl->GetParts()[Player::PARTS_WEAPON_PARENT].GetTranslation();
		angle.z += spd;

		pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetTranslation(angle);


		cnt++;
		if (cnt >= 90)
		{
			phese = 3;
			cnt = 0;
			pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetTranslation(Vector3::Zero);
			pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetScale(Vector3::Zero);

		}
		break;

	case 3:
		Vector3 scale = pl->GetParts()[Player::PARTS_WEAPON_PARENT].GetScale();
		Vector3 Scalemat = Vector3(1- scale.x, 1 - scale.y, 1 - scale.z);

		Vector3 translate = pl->GetParts()[Player::PARTS_WEAPON_PARENT].GetTranslation();
		Vector3 transmat;
		for (int i = Player::PARTS_WEAPON_SWORD1; i <= Player::PARTS_WEAPON_SWORD8; i++)
		{
			int id = i - Player::PARTS_WEAPON_SWORD1;
			float angle = XMConvertToRadians((360 / 8.0f)*id);

			pl->GetParts()[i].SetTranslation(Vector3(cosf(-angle), 0.5f, sinf(-angle)));
		}

		scale += Scalemat / 20.0f;
		pl->GetParts()[Player::PARTS_WEAPON_PARENT].SetScale(scale);

		cnt++;
		if (cnt >= 90)
		{
			pl->ChangeState(Standby::GetInstance());
			cnt= 0;
			phese = 0;
		}
		break;

	}
	
}
