#pragma once
#include "DxLib.h"
#include "../SceneBase.h"
#include "../../Manager/Generic/StageManager.h"

#include "../../Object/Manager/EnemyManager.h"


class Player;
class StageBase;

class SceneGame : public SceneBase
{
public:
	// 制限時間（秒）
	static constexpr float LIMIT_TIME = 999.0f; // 5分

	// コンストラクタ
	SceneGame(void);

	// デストラクタ
	~SceneGame(void) = default;

	// 読み込み
	void Load(void) override;

	// 読み込み終了
	void EndLoad(void) override;

	// 初期化
	void Init(void) override;

	// 更新処理
	void Update(void) override;

	// 描画処理
	void Draw(void) override;

	// 解放処理
	void Release(void) override;


	// 今回のフレームでEスキル（アイコン1）を使ったか
	bool IsESkillTriggered(void) const { return isESkillTriggered_; }
	// 今回のフレームでQスキル（アイコン2）を使ったか
	bool IsQSkillTriggered(void) const { return isQSkillTriggered_; }




private:

	bool isESkillTriggered_ = false;
	bool isQSkillTriggered_ = false;


	int iconHandle_ = -1;
	int iconHandle2_ = -1;

	int currentDrawHandle_ = -1;
	bool isGameClear_ = false;
	bool NoDrawFlag = false;
	bool NoDrawFlag2 = false;
	float scale_ = 1.0f;
	static constexpr int UI_MARGIN = 10;

	static constexpr int UI_SPACING = 15;

	// プレイヤー
	std::shared_ptr<Player> player_;
	
	//ステージベース
	std::shared_ptr<StageBase> stage_;

	// エネミーベース
	std::unique_ptr<EnemyManager> enemyManager_;

	/*std::unique_ptr<StageManager> stageManager_;*/

	// 描画(デバック)
	void DrawDebug(void);
};