#include "CharacterBase.h"
#include "../../Manager/Generic/SceneManager.h"
#include "../../Collider/ColliderBase.h"

CharacterBase::CharacterBase(void)
	: moveDir_(VGet(0, 0, 0))
	, velocity_(VGet(0, 0, 0))
	, moveSpeed_(0.0f)
	, isGround_(false)
{
}

CharacterBase::~CharacterBase(void)
{

}

void CharacterBase::InitLoad(void)
{
	InitParameter();
}

void CharacterBase::InitTransform(void)
{
	trans_.pos = VGet(0, 0, 0);
	
	trans_.rot = VGet(0, 0, 0);

	trans_.scl = VGet(1, 1, 1);
}

void CharacterBase::InitCollider(void)
{

}

void CharacterBase::Update(void)
{
	UpdateProcess();

	ApplyPhysics();

	ResolveCollisions();

	trans_.Update();
}

void CharacterBase::ApplyPhysics(void)
{
	float dt = SceneManager::GetInstance().GetDeltaTime();


	if (!isGround_)
	{
		velocity_.y += GRAVITY;

		if (velocity_.y > MAX_FALL_SPEED)
		{
			velocity_.y = MAX_FALL_SPEED;
		}
	}
	else
	{
		if (velocity_.y > 0)
		{
			velocity_.y = 0.0f;
		}
	}

	velocity_.x = moveDir_.x * moveSpeed_;

}

void CharacterBase::ResolveCollisions(void)
{
	trans_.pos = VAdd(trans_.pos, velocity_);

	isGround_ = false;

	for (const auto& hitCol : hitColliders_)
	{
		if (hitCol->GetTag() == ColliderBase::TAG::NONE)
		{

		}
	}
}

void CharacterBase::Draw(void) const
{
	ObjectBase::Draw();
}

void CharacterBase::Move(const VECTOR& amount)
{
	trans_.pos = VAdd(trans_.pos, amount);
}


