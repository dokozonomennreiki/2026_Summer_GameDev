#pragma once
#include"EnemyBase.h"

class Enemy:public EnemyBase
{

public:

	enum class ENEMY_TYPE
	{
		NONE,

		BODY,

		FOOT,
	};
	
	Enemy(void);

	Enemy(int modelHandle);

    ~Enemy(void) override;

	void Draw(void)const;

	void InitLoad(void) override;


	
protected:
	
	void InitTransform(void)override;

	void InitParameter(void) override;

	void InitCollider(void)override;

   void UpdateProcess(void) override;

 

   void UpdateProcessPost(void) override;
private:




};

