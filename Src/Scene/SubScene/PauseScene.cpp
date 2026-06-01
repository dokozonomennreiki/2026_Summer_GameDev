
#include "PauseScene.h"
#include "../../Manager/Generic/SceneManager.h"
#include "../../Manager/Generic/InputManager.h"

PauseScene::PauseScene(void)
{
	pauseMenu_ = std::make_unique<PauseMenu>();
}

PauseScene::~PauseScene(void)
{
	
}

void PauseScene::Load(void)
{
	SceneBase::Load();
}

void PauseScene::EndLoad(void)
{
	SceneBase::EndLoad();
}

void PauseScene::Init(void)
{
	SceneBase::Init();

	if (pauseMenu_)
	{
		pauseMenu_->Show();
	}
}

void PauseScene::Update(void)
{
	if (pauseMenu_)
	{
		pauseMenu_->Update();

		if (!pauseMenu_->IsVisible())
		{
			SceneManager::GetInstance().PopScene();
		}
	}

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_ESCAPE))
	{
		SceneManager::GetInstance().PopScene();
	}
}

void PauseScene::Draw(void)
{
	if (pauseMenu_)
	{
		pauseMenu_->Draw();
	}
}

void PauseScene::Release(void)
{
	if (pauseMenu_)
	{
		pauseMenu_->Release();
	}
}