#include "Main.h"
#include "Scene.h"

#include "GameInit.h"
#include "GameUpdate.h"
#include "GameRender.h"

#include "EnemyInit.h"
#include "EnemyUpdate.h"

#include "PlayerInit.h"

#include "Shot.h"

// 敵が死んだときにエフェクトを出す
void SpawnEnemyDieEffect(int x, int y, EnemyType type) {

	// １．まず敵が死んだときにエフェクトを出す。
	//		非アクティブのエフェクトを探して、再生させる。
	for (int i = 0; i < ENEMY_DIE_EFFECT_NUM; i++) {
		EnemyDieEffect* pEffect = &enemyDieEffect[i];
		if (pEffect->state == ACTIVE) continue;

		pEffect->state = ACTIVE;
		pEffect->x = x - pEffect->w / 2;
		pEffect->y = y - pEffect->h / 2;
		pEffect->centerX = pEffect->x + pEffect->w / 2;
		pEffect->centerY = pEffect->y + pEffect->h / 2;
		pEffect->frame = 0;
		pEffect->timer = 0;

		pEffect->enemyType = type;

		return;
	}
}

// 敵が死んだときの処理
bool EnemyDie(Enemy& enemy) {
	if (enemy.state != ACTIVE) return false;
	if (enemy.hp < 0) {
		enemy.hp = 0;
		KillScore(enemy.x, enemy.y, player.x, player.y, 500);
		enemy.state = DIE;

		// 死んだときのエフェクトを出す
		SpawnEnemyDieEffect(enemy.centerX, enemy.centerY, enemy.enemyType);
		if (enemy.enemyType == ENEMY_SHIELD)
			enemyAlive.enemyAliveCount--;
		if (enemy.enemyType == ENEMY_EYE)
			enemyAlive.enemyAliveCount--;

		return true;
	}
	return false;
}

// 敵の死亡エフェクトの更新 : 1,2
void EnemyDieEffectUpdate() {
	for (int i = 0; i < ENEMY_DIE_EFFECT_NUM; i++) {
		EnemyDieEffect* pEffect = &enemyDieEffect[i];
		if (pEffect->state != ACTIVE) continue;

		pEffect->timer++;

		// 60フレームごとにframeを進める
		if (pEffect->timer % 3 == 0) {
			pEffect->frame++;
			if (pEffect->frame > 5) {
				// エフェクトの再生が終わった後に、アイテムを出す
				if (pEffect->enemyType == ENEMY_EYE) {
					int rand = GetRand(100);
					if (rand < 30) {
						SpownItem(pEffect->centerX, pEffect->centerY, aimItem);
					}
				}
				if (pEffect->enemyType == ENEMY_ROT) {
					int rand = GetRand(100);
					SpownItem(pEffect->centerX, pEffect->centerY, threeWayItem);
				}
				// ここでのみINACTIVEにする
				pEffect->state = INACTIVE;
				pEffect->frame = 0;
				pEffect->timer = 0;
			}
		}
	}
}

int moveTimer = GetRand(300);
// 盾の敵のアップデート : 1,2
void EnemyShieldUpdate() {
	for (int i = 0; i < ENEMY_SHIELD_NUM; i++) {
		Enemy* pEnemy = &enemyShield[i];
		if (pEnemy->state == DIE) continue;

		// 画面外にいるときは、当たり判定が反応しないように死んでいる判定にする。
		if (sceneNum == SCENE_STAGE1) {
			if (pEnemy->x > gameSizeW &&	// 右側
				pEnemy->y > gameSizeH)	// 下側
			{
				pEnemy->state = INACTIVE;
			}
			else {
				pEnemy->state = ACTIVE;
			}

			// 移動モードの切り替え
			moveTimer--;
			if (moveTimer < 0) {
				pEnemy->enemyMoveMode = (EnemyMoveMode)((pEnemy->enemyMoveMode + 1) % MODE_NUM);
				moveTimer = GetRand(300);
			}

			// 移動
			if (pEnemy->enemyMoveMode == 0) {	// 右に移動
				pEnemy->x += pEnemy->speed;
			}
			if (pEnemy->enemyMoveMode == 1) {	// 左下に移動
				pEnemy->x -= pEnemy->speed;
				pEnemy->y += pEnemy->speed;
			}

			// 画面端に来たら反対側に出現させる
			if (pEnemy->x > gameSizeW)	pEnemy->x = 0 - pEnemy->w;
			if (pEnemy->x + pEnemy->w < 0)	pEnemy->x = gameSizeW;
			if (pEnemy->y > gameSizeH)	pEnemy->y = 0 - pEnemy->h;
			if (pEnemy->y + pEnemy->h < 0)	pEnemy->y = gameSizeH;

		}
		else if (sceneNum == SCENE_STAGE2) {
			if (pEnemy->y < 0 &&	// 上側
				pEnemy->x > gameSizeW)	// 右側
			{
				pEnemy->state = INACTIVE;
			}
			else {
				pEnemy->state = ACTIVE;
			}
			// 移動
			pEnemy->y += pEnemy->speed;
			pEnemy->x += pEnemy->speed * pEnemy->dir;
			// 左右に移動
			if (pEnemy->x < 0.0) {
				pEnemy->x = 0.0;
				pEnemy->dir = 1;
			}
			if (pEnemy->x + pEnemy->w > gameSizeW) {
				pEnemy->x = gameSizeW - pEnemy->w;
				pEnemy->dir = -1;
			}

			// 画面外に出たら、再出現させる
			if (pEnemy->y > gameSizeH) {
				pEnemy->x = GetRand(gameSizeW - pEnemy->w);
				pEnemy->y = -pEnemy->h;
			}
		}

		// センターを更新
		pEnemy->centerX = pEnemy->x + pEnemy->w / 2;
		pEnemy->centerY = pEnemy->y + pEnemy->h / 2;

		// 敵を倒した処理
		if (pEnemy->state == ACTIVE) {
			EnemyDie(enemyShield[i]);
		}
	}
}

