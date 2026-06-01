#include "EnemyCommon.h"
#include "../../../Manager/Generic/ResourceManager.h"

EnemyCommon::EnemyCommon(void)
	:EnemyBase(-1)
{
}

EnemyCommon::EnemyCommon(int modelHandle)
	:EnemyBase(modelHandle)
{
	trans_.modelId = modelHandle;

}
EnemyCommon::~EnemyCommon(void)
{
}

void EnemyCommon::InitLoad(void)
{
}

void EnemyCommon::InitTransform(void)
{
	trans_.pos = VGet(90.0f, 200.0f, 700.0f);
}

void EnemyCommon::InitCollider(void)
{
}

void EnemyCommon::Draw(void) const
{
	EnemyBase::Draw();
}

void EnemyCommon::UpdateProcess(void)
{
}

void EnemyCommon::InitParameter(void)
{
	EnemyBase::InitParameter();
}

void EnemyCommon::UpdateProcessPost(void)
{
}
