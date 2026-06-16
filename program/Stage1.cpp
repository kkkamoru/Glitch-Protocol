#include "Main.h"
#include "Shot.h"
#include "Scene.h"

#include "GameInit.h"
#include "GameUpdate.h"
#include "GameRender.h"

#include "PlayerInit.h"
#include "PlayerUpdate.h"
#include "PlayerRender.h"

#include "EnemyInit.h"
#include "EnemyUpdate.h"
#include "EnemyRender.h"

#include "Stage1.h"
#include "FontManager.h"

int fontHandle;

#include "Sound.h"
#include "Effect.h"

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Stage1Init(bool all)
{
	if (all == true) {
		GameInit();
		ScoreInit();
		BackgroundInit();

		// プレイヤー
		PlayerInitAll();
		// 敵
		EnemyInitAll();

		// アイテム
		ItemInit();

		InitEffectNoise(&noise);
		// サウンド
		Stage1BGMPlay();
	}
	else {
		GameInit();
		BackgroundInit();
		PlayerInitAll();
		EnemyInitAll();
		InitEffectNoise(&noise);
		Stage1BGMPlay();
	}
}

//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Stage1Update()
{
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
	if (StageStart() == true) {

		EnemyEyeUpdate();
		EnemyShieldUpdate();
	}

	// 敵の死亡エフェクト
	EnemyDieEffectUpdate();

	// アイテム
	ItemUpdate();

	// 当たり判定
	CheckHitEnemyShotToPlayer();
	CheckHitPlayerShotToEnemies();
	CheckHitEnemiesToPlayer();
	CheckHitItemToPlayer();

	// ステージクリア判定
	Stage1Clear();

	if (PushHitKey(KEY_INPUT_N)) {
		sceneNext = SCENE_STAGE2;
		Stage1BGMStop();
	}

	ScoreUpdate();
	PointEffectUpdate();
	noise.pUpdateFunc(&noise);
}


//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Stage1Render()
{
	DrawBack();

	DrawItem();
	DrawEnemy();
	DrawPlayer();

	// エイムショット用のカーソル
	if (playerShotPattern == AIM_SHOT) {
		Draw(targetCursor, 0.0);
	}

	PointEffectRender();

	Draw(stage1Score, 0.0);

	if (stage1Text.state == ACTIVE)
		Draw(stage1Text, 0.0);

	DrawText();


	noise.pDrawFunc(&noise);
}