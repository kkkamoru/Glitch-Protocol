#include "Main.h"
#include "Scene.h"
#include "GameInit.h"
#include "PlayerInit.h"
#include "EnemyInit.h"
#include "BossInit.h"
#include "Sound.h"

#include "GameUpdate.h"

#include "Effect.h"

bool StageStart() {
	switch (sceneNum) {
	case SCENE_STAGE1:
		stage1Text.y++;
		if (stage1Text.y > gameSizeH / 2 - stage1Text.h / 2) {
			stage1Text.state = DIE;
			return true;
		}
		else {
			return false;
		}
		break;

	case SCENE_STAGE2:
		stage2Text.y += 2;
		if (stage2Text.y > 200) {
			stage2Text.state = DIE;
			return true;
		}
		else {
			return false;
		}
		break;
	}
}

// ターゲットカーソルの更新
void TargetCursorUpdate() {
	// マウスの位置にターゲットカーソルを移動させる
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();
	targetCursor.x = mouseX - targetCursor.w / 2;
	targetCursor.y = mouseY - targetCursor.h / 2;
	targetCursor.centerX = targetCursor.x + targetCursor.w / 2;
	targetCursor.centerY = targetCursor.y + targetCursor.h / 2;
}

// アイテムを出す処理
void SpownItem(float x, float y, BaseCharacter item[]) {
	for (int i = 0; i < ITEM_MAX; i++) {
		if (item[i].state == ACTIVE) return;
		// 左上座標をセット
		item[i].x = x - item[i].w / 2;
		item[i].y = y - item[i].h / 2;

		// center の更新
		item[i].centerX = item[i].x + item[i].w / 2;
		item[i].centerY = item[i].y + item[i].h / 2;

		item[i].state = ACTIVE;
	}
}

void ItemUpdateBase(BaseCharacter& item) {
	switch (sceneNum) {
	case SCENE_STAGE1:
		if (item.state == ACTIVE) {
			item.x--;
			if (item.x < 0) {
				item.state = INACTIVE;
			}
		}
		break;
	case SCENE_STAGE2:
		if (item.state == ACTIVE) {
			item.y++;
			if (item.y > gameSizeH) {
				item.state = INACTIVE;
			}
		}
		break;
	}
}

void ItemUpdate() {
	for (int i = 0; i < ITEM_MAX; i++) {
		ItemUpdateBase(aimItem[i]);
		ItemUpdateBase(threeWayItem[i]);
	}
}

// プレイヤーと敵が当たったか
bool CheckHitEnemiesToPlayer() {
	if (player.damageTimer > 0) return false;	// 無敵時間

	for (int i = 0; i < ENEMY_EYE_NUM; i++) {
		if (enemyEye[i].state != ACTIVE) continue;
		if (CheckBoxHit(player, enemyEye[i])) {
			player.hit = true;
		}
	}
	for (int j = 0; j < ENEMY_SHIELD_NUM; j++) {
		if (enemyShield[j].state != ACTIVE) continue;
		if (CheckBoxHit(player, enemyShield[j])) {
			player.hit = true;
		}
	}
	if (CheckCircleBoxHit(enemyRot.x, enemyRot.y, enemyRot.w / 2, player.x, player.y, player.w, player.h)) {
		if (enemyRot.state != ACTIVE) return false;
		player.hit = true;
	}
	if (CheckBoxHit(player, boss)) {
		if (boss.state != ACTIVE) return false;
		player.hit = true;
	}
	return player.hit;
}


// 敵の弾がプレイヤーに当たったか
bool CheckHitEnemyShotToPlayer() {
	for (int i = 0; i < ENEMY_SHOT_NUM; i++) {
		if (enemyShot[i].state == ACTIVE) {
			if (CheckBoxHit(player, enemyShot[i])) {
				enemyShot[i].state = INACTIVE;
				player.hit = true;
			}
		}
	}
	if (player.hit) HitSEPlay();
	return player.hit;
}

