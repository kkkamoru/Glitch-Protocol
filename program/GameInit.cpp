#include "Main.h"
#include "Scene.h"
#include "EnemyInit.h"
#include "PlayerInit.h"
#include "Effect.h"

#include "GameInit.h"

//------------------------------text-----------------------------------
int scoreCount;
Text enemyAlive;
Text enemyAliveCount;

Text shot;
Text score;
int second;
int timeCount;
PointEffect pointEffect[POINT_EFFECT_NUM];

//------------------------------背景[1]-----------------------------------
int gameSizeW;
int gameSizeH;

BaseCharacter stage1Back;
BaseCharacter stage1Score;
const int BACK_NUM = 2;
BaseCharacter sparkling[BACK_NUM];
BaseCharacter loading[BACK_NUM];
BaseCharacter errorWindow[BACK_NUM];
BaseCharacter errorTriangle[BACK_NUM];

const int STAR_NUM = 20;
Star nearStar[STAR_NUM];
Star farStar[STAR_NUM];

BaseCharacter stage1Text;
//------------------------------背景[2]-----------------------------------
BaseCharacter stage2Back;
BaseCharacter stage2Score;
BaseCharacter noiseBack[BACK_NUM];

BaseCharacter stage2Text;
BaseCharacter clearText;
//------------------------------アイテム-----------------------------------
BaseCharacter aimItem[ITEM_MAX];
BaseCharacter threeWayItem[ITEM_MAX];

int continueScene;

//---------------------------------------------------------------------------------
// 初期化処理
//---------------------------------------------------------------------------------
// ゲーム全体の初期化 : 1,2
void GameInit() {
	switch (sceneNum) {
	case SCENE_STAGE1:
		screenW = 800;
		screenH = 450;
		SetGraphMode(screenW, screenH, 32);

		gameSizeW = screenW;
		gameSizeH = 400;

		continueScene = SCENE_STAGE1;

		break;

	case SCENE_STAGE2:
		screenW = 450;
		screenH = 800;
		SetGraphMode(screenW, screenH, 32);

		gameSizeW = 346;
		gameSizeH = screenH;

		continueScene = SCENE_STAGE2;
		break;

	case SCENE_CLEAR:
		screenW = 800;
		screenH = 450;
		SetGraphMode(screenW, screenH, 32);
		break;
	}
	LoadAll();
}
// 背景の初期化 : 1,2
void BackgroundInit() {
	switch (sceneNum) {
	case SCENE_STAGE1:
		stage1Back.x = 0.0f;
		stage1Back.y = 0.0f;
		stage1Back.centerX = stage1Back.x + stage1Back.w / 2;
		stage1Back.centerY = stage1Back.y + stage1Back.h / 2;
		stage1Back.w = screenW;
		stage1Back.h = screenH;

		stage1Score.x = 0.0f;
		stage1Score.y = 0.0f;
		stage1Score.centerX = stage1Score.x + stage1Score.w / 2;
		stage1Score.centerY = stage1Score.y + stage1Score.h / 2;
		stage1Score.w = screenW;
		stage1Score.h = screenH;

		for (int i = 0; i < BACK_NUM; i++) {
			sparkling[i].x = (i - 1) * 1600;
			sparkling[i].y = 0;
			sparkling[i].centerX = sparkling[i].x + sparkling[i].w / 2;
			sparkling[i].centerY = sparkling[i].y + sparkling[i].h / 2;
			sparkling[i].w = 1600;
			sparkling[i].h = 450;

			loading[i].x = (i - 1) * 1600;
			loading[i].y = 0;
			loading[i].centerX = loading[i].x + loading[i].w / 2;
			loading[i].centerY = loading[i].y + loading[i].h / 2;
			loading[i].w = 1600;
			loading[i].h = 450;

			errorWindow[i].x = (i - 1) * 1600;
			errorWindow[i].y = 0;
			errorWindow[i].centerX = errorWindow[i].x + errorWindow[i].w / 2;
			errorWindow[i].centerY = errorWindow[i].y + errorWindow[i].h / 2;
			errorWindow[i].w = 1600;
			errorWindow[i].h = 450;

			errorTriangle[i].x = (i - 1) * 1600;
			errorTriangle[i].y = 0;
			errorTriangle[i].centerX = errorTriangle[i].x + errorTriangle[i].w / 2;
			errorTriangle[i].centerY = errorTriangle[i].y + errorTriangle[i].h / 2;
			errorTriangle[i].w = 1600;
			errorTriangle[i].h = 450;
		}

		stage1Text.w = 372;
		stage1Text.h = 100;
		stage1Text.x = gameSizeW / 2 - stage1Text.w / 2;
		stage1Text.y = 0 - stage1Text.h;
		stage1Text.state = ACTIVE;

		for (int i = 0; i < STAR_NUM; i++) {
			nearStar[i].radius = 2.0f;
			nearStar[i].speed = 4.0f;

			farStar[i].radius = 1.0f;
			farStar[i].speed = 2.0f;
		}
		break;

	case SCENE_STAGE2:
		stage2Back.x = 0;
		stage2Back.y = 0;
		stage2Back.centerX = stage2Back.x + stage2Back.w / 2;
		stage2Back.centerY = stage2Back.y + stage2Back.h / 2;
		stage2Back.w = screenW;
		stage2Back.h = screenH;

		stage2Score.x = 0.0f;
		stage2Score.y = 0.0f;
		stage2Score.centerX = stage2Score.x + stage2Score.w / 2;
		stage2Score.centerY = stage2Score.y + stage2Score.h / 2;
		stage2Score.w = screenW;
		stage2Score.h = screenH;

		for (int i = 0; i < BACK_NUM; i++) {
			noiseBack[i].x = 0;
			noiseBack[i].y = 0;
			noiseBack[i].centerX = noiseBack[i].x + noiseBack[i].w / 2;
			noiseBack[i].centerY = noiseBack[i].y + noiseBack[i].h / 2;
			noiseBack[i].w = screenW;
			noiseBack[i].h = 1600;
		}

		stage2Text.w = 450;
		stage2Text.h = 100;
		stage2Text.x = 0;
		stage2Text.y = 0 - stage2Text.h;
		stage2Text.state = ACTIVE;

		clearText.w = 450;
		clearText.h = 98;
		clearText.x = 0;
		clearText.y = 0 - clearText.h;

		break;
	}

	for (int i = 0; i < STAR_NUM; i++) {
		nearStar[i].x = GetRand(screenW);
		nearStar[i].y = GetRand(screenH);

		farStar[i].x = GetRand(screenW);
		farStar[i].y = GetRand(screenH);
	}
}

