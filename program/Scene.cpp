#include "Main.h"
#include "FontManager.h"

#include "PlayerInit.h"
#include "EnemyInit.h"
#include "GameInit.h"
#include "BossInit.h"

#include "Title.h"
#include "Option.h"
#include "Stage1.h"
#include "Stage2.h"
#include "GameOver.h"
#include "Ranking.h"
#include "OP.h"
#include "Clear.h"

#include "Sound.h"
#include "Scene.h"
int sceneNum;
int sceneNext;
bool continueFlag = false;

int screenW = 800;
int screenH = 450;



//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void LoadAll() {


	// フォント
	LoadFonts();

	//------------------------------プレイヤー-----------------------------------
	player.image = LoadGraph("data/player.png");

	//------------------------------エフェクト--------------------------------
	playerEffect.image = LoadGraph("data/effect/playerEffect.png");

	//------------------------------ターゲットカーソル---------------------------
	targetCursor.image = LoadGraph("data/effect/targetCursor.png");

	//------------------------------敵の死亡エフェクト------------------------
	for (int i = 0; i < ENEMY_DIE_EFFECT_NUM; i++) {
		enemyDieEffect[i].image = LoadGraph("data/effect/enemyDieEffect.png");
	}

	for (int i = 0; i < BOSS_DIE_EFFECT_NUM; i++) {
		bossDieEffect[i].image = LoadGraph("data/effect/bossDieEffect.png");
	}

	//------------------------------敵------------------------------------------
	for (int i = 0; i < ENEMY_SHIELD_NUM; i++) {
		enemyShield[i].image = LoadGraph("data/enemyShield.png");
	}
	for (int i = 0; i < ENEMY_EYE_NUM; i++) {
		enemyEye[i].image = LoadGraph("data/enemyEye.png");
	}
	enemyRot.image = LoadGraph("data/enemyRot.png");

	boss.images[0] = LoadGraph("data/boss/boss1.png");
	boss.images[1] = LoadGraph("data/boss/boss2.png");
	boss.images[2] = LoadGraph("data/boss/boss3.png");

	//------------------------------弾------------------------------------------
	for (int i = 0; i < ENEMY_SHOT_NUM; i++) {
		enemyShot[i].image = LoadGraph("data/enemyShot.png");
	}
	for (int i = 0; i < PLAYER_SHOT_NUM; i++) {
		playerShot[i].image = LoadGraph("data/playerShot.png");
	}

	//-----------------------------アイテム----------------------------------------
	for (int i = 0; i < ITEM_MAX; i++) {
		aimItem[i].image = LoadGraph("data/effect/aimItem.png");
	}
	for (int i = 0; i < ITEM_MAX; i++) {
		threeWayItem[i].image = LoadGraph("data/effect/threeWayItem.png");
	}

	//----------------------------タイトル--------------------------------------
	titleBack.image = LoadGraph("data/titleBack.png");

	//----------------------------オプション------------------------------------
	optionBack.image = LoadGraph("data/optionBack.png");

	//-----------------------------[1]背景----------------------------------------
	stage1Back.image = LoadGraph("data/stageBack/Stage1Back.png");
	for (int i = 0; i < BACK_NUM; i++) {
		sparkling[i].image = LoadGraph("data/stageBack/sparkling.png");
		loading[i].image = LoadGraph("data/stageBack/loading.png");
		errorWindow[i].image = LoadGraph("data/stageBack/errorWindow.png");
		errorTriangle[i].image = LoadGraph("data/stageBack/errorTriangle.png");
	}

	stage1Score.image = LoadGraph("data/stageBack/stage1Score.png");
	stage1Text.image = LoadGraph("data/stageBack/stage1Text.png");

	//-----------------------------[2]背景----------------------------------------
	stage2Back.image = LoadGraph("data/stageBack/Stage2Back.png");
	for (int i = 0; i < BACK_NUM; i++) {
		noiseBack[i].image = LoadGraph("data/stageBack/noiseBack.png");
	}

	stage2Text.image = LoadGraph("data/stageBack/stage2Text.png");
	clearText.image = LoadGraph("data/stageBack/clearText.png");
	stage2Score.image = LoadGraph("data/stageBack/stage2Score.png");

	warning.image = LoadGraph("data/warning.png");

	//------------------------------ゲームオーバー-------------------------------
	gameOverBack.image = LoadGraph("data/gameOverBack.png");

	//----------------------------クリア------------------------------------
	clearBack.image = LoadGraph("data/clearBack.png");

	//------------------------------ランキング--------------------------------
	rankingBack.image = LoadGraph("data/rankingBack.png");

	//------------------------------サウンド--------------------------------
	stage1BGM = LoadSoundMem("data/sound/stage1BGM.mp3");
	stage2BGM = LoadSoundMem("data/sound/stage2BGM.mp3");
	bossBGM = LoadSoundMem("data/sound/bossBGM.mp3");
	clearBGM = LoadSoundMem("data/sound/clearBGM.mp3");
	shotSE = LoadSoundMem("data/sound/shotSE.mp3");
	itemSE = LoadSoundMem("data/sound/itemSE.mp3");
	selectSE = LoadSoundMem("data/sound/selectSE.mp3");
	warningSE = LoadSoundMem("data/sound/warningSE.mp3");
	hitSE = LoadSoundMem("data/sound/hitSE.mp3");
	tipingSE = LoadSoundMem("data/sound/tipingSE.mp3");
}

void SceneInit()
{
	sceneNum = SCENE_OP;
	sceneNext = SCENE_OP;

	LoadAll();

	OPInit();

	for (int i = 0; i < SCORE_MAX; i++) {
		scores[i] = 0;
	}

}

