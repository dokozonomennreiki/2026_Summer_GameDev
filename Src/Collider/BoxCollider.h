#pragma once
#include "ColliderBase.h"

class BoxCollider : public ColliderBase
{
public:

	BoxCollider(const Transform* follow, VECTOR size, VECTOR offset = VGet(0, 0, 0), TAG tag = TAG::NONE);

	virtual ~BoxCollider(void) override;

	virtual VECTOR GetWorldPos(void) const override;

	VECTOR GetSize(void) const { return size_; }

	void SetSize(const VECTOR& size) { size_ = size; }

	void GetVertices(VECTOR outVertices[4]) const;

protected:
	
	virtual void DrawDebug(int color) override;

private:

	VECTOR size_;

	VECTOR offset_;
};

