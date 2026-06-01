#pragma once
#include "../CharacterBase.h"
#include "DxLib.h"


class Player : public CharacterBase
{
public:

	Player(void);

   ~Player(void) override;

   void InitLoad(void) override;

	void Draw(void) const;

	// 今回のフレームでEスキル（アイコン1）を使ったか
	bool IsESkillTriggered(void) const { return isESkillTriggered_; }
	// 今回のフレームでQスキル（アイコン2）を使ったか
	bool IsQSkillTriggered(void) const { return isQSkillTriggered_; }

	// 攻撃範囲（半径）を取得するゲッター
	float GetAttackRange(void) const { return 150.0f; } // 例: 半径150の範囲攻撃
	// 攻撃力を取得する
	int GetAttackDamage(void) const { return parameter_.attackDamage; }

	int GetIconHandle(void) const { return iconHandle_; }
	int GetIconHandle2(void) const { return iconHandle2_; }
	bool GetNoDrawFlag(void) const { return NoDrawFlag; }
	bool GetNoDrawFlag2(void) const { return NoDrawFlag2; }

protected:

	void InitTransform(void) override;

	void InitCollider(void) override;

	void InitParameter(void) override;

	void UpdateProcessPost(void) override;

	void UpdateProcess(void) override;


	
private:

	bool isESkillTriggered_ = false;
	bool isQSkillTriggered_ = false;


	int iconHandle_ = -1;


	int iconHandle2_ = -1;


	int currentDrawHandle_ = -1;

	bool NoDrawFlag = false;
	bool NoDrawFlag2 = false;
	float scale_ = 1.0f;
	static constexpr int UI_MARGIN = 20;

	static constexpr int UI_SPACING = 15;
};

