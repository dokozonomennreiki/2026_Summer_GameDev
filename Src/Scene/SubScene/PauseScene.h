#pragma once
#include "../SceneBase.h"
#include "../../DrawUI/SceneUI/PauseMenu.h"
#include <memory>
class PauseScene : public SceneBase
{
public:
	PauseScene(void);

	virtual ~PauseScene(void) override;

	virtual void Load(void) override;

	virtual void EndLoad(void) override;

	virtual void Init(void) override;

	virtual void Update(void) override;
	
	virtual void Draw(void) override;

	virtual void Release(void) override;

private:

	std::unique_ptr<PauseMenu> pauseMenu_;
};

