#pragma once
#include"../../Scene/MainScene/SceneGame.h"

class CharacterBase;

class ControlDamage
{
public:
	// 構造体を使わず、引数で直接データを渡す
	static void ApplyDamage(
		CharacterBase*attacker
		,CharacterBase,int rawDamage
		, bool isCritical = false);

	// 環境ダメージ用
	static void ApplyDirectDamage(
		CharacterBase* defender, int damage);

};

