#pragma once
#include <vector>
#include <memory>
#include <string>
#include <DxLib.h>

class EnemyBase;

class EnemyManager
{
	
public:

	EnemyManager();
	~EnemyManager();

	void Load();

	void Initialize();
	void Update(void);
	void Draw() ;
	void Release();


	int GetEnemyCount(void) const { return static_cast<int>(enemies_.size()); }
	void ApplyAreaDamage(const VECTOR& attackerPos, float range, int damage);
	
void DamageToTarget( int targetNo, int damage);

private:
		//異なる種類のエネミーを一括管理するため基礎kjラスのポインタ配列にする
	
		std::vector<std::shared_ptr<EnemyBase>> enemies_; // 生存しているエネミーのリスト
		std::vector<int> pendingExpRewards_;
		 
};

