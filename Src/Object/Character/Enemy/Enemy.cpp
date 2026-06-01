#include "Enemy.h"
#include "../../../Manager/Generic/ResourceManager.h"

Enemy::Enemy(void)
	: EnemyBase(-1)
{
}

Enemy::Enemy(int modelHandle)
	:EnemyBase(modelHandle)
{
	trans_.modelId = MV1DuplicateModel(modelHandle);
}

Enemy::~Enemy(void)
{
}

void Enemy::InitLoad(void)
{

}

void Enemy::InitTransform(void)
{
	//trans_.pos = VGet(90.0f, 200.0f, 700.0f);
}

void Enemy::InitCollider(void)
{
}

void Enemy::Draw(void) const
{
	EnemyBase::Draw();
}

void Enemy::UpdateProcess(void)
{
	isGround_ = true;
	velocity_.y = 0.0f;
}

void Enemy::InitParameter(void)
{
	EnemyBase::InitParameter();
}

void Enemy::UpdateProcessPost(void)
{
}
