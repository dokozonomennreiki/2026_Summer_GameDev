#include "Player.h"
#include "../../../Manager/Generic/InputManager.h"
#include "../../../Manager/Generic/ResourceManager.h"
#include "../../../Collider/SphereCollider.h"


Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::InitLoad(void)
{
	
	trans_.modelId = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::MODEL_PLAYER);

	iconHandle_ = LoadGraph("Data/Image/IconTest.png");
	iconHandle2_ = LoadGraph("Data/Image/IconTest2.png");
	
	
	if (iconHandle_ - 1)
	{
		printfDx("IconTest.pngの読み込みに失敗");

	}
}

void Player::InitTransform(void)
{
	trans_.pos = VGet(0.0f, 200.0f, -500.0f);

	moveSpeed_ = 5.0f;
}

void Player::InitCollider(void)
{
	int bodyKey = static_cast<int>(COLLIDER_TYPE::BODY);

	ownColliders_[bodyKey] = new SphereCollider(&trans_, 16.0f, VGet(0, 0, 0), ColliderBase::TAG::PLAYER);
}

void Player::InitParameter(void)
{
	parameter_.maxHp = 100;

	parameter_.hp = 100;

	parameter_.attackDamage = 30;

	parameter_.turnSpeed = 15;
	
	parameter_.defense = 20;
}

void Player::UpdateProcessPost(void)
{
	moveDir_ = VGet(0, 0, 0);
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_A)) { moveDir_.x -= 1.0f; }
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_D)) { moveDir_.x += 1.0f; }

	if (VSquareSize(moveDir_) > 0.0f) { moveDir_ = VNorm(moveDir_); }

	// ─── ★スキル発動フラグの更新 ───
	// 毎フレームリセットし、押された瞬間（TrgDown）だけ true にする
	isESkillTriggered_ = false;

	isQSkillTriggered_ = false;

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_E))
	{
		int i= 1;
		NoDrawFlag = !NoDrawFlag; // 既存の表示切り替えロジック
		isESkillTriggered_ = true; // ★攻撃発生！
	}

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_Q))
	{
		NoDrawFlag2 = !NoDrawFlag2; // 既存の表示切り替えロジック
		isQSkillTriggered_ = true;  // ★攻撃発生！
	}
}


void Player::UpdateProcess(void)
{
	moveDir_ = VGet(0, 0, 0);

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_A)) { moveDir_.x -= 1.0f; }

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_D)) { moveDir_.x += 1.0f; }



	if (VSquareSize(moveDir_) > 0.0f)
	{
		moveDir_ = VNorm(moveDir_);	
	}


	UpdateProcessPost();

}



void Player::Draw(void) const
{

	CharacterBase::Draw();

	
}
