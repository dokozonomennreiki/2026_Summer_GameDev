#pragma once

#include "../Scene/SceneBase.h"
#include<memory>

class Transform;

class StageBase : public SceneBase
{
public:

	//@brief コンストラクタ
	StageBase(void);

	 ~StageBase(void) override;

	void Load(void) override;

	void EndLoad(void) override;

	 void Init(void) override ;

	 void Update(void) override ;

	 void Draw(void) override;

	 void Release(void) override ;

protected: 

	float LimitMinX_;

	float LimitMaxX_;

	float LimitMinY_;

	float LimitMaxY_;

	//トランスフォーム
	std::shared_ptr<Transform> transform_;

	virtual void DebugDraw(void) const;
};

