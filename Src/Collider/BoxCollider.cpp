
#include "BoxCollider.h"

BoxCollider::BoxCollider(const Transform* follow, VECTOR size, VECTOR offset, TAG tag)
	: ColliderBase(SHAPE::BOX, tag, follow)
	, size_(size)
	, offset_(offset)
{

}

BoxCollider::~BoxCollider(void)
{

}

VECTOR BoxCollider::GetWorldPos(void) const
{
	return GetRotPos2D(offset_);
}

void BoxCollider::GetVertices(VECTOR outVertices[4]) const
{
	float halfWidth = size_.x / 2.0f;

	float halfHeight = size_.y / 2.0f;

	VECTOR localPos[4] =
	{
		{ -halfHeight, -halfWidth, 0.0f },

		{ halfWidth, -halfHeight, 0.0f },

		{ halfWidth, halfHeight, 0.0f },

		{ -halfWidth, halfHeight, 0.0f }
	};

	for (int i = 0; i < 4; ++i)
	{
		outVertices[i] = GetRotPos2D(VAdd(offset_, localPos[i]));
	}
}

void BoxCollider::DrawDebug(int color)
{
	VECTOR vertices[4];

	GetVertices(vertices);

	for (int i = 0; i < 4; ++i)
	{
		int nextIndex = (i + 1) % 4;

		DrawLine(static_cast<int>(vertices[i].x), static_cast<int>(vertices[i].y), static_cast<int>(vertices[nextIndex].x), static_cast<int>(vertices[nextIndex].y), color);
	}
}