#include "Source.h"
#include "Scene.h"
#include "GameInit.h"
#include "PlayerInit.h"

//------------------------------プレイヤー-----------------------------------
Player player;
PlayerPattern playerPattern;
PlayerShotPattern playerShotPattern;

// エフェクト
BaseCharacter playerEffect;
int effectChangeCount;						// プレイヤーのエフェクトを時間で変化させる
int playerEffectAngle;						// 回転角度

int playerEffectSrcX[PLAYER_MAX] =
{ -1,0,22,44,66,0,22,44,66 };				// 横幅の切り出し位置

//------------------------------弾(プレイヤー)----------------------------
Shot playerShot[PLAYER_SHOT_NUM];
float playerShotDirX[PLAYER_SHOT_NUM];		// 弾の進む方向
float playerShotDirY[PLAYER_SHOT_NUM];

BaseCharacter targetCursor;				// エイムショット用のカーソル

// プレイヤーの初期化
void PlayerInit() {
	switch (sceneNum) {
	case SCENE_TITLE:
		player.hp = 10;
		player.speed = 4.0f;
		player.x = 562.0f;
		player.y = 105.0f;
		player.w = 20;
		player.h = 20;
		player.centerX = player.x + player.w / 2;
		player.centerY = player.y + player.h / 2;

		player.state = ACTIVE;

	case SCENE_STAGE1:
		player.x = 100.0f;
		player.y = gameSizeH / 2;
		player.hp = 10;

		break;

	case SCENE_STAGE2:
		player.x = screenW / 2;
		player.y = 700;

		break;
	}
	player.damageTimer = 0;
	player.flashTimer = 0;
	player.shotTimer = -1;
	player.hit = false;
}
// プレイヤーエフェクトの初期化
void PlayerEffectInit() {
	playerEffect.x = 0.0f;
	playerEffect.y = 0.0f;
	playerEffect.centerX = playerEffect.x + playerEffect.w / 2;
	playerEffect.centerY = playerEffect.y + playerEffect.h / 2;
	playerEffect.w = 21;
	playerEffect.h = 30;

	effectChangeCount = 0;
	playerPattern = PLAYER_STAND;
	playerEffectAngle = 0;
}
// プレイヤーの弾の初期化
void PlayerShotInit(bool all) {
	for (int i = 0; i < PLAYER_SHOT_NUM; i++) {
		playerShot[i].x = 0.0f;
		playerShot[i].y = 0.0f;
		playerShot[i].w = 20;
		playerShot[i].h = 20;

		playerShot[i].speed = 10.0f;
		playerShot[i].state = INACTIVE;
		playerShotDirX[i] = 0;
		playerShotDirY[i] = 0;
	}
	// エイムショット用のカーソル
	targetCursor.x = 0.0f;
	targetCursor.y = 0.0f;
	targetCursor.w = 50;
	targetCursor.h = 50;
	targetCursor.centerX = targetCursor.x + targetCursor.w / 2;
	targetCursor.centerY = targetCursor.y + targetCursor.h / 2;

	switch (sceneNum) {
	case SCENE_TITLE:
		playerShotPattern = AIM_SHOT;
		break;
	case SCENE_STAGE1:
		if (all) {
			// 弾は通常ショットから開始
			playerShotPattern = NORMAL_SHOT;
		}
		break;
	}
}

//-------------------------------
// : 1,2
void PlayerInitAll() {
	PlayerInit();
	PlayerEffectInit();
	PlayerShotInit(all);
}
//-------------------------------
