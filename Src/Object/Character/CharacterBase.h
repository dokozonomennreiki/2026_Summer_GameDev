#pragma once
#include "../ObjectBase.h"

class CharacterBase : public ObjectBase
{
public:

	enum class COLLIDER_TYPE
	{
		NONE,

		BODY,

		FOOT,
	};

	CharacterBase(void);

	virtual ~CharacterBase(void) override;

	virtual void Update(void) override final;

	virtual void Draw(void) const override;

protected:
	struct Parameter
	{
		int maxHp = 100;
		int hp = 100;
		int attackDamage = 30;
		int turnSpeed = 15;
		int defense = 20;


	};

	static constexpr float GRAVITY = 0.0f;

	static constexpr float MAX_FALL_SPEED = 0.0f;

	Parameter parameter_;

	VECTOR moveDir_;

	VECTOR velocity_;

	float moveSpeed_;

	bool isGround_;

	virtual void InitLoad(void) override;

	virtual void InitTransform(void) override;

	virtual void InitCollider(void) override;

	virtual void InitParameter(void) = 0;

	virtual void UpdateProcess(void) = 0;

	virtual void UpdateProcessPost(void) = 0;

	virtual void ApplyPhysics(void);

	virtual void ResolveCollisions(void);

	void Move(const VECTOR& amount);
};

