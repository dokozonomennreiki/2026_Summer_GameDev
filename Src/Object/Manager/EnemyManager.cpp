 	#include "EnemyManager.h"
	#include "../Character/Enemy/EnemyBase.h"
	#include "../Character/Enemy/Enemy.h"
	#include "../../Manager/Generic/ResourceManager.h"
    #include <memory>
    #include"../Character/Player/Player.h"

	EnemyManager::EnemyManager()
	{
		enemies_ = std::vector<std::shared_ptr<EnemyBase>>();
	}

	EnemyManager::~EnemyManager()
	{
		Release();
	}

	void EnemyManager::Load()
	{
		for (int i = 0; i < 3; ++i)
		{
			OutputDebugStringA(("エネミー生成ループ開始: " + std::to_string(i) + "\n").c_str());

			// ここで必要なリソースを読み込む
			int handle = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::MODEL_ENEMY);

			std::shared_ptr<EnemyBase> newEnemy = std::make_shared<Enemy>(handle);

			enemies_.push_back(newEnemy);

			OutputDebugStringA(("現在のリスト数: " + std::to_string(enemies_.size()) + "\n").c_str());
		}
		
	}

	void EnemyManager::Initialize()
	{
		for (int i = 0; i < 3; ++i)
		{
			OutputDebugStringA(("エネミー生成ループ開始: " + std::to_string(i) + "\n").c_str());
			
			// 等間隔に配置する座標を計算
			VECTOR currentPos = VGet(i *10.0f, 200.0f, 0.0f);
			currentPos.x += i * 100.0f;

			enemies_.at(i)->Init();
			enemies_.at(i)->SetPos(currentPos);
		
			OutputDebugStringA(("現在のリスト数: " + std::to_string(enemies_.size()) + "\n").c_str());
		}
	
	}

	void EnemyManager::Update(void)
	{

		for (auto it = enemies_.begin(); it != enemies_.end(); )
		{
			if (*it && !(*it)->IsAlive())
			{
				// 生存フラグがfalseならリストから削除
				it = enemies_.erase(it);
			}
			else
			{
				// 生きているなら次の要素へ
				++it;
			}
		}

		
		// すべてのエネミーの更新
		for (auto& enemy : enemies_)
		{
			if (enemy)
			{
				enemy->Update();
			}
		}
	
	}

	void EnemyManager::Draw()
	{	
		for (auto& enemy : enemies_)
		{
			
			enemy->Draw();
			
		}
#ifdef _DEBUG
		DrawFormatString(10, 100, GetColor(255, 255, 255), "Simple Enemies: %d", static_cast<int>(enemies_.size()));

#endif
	}

	void EnemyManager::Release()
	{
		for (auto& enemy : enemies_)
		{
			if(enemy)enemy->Release();
		}
		enemies_.clear();
	}

	void EnemyManager::ApplyAreaDamage(const VECTOR& attackerPos, float range, int damage)
	{
		for (auto& enemy : enemies_)
		{
			if (!enemy || !enemy->IsAlive()) continue; // ★死んでいる敵は無視

			VECTOR toEnemy = VSub(enemy->GetPos(), attackerPos);
			float distSq = VSquareSize(toEnemy);
			float rangeSq = range * range;

			if (distSq <= rangeSq)
			{
				int currentHp = enemy->GetHp();
				int newHp = currentHp - damage;

				if (newHp <= 0)
				{
					enemy->SetHp(0);
					enemy->SetIsAlive(false); // ★範囲攻撃で死んだら生存フラグをfalseに
				}
				else
				{
					enemy->SetHp(newHp);
				}
				printfDx("敵に %d のダメージ！ 残りHP: %d\n", damage, enemy->GetHp());
			}
		}
	}

	void EnemyManager::DamageToTarget( int targetNo, int damage)
	{
		if (targetNo < 0 || targetNo >= static_cast<int>(enemies_.size()))
		{
			//
			return;
		}

		// 2. リストから指定された番号のエネミー（スマートポインタ）を取り出す
		auto& targetEnemy = enemies_[targetNo];
		if (!targetEnemy) return;

		// 3. 敵の現在のHPを取得してダメージ分を減らす
		int currentHp = targetEnemy->GetHp();
		int newHp = currentHp - damage;

		if (newHp > 0)
		{
			// まだ生きている場合は新しいHPを設定
			targetEnemy->SetHp(newHp);

			// 画面へのデバッグ表示（確認用）
			printfDx("番号 %d の敵に %d ダメージ！残りHP: %d\n", targetNo, damage, targetEnemy->GetHp());
		}
		else
		{
			targetEnemy->SetIsAlive(false); // ★HPが0以下になったら生存フラグをfalseにす
			// 4. HPが0以下になったら消滅（リストから削除）させる処理
			// std::shared_ptr（スマートポインタ）なので、eraseするだけで自動的にメモリからも消滅
			enemies_.erase(enemies_.begin() + targetNo);

			printfDx("番号 %d の敵のHPが0になったため消滅しました。\n", targetNo);
		}
	}
