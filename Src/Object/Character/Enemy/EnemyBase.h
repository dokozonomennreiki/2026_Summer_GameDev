#pragma once
#include <memory>
#include"../../ObjectBase.h"
#include "../CharacterBase.h"


class EnemyBase : public CharacterBase
{
public:

	EnemyBase(void);
	
	
	EnemyBase(int modelHandle);

	
		
	virtual ~EnemyBase(void) override;
	
	virtual void InitLoad(void) override;

	virtual void InitTransform(void) override;

	virtual void InitParameter(void) override;

	virtual void InitCollider(void) override;

	virtual void Draw(void) const;
	
	virtual void UpdateProcessPost(void) override;

	virtual void UpdateProcess(void) override;
	
	int GetHp(void);

	void SetHp(int hp);

	void SetPos(const VECTOR& pos) { trans_.pos = pos; }

	bool IsAlive(void) const { return  isAlive_; }

	void SetIsAlive(bool alive) { isAlive_ = alive; }

protected:

	
private:

	bool NoDrawFlag = false;
	bool NoDrawFlag2 = false;
	float scale_ = 1.0f;
	static constexpr int UI_MARGIN = 20;

	static constexpr int UI_SPACING = 15;



bool isAlive_ = true;

};

