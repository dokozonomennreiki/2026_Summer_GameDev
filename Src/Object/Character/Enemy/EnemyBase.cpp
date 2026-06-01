#include "EnemyBase.h"
#include"../../../Manager/Generic/InputManager.h"
#include "../../../Manager/Generic/ResourceManager.h"
#include "../../../Collider/SphereCollider.h"
#include "../../Manager/EnemyManager.h"

EnemyBase::EnemyBase(void)
{
}

EnemyBase::EnemyBase(int modelHandle)
{
	trans_.modelId = modelHandle;
	
}

EnemyBase::~EnemyBase(void)
{
}

void EnemyBase::InitLoad(void)
{
	
}

void EnemyBase::InitTransform(void)
{
	
}

void EnemyBase::InitParameter(void)
{

	parameter_.maxHp = 100;

	parameter_.hp = 100;

	parameter_.attackDamage = 30;

	parameter_.turnSpeed = 15;

	parameter_.defense = 20;

}

void EnemyBase::UpdateProcessPost(void)
{
	trans_.Update();
}

void EnemyBase::InitCollider(void)
{
}



void EnemyBase::UpdateProcess(void)
{
}

int EnemyBase::GetHp(void)
{
	return parameter_.hp;
}

void EnemyBase::SetHp(int hp)
{
	parameter_.hp =hp;
	
}



void EnemyBase::Draw(void) const
{
	if (isAlive_) 
	{

		CharacterBase::Draw();
	}
    if (!isAlive_) return;

    // 1. 通常のエネミー3Dモデルを描画
    CharacterBase::Draw();

    // 2. HPバーを頭上に表示する処理
    // エネミーの足元座標（trans_.pos）から、頭上の位置を計算する（例: Y座標に+30.0fする）
    VECTOR headWorldPos = trans_.pos;
    headWorldPos.y += 30.0f; // エネミーのモデルの大きさに合わせて調整してください

    // 3D空間の座標を、画面上の2D座標（X, Y）に変換する
    VECTOR screenPos = ConvWorldPosToScreenPos(headWorldPos);

    // 画面外（カメラの後ろなど）にいる場合は描画しない
    if (screenPos.z >= 0.0f && screenPos.z <= 1.0f)
    {
        int barWidth = 50;   // 頭上用なので少し短めに
        int barHeight = 6;    // 少し細めに

        // バーがエネミーの真ん中に来るように、X座標を「幅の半分」だけ左にずらす
        int startX = static_cast<int>(screenPos.x) - (barWidth / 2);
        int startY = static_cast<int>(screenPos.y);

        // HP割合の計算
        float hpRate = static_cast<float>(parameter_.hp) / static_cast<float>(parameter_.maxHp);
        if (hpRate < 0.0f) hpRate = 0.0f;
        int currentBarWidth = static_cast<int>(barWidth * hpRate);

        // 背景（黒）
        DrawBox(startX, startY, startX + barWidth, startY + barHeight, GetColor(0, 0, 0), TRUE);
        // HP（緑や赤など、お好みで）
        if (currentBarWidth > 0)
        {
            DrawBox(startX, startY, startX + currentBarWidth, startY + barHeight, GetColor(0, 255, 0), TRUE);
        }
    }

}


