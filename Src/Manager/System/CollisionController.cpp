
#define NOMINMAX
#include "CollisionController.h"
#include "../../Object/ObjectBase.h"
#include "../../Utility/Utility.h"
#include "../Generic/SceneManager.h"
#include "../../Collider/BoxCollider.h"
#include "../../Collider/SphereCollider.h"
#include <algorithm>
#include <cmath >
#include <limits>
CollisionController* CollisionController::instance_ = nullptr;

void CollisionController::CreateInstance(void)
{
    if (instance_ == nullptr)
    {
        instance_ = new CollisionController();
        instance_->Init();
    }
}

CollisionController& CollisionController::GetInstance(void)
{
    return *instance_;
}

void CollisionController::Destroy(void)
{
    delete instance_;
    instance_ = nullptr;
}

CollisionController::CollisionController(void)
    : updateTimer_(0.0f)
{
}

CollisionController::~CollisionController(void)
{
}

void CollisionController::Init(void)
{
    objects_.clear();
}

void CollisionController::RegisterObject(ObjectBase* obj) 
{
    if (!obj) return;
    objects_.push_back(obj);
}

void CollisionController::UnregisterObject(ObjectBase* obj)
{
    objects_.erase(std::remove(objects_.begin(), objects_.end(), obj), objects_.end());
}

void CollisionController::Update(void)
{
    updateTimer_ += SceneManager::GetInstance().GetDeltaTime();

    if (updateTimer_ >= UPDATE_INTERVAL)
    {
        updateTimer_ = 0.0f;
        UpdateCollisionPairs();
    }
}

// コライダペアの更新処理を分離
void CollisionController::UpdateCollisionPairs(void)
{
    if (objects_.size() < 2) { return; }

    for (size_t i = 0; i < objects_.size(); ++i)
    {
        auto* objA = objects_[i];

        objA->ClearHitCollider();

        for (size_t j = i + 1; j < objects_.size(); ++j)
        {
            auto* objB = objects_[j];

            for (auto const& [keyA, colA] : objA->GetOwnColliders())
            {
                if (!colA->IsValid()) { continue; }

                for (auto const& [keyB, colB] : objB->GetOwnColliders())
                {
                    if (!colB->IsValid()) { continue; }

                    if (IsCollisionEnabled(colA->GetTag(), colB->GetTag())) { continue; }

                    CollisionInfo info;

                    if (CheckCollision(colA, colB, info))
                    {
                        objA->AddHitCollider(colA);

                        objB->AddHitCollider(colB);
                    }
                    
                }
            }
        }
    }
}

bool CollisionController::CheckCollision(const ColliderBase* colA, const ColliderBase* colB, CollisionInfo& info)
{
    auto shapeA = colA->GetShape();

    auto shapeB = colB->GetShape();

    if (shapeA == ColliderBase::SHAPE::CIRCLE && shapeB == ColliderBase::SHAPE::CIRCLE)
    {
        return CheckCircleVsCircle(colA, colB, info);
    }

    if (shapeA == ColliderBase::SHAPE::BOX && shapeB == ColliderBase::SHAPE::BOX)
    {
        return CheckBoxVsBox(colA, colB, info);
    }

    if (shapeA == ColliderBase::SHAPE::CIRCLE && shapeB == ColliderBase::SHAPE::BOX)
    {
        return CheckCircleVsBox(colA, colB, info);
    }

    if (shapeA == ColliderBase::SHAPE::BOX && shapeB == ColliderBase::SHAPE::CIRCLE)
    {
        return CheckCircleVsBox(colA, colB, info);
    }

    return false;
}

bool CollisionController::CheckCircleVsBox(const ColliderBase* circle, const ColliderBase* box, CollisionInfo& outInfo)
{
    auto* b = static_cast<const BoxCollider*>(box);

    VECTOR boxPos = b->GetWorldPos();

    VECTOR circlePos = circle->GetWorldPos();

    float angle = b->GetFollow() ? b->GetFollow()->rot.z : 0.0f;

    float relX = circlePos.x - boxPos.x;

    float relY = circlePos.y - boxPos.y;

    float s = sinf(-angle);

    float c = cosf(-angle);

    float localX = relX * c - relY * s;

    float localY = relX * s + relY * c;

    VECTOR boxSize = b->GetSize();

    float halfWidth = boxSize.x / 2.0f;

    float halfHeight = boxSize.y / 2.0f;

    float closestX = std::max(-halfWidth, std::min(localX, halfWidth));

    float closestY = std::max(-halfHeight, std::min(localY, halfHeight));

    float dx = localX - closestX;

    float dy = localY - closestY;

    float distSq = dx * dx + dy * dy;

    float r = circle->GetRadius();

    if (distSq < r * r)
    {
        return true;
    }

    return false;
}

bool CollisionController::CheckBoxVsBox(const ColliderBase* boxA, const ColliderBase* boxB, CollisionInfo& outInfo)
{
    VECTOR posA = boxA->GetWorldPos();

    VECTOR posB = boxB->GetWorldPos();

    float dx = posA.x - posB.x;

    float dy = posA.y - posB.y;

    float distSq = dx * dx + dy * dy;

    auto* bA = static_cast<const BoxCollider*>(boxA);

    auto* bB = static_cast<const BoxCollider*>(boxB);

    float rA = VSize(bA->GetSize()) * 0.5f;

    float rB = VSize(bB->GetSize()) * 0.5f;

    return distSq < (rA + rB) * (rA + rB);
}

bool CollisionController::CheckCircleVsCircle(const ColliderBase* colA, const ColliderBase* colB, CollisionInfo& outInfo)
{
    // 2D座標(X, Y)のみで距離計算
    VECTOR posA = colA->GetWorldPos();
    VECTOR posB = colB->GetWorldPos();

    float dx = posA.x - posB.x;
    float dy = posA.y - posB.y;
    float distSq = dx * dx + dy * dy;

    float radiusSum = colA->GetRadius() + colB->GetRadius();

    if (distSq < radiusSum * radiusSum) {
        float dist = sqrtf(distSq);
        outInfo.hitNormal = (dist > 0) ? VGet(dx / dist, dy / dist, 0) : VGet(1, 0, 0);
        outInfo.penetration = radiusSum - dist;
        return true;
    }
    return false;
}

bool CollisionController::IsCollisionEnabled(ColliderBase::TAG tagA, ColliderBase::TAG tagB)
{
    // 2Dゲームで必要な組み合わせのみ true を返す
    if ((tagA == ColliderBase::TAG::PLAYER && tagB == ColliderBase::TAG::ENEMY) ||
        (tagA == ColliderBase::TAG::ENEMY && tagB == ColliderBase::TAG::PLAYER))
    {
        return true;
    }

    return false;
}

void CollisionController::Clear(void)
{
    objects_.clear();
}