/// プレイヤーの弾が敵に当たったか : 1,2
bool CheckHitPlayerShotToEnemies() {
	bool hit = false;
	for (int i = 0; i < PLAYER_SHOT_NUM; i++) {
		if (playerShot[i].state != ACTIVE) continue;

		// 目の敵
		for (int j = 0; j < ENEMY_EYE_NUM; j++) {
			if (enemyEye[j].state != ACTIVE) continue;

			if (CheckBoxHit(playerShot[i], enemyEye[j])) {
				playerShot[i].state = INACTIVE;
				hit = true;
				enemyEye[j].hp--;
			}
		}

		// 盾の敵
		for (int j = 0; j < ENEMY_SHIELD_NUM; j++) {
			if (enemyShield[j].state != ACTIVE) continue;

			if (CheckBoxHit(playerShot[i], enemyShield[j])) {
				playerShot[i].state = INACTIVE;
				hit = true;
				enemyShield[j].hp--;
			}
		}

		// 回転の敵
		if (enemyRot.state != ACTIVE) continue;

		if (CheckBoxHit(playerShot[i], enemyRot)) {
			playerShot[i].state = INACTIVE;
			hit = true;
			enemyRot.hp--;
		}

		// ボス
		if (boss.state != ACTIVE) continue;
		if (CheckBoxHit(playerShot[i], boss)) {
			playerShot[i].state = INACTIVE;
			hit = true;
			boss.hp--;
		}
	}
	if (hit) {
		HitSEPlay();
	}
	return hit;
}

// アイテムとプレイヤーが当たったか : 1,2
bool CheckHitItemToPlayer() {
	bool hit = false;
	// エイムアイテム------------------------------------------
	for (int i = 0; i < ITEM_MAX; i++) {
		if (aimItem[i].state == ACTIVE) {
			if (CheckBoxHit(player, aimItem[i])) {
				aimItem[i].state = INACTIVE;
				hit = true;
				// アイテムを取った処理
				for (int j = 0; j < PLAYER_SHOT_NUM; j++) {
					playerShot[j].state = INACTIVE;
				}
				playerShotPattern = AIM_SHOT;
			}
		}
	}

	// ３方向アイテム------------------------------------------
	for (int i = 0; i < ITEM_MAX; i++) {
		if (threeWayItem[i].state == ACTIVE) {
			if (CheckBoxHit(player, threeWayItem[i])) {
				threeWayItem[i].state = INACTIVE;
				hit = true;
				// アイテムを取った処理
				for (int j = 0; j < PLAYER_SHOT_NUM; j++) {
					playerShot[j].state = INACTIVE;
				}
				playerShotPattern = THREE_WAY_SHOT;
			}
		}
	}

	if (hit) {
		ScoreUp(300);
		SpownPointEffect(player.x, player.y, +300);

		ItemSEPlay();
	}
	return hit;
}

// テキストの更新 : 1
void TextUpdate() {
	timeCount++;
	if (timeCount % 60 == 0) {
		second++;
	}

	if (scoreCount < 0)
		scoreCount = 0;

	switch (playerShotPattern) {
	case 0: sprintf_s(shot.text, "自動で発射！"); break;
	case 1: sprintf_s(shot.text, "マウスでねらって発射！"); break;
	case 2: sprintf_s(shot.text, "マウスクリックで発射！"); break;
	}

	sprintf_s(enemyAlive.text, "敵残り: %2d体",
		enemyAlive.enemyAliveCount);

	// スコア
	switch (sceneNum) {
	case SCENE_STAGE1:
		sprintf_s(score.text, "HP : %2d　score : %5d　time : %d", player.hp, scoreCount, second);
		break;

	case SCENE_STAGE2:
		sprintf_s(score.text,
			"HP:%2d\n\n"
			"score\n:%d\n\n"
			"time\n: %d",
			player.hp, scoreCount, second);
		break;
	}
}

