#pragma once
#include "EnemyBase.h"

class EnemyCommon:public EnemyBase
{
public:
	
	enum class COLLIDER_TYPE

	{
		
		NONE,

		BODY,

		FOOT,
	};

	EnemyCommon(void);

	EnemyCommon(int modelHandle);

	virtual ~EnemyCommon(void) override;

	virtual void Draw(void)const override;

	virtual void InitLoad(void) override;

protected:
	virtual void InitTransform(void)override;

	virtual void InitCollider(void)override;

	virtual void UpdateProcess(void) override;

	void InitParameter(void) override;

	void UpdateProcessPost(void) override;
};

