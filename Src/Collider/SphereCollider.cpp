
#include "SphereCollider.h"

SphereCollider::SphereCollider(const Transform* follow, float radius, VECTOR offset, TAG tag)
	: ColliderBase(SHAPE::CIRCLE, tag, follow)
	, radius_(radius)
	, offset_(offset)
{
}

SphereCollider::~SphereCollider(void)
{

}

VECTOR SphereCollider::GetWorldPos(void) const
{
	return GetRotPos2D(offset_);
}

void SphereCollider::DrawDebug(int color)
{
	VECTOR worldPos = GetWorldPos();

	DrawCircle(static_cast<int>(worldPos.x), static_cast<int>(worldPos.y), static_cast<int>(radius_), color, false);
}