//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
bool all = true;
void SceneUpdate() {
	if (sceneNum != sceneNext) {

		if ((sceneNum == SCENE_GAMEOVER && sceneNext == SCENE_STAGE1) ||
			(sceneNum == SCENE_GAMEOVER && sceneNext == SCENE_STAGE2)) {
			// コンティニューの時は全ては初期化しない
			all = false;
		}

		sceneNum = sceneNext;

		switch (sceneNum) {
		case SCENE_OP:
			OPInit();
			break;
		case SCENE_TITLE:
			TitleInit();
			break;
		case SCENE_STAGE1:
			Stage1Init(all);
			break;
		case SCENE_STAGE2:
			Stage2Init(all);
			break;
		case SCENE_GAMEOVER:
			GameOverInit();
			break;

		case SCENE_CLEAR:
			ClearInit();
			break;

		case SCENE_RANKING:
			RankingInit();
			break;

		case SCENE_OPTION:
			OptionInit();
			break;
		}
	}

	switch (sceneNum) {
	case SCENE_OP:
		OPUpdate();
		break;
	case SCENE_TITLE:
		TitleUpdate();
		break;
	case SCENE_STAGE1:
		Stage1Update();
		break;
	case SCENE_STAGE2:
		Stage2Update();
		break;
	case SCENE_GAMEOVER:
		GameOverUpdate();
		break;
	case SCENE_CLEAR:
		ClearUpdate();
		break;
	case SCENE_RANKING:
		RankingUpdate();
		break;
	case SCENE_OPTION:
		OptionUpdate();
		break;
	}

}

//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void SceneRender() {
	switch (sceneNum) {
	case SCENE_OP:
		OPRender();
		break;
	case SCENE_TITLE:
		TitleRender();
		break;
	case SCENE_STAGE1:
		Stage1Render();
		break;
	case SCENE_STAGE2:
		Stage2Render();
		break;
	case SCENE_GAMEOVER:
		GameOverRender();
		break;
	case SCENE_CLEAR:
		ClearRender();
		break;
	case SCENE_RANKING:
		RankingRender();
		break;
	case SCENE_OPTION:
		OptionRender();
		break;
	}
}

//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void SceneExit()
{
	// 読み込んだ順に書く
	//------------------------------プレイヤー-----------------------------------
	DeleteGraph(player.image);
	//------------------------------エフェクト--------------------------------
	DeleteGraph(playerEffect.image);
	//------------------------------ターゲットカーソル---------------------------
	DeleteGraph(targetCursor.image);
	//------------------------------敵の死亡エフェクト------------------------
	for (int i = 0; i < ENEMY_DIE_EFFECT_NUM; i++) {
		DeleteGraph(enemyDieEffect[i].image);
	}
	for (int i = 0; i < BOSS_DIE_EFFECT_NUM; i++) {
		DeleteGraph(bossDieEffect[i].image);
	}
	//------------------------------敵------------------------------------------
	for (int i = 0; i < ENEMY_SHIELD_NUM; i++) {
		DeleteGraph(enemyShield[i].image);
	}
	for (int i = 0; i < ENEMY_EYE_NUM; i++) {
		DeleteGraph(enemyEye[i].image);
	}
	DeleteGraph(enemyRot.image);

	DeleteGraph(boss.images[0]);
	DeleteGraph(boss.images[1]);
	DeleteGraph(boss.images[2]);

	//------------------------------弾------------------------------------------
	for (int i = 0; i < ENEMY_SHOT_NUM; i++) {
		DeleteGraph(enemyShot[i].image);
	}
	for (int i = 0; i < PLAYER_SHOT_NUM; i++) {
		DeleteGraph(playerShot[i].image);
	}
	//-----------------------------アイテム----------------------------------------
	for (int i = 0; i < ITEM_MAX; i++) {
		DeleteGraph(aimItem[i].image);
	}
	for (int i = 0; i < ITEM_MAX; i++) {
		DeleteGraph(threeWayItem[i].image);
	}
	//----------------------------タイトル--------------------------------------
	DeleteGraph(titleBack.image);		// タイトル背景
	//----------------------------オプション------------------------------------
	DeleteGraph(optionBack.image);
	//-----------------------------[1]背景----------------------------------------
	DeleteGraph(stage1Back.image);
	for (int i = 0; i < BACK_NUM; i++) {
		DeleteGraph(sparkling[i].image);
		DeleteGraph(loading[i].image);
		DeleteGraph(errorWindow[i].image);
		DeleteGraph(errorTriangle[i].image);
	}
	DeleteGraph(stage1Score.image);
	DeleteGraph(stage1Text.image);
	//-----------------------------[2]背景----------------------------------------
	DeleteGraph(stage2Back.image);
	for (int i = 0; i < BACK_NUM; i++) {
		DeleteGraph(noiseBack[i].image);
	}
	DeleteGraph(stage2Text.image);
	DeleteGraph(clearText.image);
	DeleteGraph(stage2Score.image);
	DeleteGraph(warning.image);
	//------------------------------ゲームオーバー-------------------------------
	DeleteGraph(gameOverBack.image);

	//----------------------------クリア------------------------------------
	DeleteGraph(clearBack.image);
	//------------------------------ランキング--------------------------------
	DeleteGraph(rankingBack.image);
	//------------------------------サウンド--------------------------------
	DeleteGraph(stage1BGM);
	DeleteGraph(stage2BGM);
	DeleteGraph(clearBGM);
	DeleteGraph(bossBGM);
	DeleteGraph(shotSE);
	DeleteGraph(itemSE);
	DeleteGraph(selectSE);
	DeleteGraph(warningSE);
	DeleteGraph(hitSE);
	DeleteGraph(tipingSE);

	DeleteFonts();
}