void EnemyShotUpdate() {
	for (int i = 0; i < ENEMY_SHOT_NUM; i++) {
		Shot* pShot = &enemyShot[i];
		ObjectHoming(
			&pShot->angle,
			pShot->x, pShot->y,
			player.x, player.y);
	}
}

// 目の敵のアップデート : 1,2
void EnemyEyeUpdate() {
	for (int i = 0; i < ENEMY_EYE_NUM; i++) {
		Enemy* pEnemy = &enemyEye[i];
		for (int j = 0; j < CREATE_EFFECT_NUM; j++) {
			EnemyEyeCreateEffect* pEffect = &pEnemy->createEffect[j];

			// 敵がアクティブでないときはエフェクトも非アクティブにする
			if (pEnemy->state != ACTIVE) {
				pEffect->isActive = false;
			}

			if (pEnemy->state == DIE) continue;

			// 出現するまでの時間
			pEnemy->createTimer--;
			if (pEnemy->createTimer > 0) {
				pEnemy->state = INACTIVE;
			}
			else {
				// 出現エフェクト
				pEffect->isActive = true;
				pEffect->x = pEnemy->centerX;
				pEffect->y = pEnemy->centerY;
				pEffect->size += 2 + j;	// 波紋になるように大きさを変化
				pEffect->alpha -= 5 + j;
				pEnemy->state = ACTIVE;
				pEnemy->alpha++;
				ClampPosition(enemyEye[i], gameSizeW, gameSizeH);
			}
			if (pEffect->alpha <= 0)
			{
				pEffect->isActive = false;
			}
		}

		if (pEnemy->enemyMoveMode == TURN) {
			// 敵から見たプレイヤーの方向
			ObjectHoming(
				&pEnemy->angle,
				pEnemy->x, pEnemy->y,
				player.x, player.y);

			speedX[i] = cosf(TO_RADIAN(pEnemy->angle)) * pEnemy->speed;
			speedY[i] = sinf(TO_RADIAN(pEnemy->angle)) * pEnemy->speed;
		}
		if (pEnemy->enemyMoveMode == MOVE) {
			pEnemy->x += speedX[i];
			pEnemy->y += speedY[i];

			// センターを更新
			pEnemy->centerX = pEnemy->x + pEnemy->w / 2;
			pEnemy->centerY = pEnemy->y + pEnemy->h / 2;
		}

		pEnemy->moveModeTimer--;

		if (pEnemy->moveModeTimer <= 0) {
			pEnemy->enemyMoveMode = (EnemyMoveMode)((pEnemy->enemyMoveMode + 1) % MODE_NUM);
			pEnemy->moveModeTimer = GetRandomF(30, 150);
		}

		// 弾を撃つ処理
		AimShot(
			&pEnemy->shotTimer, ENEMY_SHOT_NUM,
			enemyShot, enemyEye[i], player);

		// 敵を倒した処理
		if (pEnemy->state == ACTIVE) {
			EnemyDie(enemyEye[i]);
		}
	}
	ShotUpdate(ENEMY_SHOT_NUM, enemyShot);
}

// 回転する敵のアップデート : 1
void EnemyRotUpdate() {
	// 出現させるまでの時間
	enemyRot.createTimer--;
	if (enemyRot.createTimer < 0) {
		enemyRot.y++;
		if (enemyRot.y > 300.0f) enemyRot.y = 300.0f;
	}
	// 死んだら再出現
	if (EnemyDie(enemyRot)) {
		EnemyRotInit(all);
		spownRight = (GetRand(1) == 0) ? true : false;
	}

	if (spownRight) {
		enemyRot.x = gameSizeW - enemyRot.w;

		// 弾を撃つ処理
		ThreeWayShot(
			&enemyRot.shotTimer, ENEMY_SHOT_NUM,
			enemyShot, enemyRot, -1, 0, 120.0f);
	}
	else {
		enemyRot.x = 0;

		// 弾を撃つ処理
		ThreeWayShot(
			&enemyRot.shotTimer, ENEMY_SHOT_NUM,
			enemyShot, enemyRot, -1, 0, 60.0f);
	}

	// 回転させる
	enemyRotAngle += 0.2f;
	if (enemyRotAngle > 360.0f) enemyRotAngle = 0.0f;
	enemyRot.centerX = enemyRot.x + enemyRot.w / 2;
	enemyRot.centerY = enemyRot.y + enemyRot.h / 2;

	// 敵を倒した処理
	if (enemyRot.state == ACTIVE) {
		EnemyDie(enemyRot);
	}

	ShotUpdate(ENEMY_SHOT_NUM, enemyShot);
}
