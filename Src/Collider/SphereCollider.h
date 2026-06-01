#pragma once
#include "ColliderBase.h"

class SphereCollider : public ColliderBase
{
public:
	// コンストラクタ
	SphereCollider(const Transform* follow, float radius, VECTOR offset = VGet(0, 0, 0), TAG tag = TAG::NONE);

	// デストラクタ
	virtual ~SphereCollider(void) override;

	// 半径の取得
	virtual float GetRadius(void) const override { return radius_; }
	
	// 半径の設定
	void SetRadius(float radius) { radius_ = radius; }

	virtual VECTOR GetWorldPos(void) const override;

	void SetOffset(const VECTOR& offset) { offset_ = offset; }

	VECTOR GetOffset(void) const { return offset_; }

protected:
	virtual void DrawDebug(int color) override;

private:
	
	float radius_; // 半径
	
	VECTOR offset_; // ローカルオフセット
};