// スコアの初期化
void ScoreInit() {
	for (int i = 0; i < POINT_EFFECT_NUM; i++) {
		PointEffect* pEffect = &pointEffect[i];
		pEffect->active = false;
		pEffect->alpha = 255;
	}
	switch (sceneNum) {
	case SCENE_STAGE1:
		score.x = 10;
		score.y = 410;
		scoreCount = 1000;
		second = 0;
		timeCount = 0;

		shot.x = 500;
		shot.y = 410;

		enemyAlive.x = 10;
		enemyAlive.y = 10;
		enemyAlive.enemyAliveCount = ENEMY_EYE_NUM + ENEMY_SHIELD_NUM;
		break;

	case SCENE_STAGE2:
		enemyAlive.enemyAliveCount = ENEMY_EYE_NUM + ENEMY_SHIELD_NUM;
		//enemyAlive.enemyAliveCount = 0;
		score.x = 370;
		score.y = 200;
		break;
	}
}

//------------------------------アイテム-----------------------------------
// アイテムの基本初期化
void ItemInitBase(BaseCharacter item) {
	item.x = 0;
	item.y = 0;
	item.w = 30;
	item.h = 30;
	item.centerX = item.x + item.w / 2;
	item.centerY = item.y + item.h / 2;
	item.state = INACTIVE;
}

// アイテムの初期化
void ItemInit() {
	switch (sceneNum) {
	case SCENE_STAGE1:
		for (int i = 0; i < ITEM_MAX; i++) {
			ItemInitBase(aimItem[i]);
		}

		for (int i = 0; i < ITEM_MAX; i++) {
			ItemInitBase(threeWayItem[i]);
		}
		break;

	case SCENE_STAGE2:
		for (int i = 0; i < ITEM_MAX; i++) {
			ItemInitBase(aimItem[i]);
		}
		for (int i = 0; i < ITEM_MAX; i++) {
			ItemInitBase(threeWayItem[i]);
		}
		break;
	}
}