//-----------------------------------------------------
// ステージ1クリア判定 : 1
void Stage1Clear() {
	for (int i = 0; i < ENEMY_SHIELD_NUM; i++) {
		if (enemyShield[i].state == ACTIVE) {
			return;
		}
	}
	for (int i = 0; i < ENEMY_EYE_NUM; i++) {
		if (enemyEye[i].state == ACTIVE) {
			return;
		}
	}

	sceneNext = SCENE_STAGE2;
	Stage1BGMStop();
}

bool clearMoveFlag = false;
// ステージ2クリア判定 : 2
void Stage2Clear() {
	if (boss.state == DIE) {
		enemyRot.state = INACTIVE;
		Stage2BGMStop();
		BossBGMStop();

		if (clearText.y < 0 - clearText.h + 1)
			ClearBGMPlay();

		if (clearText.y >= 250) {
			sceneNext = SCENE_CLEAR;
			clearMoveFlag = false;
		}
	}
}

// 背景の移動 : 1,2
void BackUpdate(Star stars[]) {
	switch (sceneNum) {
	case SCENE_STAGE1:
		for (int i = 0; i < STAR_NUM; i++) {
			stars[i].x -= stars[i].speed;
			if (stars[i].x < 0) {
				stars[i].x = screenW;
				stars[i].y = GetRand(screenH);
			}
		}

		for (int i = 0; i < BACK_NUM; i++) {
			sparkling[i].x -= 2;
			if (sparkling[i].x <= -1600) sparkling[i].x = 1600;
			loading[i].x -= 3;
			if (loading[i].x <= -1600) loading[i].x = 1600;
			errorWindow[i].x -= 1.5;
			if (errorWindow[i].x <= -1600) errorWindow[i].x = 1600;
			errorTriangle[i].x -= 2.5;
			if (errorTriangle[i].x <= -1600) errorTriangle[i].x = 1600;
		}
		break;

	case SCENE_STAGE2:
		for (int i = 0; i < STAR_NUM; i++) {
			stars[i].y += stars[i].speed;
			if (stars[i].y > screenH) {
				stars[i].y = 0;
				stars[i].x = GetRand(screenW);
			}
		}

		for (int i = 0; i < BACK_NUM; i++) {
			noiseBack[i].y += 5;
			if (noiseBack[i].y > screenH) noiseBack[i].y = -1600;
		}

		if (bossDieEffect[BOSS_DIE_EFFECT_NUM - 1].frame >= 5) {
			clearMoveFlag = true;
		}
		if (clearMoveFlag) {
			clearText.y++;
			if (clearText.y > 250) clearText.y = 250;
		}
		break;
	}
}

// ポイントの出現
void SpownPointEffect(float x, float y, int score) {
	for (int i = 0; i < POINT_EFFECT_NUM; i++) {
		PointEffect* pEffect = &pointEffect[i];
		if (pEffect->active == true) continue;
		pEffect->x = x;
		pEffect->y = y;
		pEffect->frame = 0;
		pEffect->active = true;
		sprintf_s(pEffect->text, "%d", score);
		break;
	}
}

// スコアの増減
void ScoreDown(int down) {
	scoreCount -= down;
	if (scoreCount < 0)
		scoreCount = 0;
}
void ScoreUp(int up) {
	scoreCount += up;
}

// 敵を倒したときのスコア
void KillScore(float x1, float y1, float x2, float y2, int score) {
	float distance = GetDistance(x1, y1, x2, y2);
	// 近くで倒すとスコアアップ
	if (distance < 150) {
		ScoreUp(score);
		SpownPointEffect(x1, y1, score);
	}
}

void ScoreUpdate() {
	if (timeCount % 600 == 0 && scoreCount > 0 && second != 0) {
		ScoreDown(50);
	}
}


// ポイントの更新
void PointEffectUpdate() {
	for (int i = 0; i < POINT_EFFECT_NUM; i++) {
		PointEffect* pEffect = &pointEffect[i];
		if (pEffect->active) {
			pEffect->frame++;
			pEffect->alpha -= 7;
			if (pEffect->alpha < 0) {
				pEffect->active = false;
				pEffect->alpha = 255;
			}
		}
	}
}