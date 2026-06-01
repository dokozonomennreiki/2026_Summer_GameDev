#include "SceneScore.h"
#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/SceneManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../Manager/System/Loading.h"
#include "SceneTitle.h"
#include "../../Manager/System/TimeManager.h"
#include "../../Application.h"
#include "../SubScene/PauseScene.h"

SceneScore::SceneScore(void)
{
}

void SceneScore::Load(void)
{
    SceneBase::Load();
    // 時間カウントリセット
    TimeManager::GetInstance().Reset();

    ResourceManager::GetInstance().InitGameClear();

    Loading::GetInstance()->SetProgress(25.0f);

    //SoundManager::GetInstance().Add(SoundManager::TYPE::BGM, SoundManager::SOUND::BGM_SCORE, ResourceManager::GetInstance().Load(ResourceManager::SRC::BGM_SCORE).handleId_);

    Loading::GetInstance()->SetProgress(45.0f);

    Loading::GetInstance()->SetProgress(60.0f);

    Loading::GetInstance()->SetProgress(80.0f);

    Loading::GetInstance()->SetProgress(100.0f);

    // サウンドのリソース読み込み
    
}

void SceneScore::EndLoad(void)
{
    SceneBase::EndLoad();
}

void SceneScore::Init(void)
{
    // サウンド
    auto& res = ResourceManager::GetInstance();

    // 初期BGM
    //SoundManager::GetInstance().Play(SoundManager::SOUND::BGM_SCORE);

    // SceneManagerからゲーム統計を取得
    auto& sceneMgr = SceneManager::GetInstance();
    

}

void SceneScore::Update(void)
{
    auto& sound = SoundManager::GetInstance();
    auto& input = InputManager::GetInstance();
    auto& sceneMgr = SceneManager::GetInstance();

    if (input.IsTrgDown(KEY_INPUT_ESCAPE))
    {
        SceneManager::GetInstance().PushScene(std::make_shared<PauseScene>());

        return;
    }
}

void SceneScore::Draw(void)
{
    

#ifdef _DEBUG
    DrawDebug();
#endif
}

void SceneScore::Release(void)
{
}

void SceneScore::DrawDebug(void)
{
}