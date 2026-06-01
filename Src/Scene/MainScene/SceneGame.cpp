#include "SceneGame.h"
#include "../../Manager/Generic/Camera.h"
#include "../../Manager/Generic/SceneManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../Manager/System/TimeManager.h"
#include "SceneScore.h"
#include "SceneTitle.h"
#include "../SubScene/PauseScene.h"
#include "../../Manager/System/Loading.h"
#include "../../Object/Character/Player/Player.h"
#include "../../Stage/StageBase.h"
#include "../../Object/Manager/EnemyManager.h"
#include"../../Object/Character/Enemy/Enemy.h"
#include "../../Object/Character/Enemy/EnemyBase.h"


// コンストラクタ
SceneGame::SceneGame(void)
	: player_(std::make_shared<Player>())
	,stage_(std::make_shared<StageBase>())
	, enemyManager_(std::make_unique<EnemyManager>())
{

}

// 読み込み
void SceneGame::Load()
{
	SceneBase::Load();

	// ここで必要なリソースを読み込む
	ResourceManager::GetInstance().InitGame();
	
	player_->InitLoad();

	enemyManager_->Load();

	stage_->Load();

	Loading::GetInstance()->SetProgress(45.0f);

	Loading::GetInstance()->SetProgress(60.0f);

	// サウンドの読み込み
	
	Loading::GetInstance()->SetProgress(80.0f);

	//時間カウントリセット
	TimeManager::GetInstance().Reset();

	Loading::GetInstance()->SetProgress(100.0f);
}

// 読み込み終了
void SceneGame::EndLoad()
{
	SceneBase::EndLoad();
}

// 初期化
void SceneGame::Init()
{
	// カメラ設定
	auto& camera = SceneManager::GetInstance().GetCamera();
	camera->ChangeMode(Camera::MODE::FIXED_POINT);

	player_->Init();

	stage_->Init();

	camera->SetFollowTarget(&player_->GetTransform());

	/*stageManager_->ChangeStage(std::make_shared<Lobby1F>());*/

	enemyManager_->Initialize();

	stage_->Init();
}

// 更新処理
void SceneGame::Update(void)
{
	auto& sound = SoundManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = TimeManager::GetInstance();
	auto& camera = SceneManager::GetInstance().GetCamera();
	auto loader = Loading::GetInstance();
	if (isGameClear_)
	{
		// クリア画面中の処理（タイトルに戻る入力など）をここに書けます
		if (input.IsTrgDown(KEY_INPUT_SPACE) || input.IsTrgMouseLeft())
		{
			SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>());
		}
		return; // クリア後は通常のゲーム更新（移動や攻撃）をすべてストップする
	}

	

	if (Loading::GetInstance()->IsLoading()) return;



	if (input.IsTrgDown(KEY_INPUT_ESCAPE))
	{
		SceneManager::GetInstance().PushScene(std::make_shared<PauseScene>());

		return;
	}

	//stageManager_->Update();

	player_->Update();

	enemyManager_->Update();

	stage_->Update();
	

	if (player_->IsQSkillTriggered())
	{
		if (enemyManager_->GetEnemyCount() > 0)
		{
			// 通常攻撃力の2倍（30 * 2 = 60ダメージ）を与える例
			int qDamage = player_->GetAttackDamage() * 2;

			
			// 0番のエネミーにEスキルのダメージを適用
			enemyManager_->DamageToTarget(0, qDamage);
			

			DxLib::printfDx("Qスキル発動！ 0番の敵に %d の大ダメージ！\n", qDamage);
		}
	}
	// 2. Eキー（通常のスキル攻撃）が押されたとき
	else if (player_->IsESkillTriggered())
	{
		if (enemyManager_->GetEnemyCount() > 0)
		{
			// 通常の攻撃力（30ダメージ）
			int eDamage = player_->GetAttackDamage();

			// 0番のエネミーにEスキルのダメージを適用
			enemyManager_->DamageToTarget(0, eDamage);
			
			DxLib::printfDx("Eスキル発動！ 0番の敵に %d のダメージ！\n", eDamage);
		}
	}
	// ─── ★敵が全員消えたかどうかのクリア判定 ───
	if (enemyManager_->GetEnemyCount() <= 0)
	{
		isGameClear_ = true; // 敵が0匹になったらクリア状態にする
	}
	
		


}

// 描画処理
void SceneGame::Draw(void)
{

	if (Loading::GetInstance()->IsLoading()) return;


	
	stage_->Draw();
	enemyManager_->Draw();
	player_->Draw();

	int winW, winH;
	GetWindowSize(&winW, &winH);

	// プレイヤーから現在のアイコン情報を取得
	int icon1 = player_->GetIconHandle();
	int icon2 = player_->GetIconHandle2();
	bool noDraw1 = player_->GetNoDrawFlag();
	bool noDraw2 = player_->GetNoDrawFlag2();

	int imgW1, imgH1, imgW2, imgH2;
	GetGraphSize(icon1, &imgW1, &imgH1);
	GetGraphSize(icon2, &imgW2, &imgH2);

	// UI配置用のレイアウト定数
	constexpr int UI_MARGIN = 20;
	constexpr int UI_SPACING = 15;

	float x1 = (float)winW - (imgW1 * 1.0f / 2.0f) - UI_MARGIN;
	float y1 = (float)winH - (imgH1 * 1.0f / 2.0f) - UI_MARGIN;

	// 1つ目のアイコン描画
	if (!noDraw1 && icon1 != -1)
	{
		DrawRotaGraph((int)x1, (int)y1, 1.0f, 0.0f, icon1, TRUE);
	}

	// 2つ目のアイコン描画
	if (!noDraw2 && icon2 != -1)
	{
		float x2 = x1 - (imgW1 * 1.0f / 2.0f) - UI_SPACING - (imgW2 * 0.7f / 2.0f);
		float y2 = y1;

		DrawRotaGraph((int)x2, (int)y2, 0.7f, 0.0f, icon2, TRUE);
	}


	int remainingEnemies = enemyManager_->GetEnemyCount();

	// 画面の左上に現在の敵の数を表示
	DrawFormatString(20, 20, GetColor(255, 255, 255), "残りエネミー数: %d", remainingEnemies);

	// もし敵の数が0になったら、画面中央にゲームクリアを表示
	if (isGameClear_)
	{
		int winW, winH;
		DxLib::GetWindowSize(&winW, &winH);

		// 文字のサイズを大きく設定
		DxLib::SetFontSize(64);

		int textX = (winW / 2) - 200; // 画面中央付近のX座標
		int textY = (winH / 2) - 50;  // 画面中央付近のY座標

		// GetColorエラーを100%回避するため、直接16進数（0xffd700 = 金色）で指定
		DxLib::DrawString(textX, textY, "GAME CLEAR!", 0xffd700);

		// サブメッセージの描画
		DxLib::SetFontSize(24);
		DxLib::DrawString((winW / 2) - 140, textY + 80,  "すべての敵を撃破した！",0xffffff);

		// 他の文字が巨大化しないように、フォントサイズを元の大きさに戻しておく
		DxLib::SetFontSize(16);
	}
	


	DrawFormatString(20, 20, 0xffffff, "残りエネミー数: %d", enemyManager_->GetEnemyCount());
#ifdef _DEBUG
	//デバック表示
	DrawDebug();
#endif // _DEBUG
}

// 解放処理
void SceneGame::Release(void)
{
	//if (stageManager_) stageManager_->Release();
}

// 描画(デバック)
void SceneGame::DrawDebug(void)
{
}