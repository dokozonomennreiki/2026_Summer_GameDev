#include "StageBase.h"
#include "../Object/Common/Transform.h"
#include"../Manager/Generic/ResourceManager.h"


StageBase::StageBase(void)
	: LimitMaxX_(0.0f)
	, LimitMinX_(0.0f)
	, LimitMaxY_(0.0f)
	, LimitMinY_(0.0f)
	,transform_(std::make_shared<Transform>())
{

}

StageBase::~StageBase(void)
{
}

void StageBase::Load(void)
{
	SceneBase::Load();
	transform_->modelId = ResourceManager::GetInstance().Load(ResourceManager::SRC::MODEL_GROUND).handleId_;

	transform_->pos = VGet(1, 1, 1);
	transform_->scl = VGet(1, 1, 1);

	transform_->Update();
	
}

void StageBase::EndLoad(void)
{
	SceneBase::EndLoad();
}

void StageBase::Init(void)
{
}

void StageBase::Update(void)
{
}

void StageBase::Draw(void)
{


	MV1DrawModel(transform_->modelId);

	DrawFormatString(0, 50, GetColor(255, 255, 255), "ステージ座標 (%d, %d, %d)", transform_->pos.x, transform_->pos.y, transform_->pos.z);
	DrawFormatString(0, 100, GetColor(255, 255, 255), "ステージID %d",transform_->modelId);
}

void StageBase::Release(void)
{
}

void StageBase::DebugDraw(void) const
{

}
