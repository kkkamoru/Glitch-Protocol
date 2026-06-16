#include "Main.h"
#include "Scene.h"
#include "GameOver.h"
#include "Shot.h"
#include "FontManager.h"

#include "GameInit.h"
#include "GameUpdate.h"
#include "GameRender.h"

#include "PlayerInit.h"
#include "PlayerUpdate.h"
#include "PlayerRender.h"

#include "EnemyInit.h"
#include "EnemyUpdate.h"
#include "EnemyRender.h"

#include "BossInit.h"
#include "BossUpdate.h"
#include "BossRender.h"

#include "Sound.h"
#include "Effect.h"
#include "Stage2.h"

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Stage2Init(bool all) {
	if (all == true) {
		GameInit();
		ScoreInit();
		BackgroundInit();
		PlayerInitAll();
		EnemyInitAll();
		BossInitAll();
		ItemInit();

		InitEffectNoise(&noise);

		Stage2BGMPlay();
	}
	else {
		GameInit();
		BackgroundInit();
		PlayerInitAll();
		EnemyInitAll();
		InitEffectNoise(&noise);
		Stage2BGMPlay();
	}
}

//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Stage2Update() {
	all = true;
	StageStart();
	TextUpdate();
	// 星
	BackUpdate(farStar);
	BackUpdate(nearStar);

	// プレイヤー
	PlayerUpdate();
	PlayerDamage();
	PlayerNormalShot();
	PlayerAimShot();
	PlayerThreeWayShot();

	// ターゲットカーソル
	TargetCursorUpdate();

	// 敵
	if (StageStart()) {
		EnemyShieldUpdate();
		EnemyEyeUpdate();
		EnemyRotUpdate();
	}

	// 敵の死亡エフェクト
	EnemyDieEffectUpdate();
	BossDieEffectUpdate();

	// アイテム
	ItemUpdate();

	// 当たり判定
	CheckHitEnemyShotToPlayer();
	CheckHitPlayerShotToEnemies();
	CheckHitEnemiesToPlayer();
	CheckHitItemToPlayer();

	ScoreUpdate();

	noise.pUpdateFunc(&noise);

	BossUpdate();

	Stage2Clear();
	PointEffectUpdate();

	WarningUpdate();
}

//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Stage2Render() {

	DrawBack();

	DrawItem();

	DrawEnemy();
	BossRender();
	DrawPlayer();

	// エイムショット用のカーソル
	if (playerShotPattern == AIM_SHOT) {
		Draw(targetCursor, 0.0);
	}
	PointEffectRender();


	if (stage2Text.state == ACTIVE)
		Draw(stage2Text, 0.0);
	Draw(clearText, 0.0);
	Draw(stage2Score, 0.0);


	DrawText();

	noise.pDrawFunc(&noise);
}

