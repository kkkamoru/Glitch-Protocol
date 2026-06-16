#include "Main.h"
#include "Scene.h"
#include "GameInit.h"
#include <math.h>

#include "PlayerInit.h"
#include "EnemyInit.h"

#include "Shot.h"
#include "Sound.h"


//------------------------------------------------------------
// 汎用的な弾の処理
// ------------------------------------------------------------
// まっすぐ弾を撃つ
void EnemyStraightShot(
	int* timer, int shot_num,
	Shot* shot, Enemy& enemy
) {
	if (enemy.state == ACTIVE) {	// 敵が生きているときだけ

		// 最初の弾を撃つまでの時間
		(*timer)++;
		if (*timer < 20) return;

		if (*timer % 20 == 0) {
			for (int i = 0; i < shot_num; i++) {
				if (shot[i].state != ACTIVE) {		// 空いている弾を探す
					shot[i].state = ACTIVE;
					// 弾の初期位置
					shot[i].x = enemy.centerX - shot[i].w / 2;
					shot[i].y = enemy.centerY - shot[i].h / 2;
					shot[i].centerX = shot[i].x + shot[i].w / 2;
					shot[i].centerY = shot[i].y + shot[i].h / 2;
					// 発射方向（下方向へ進む）
					shot[i].speedX = 0;
					shot[i].speedY = enemyShot[i].speed;
					break;
				}
			}
		}
	}
	// 弾の移動
	for (int i = 0; i < shot_num; i++) {
		if (shot[i].state == ACTIVE) {
			shot[i].y += shot[i].speedY;
			// centerを更新
			shot[i].centerX = shot[i].x + shot[i].w / 2;
			shot[i].centerY = shot[i].y + shot[i].h / 2;
			// 画面外に出たらフラグをfalseに
			if (shot[i].x + shot[i].w < 0 || shot[i].x > screenW ||
				shot[i].y < 0 || shot[i].y > screenH) {
				shot[i].state = INACTIVE;
			}
		}
	}
}

void ObjectHoming(float* angle, float x, float y, float targetX, float targetY)
{
	float diffX = targetX - x;
	float diffY = targetY - y;
	float rad = atan2f(diffY, diffX);
	*angle = rad * 180.0f / 3.14159265f;
}
// 相手の方向を確認
void AimShotStart
(int shot_num, Shot* shot,
	float shooterX, float shooterY, float targetX, float targetY)
{
	for (int i = 0; i < shot_num; i++) {
		if (shot[i].state != ACTIVE) {		// 空いている弾を探す
			shot[i].state = ACTIVE;

			// 弾の初期位置
			shot[i].x = shooterX - shot[i].w / 2;
			shot[i].y = shooterY - shot[i].h / 2;
			shot[i].centerX = shot[i].x + shot[i].w / 2;
			shot[i].centerY = shot[i].y + shot[i].h / 2;

			//	弾から見たプレイヤーの方向（矢印：位置関係によって長さはバラバラ）
			ObjectHoming(&shot[i].angle,
				shot[i].centerX, shot[i].centerY,
				targetX, targetY);

			shot[i].speedX = cosf(TO_RADIAN(shot[i].angle)) * shot[i].speed;
			shot[i].speedY = sinf(TO_RADIAN(shot[i].angle)) * shot[i].speed;

			break;
		}
	}
}

// 相手に向かって弾を進める
void ShotUpdate
(int shot_num, Shot* shot)
{
	// 弾の移動
	for (int i = 0; i < shot_num; i++) {
		if (shot[i].state == ACTIVE) {
			// プレイヤーの方向に向かって進む
			//	その矢印の長さをスピード分にします
			shot[i].x += shot[i].speedX;
			shot[i].y += shot[i].speedY;

			// centerを更新
			shot[i].centerX = shot[i].x + shot[i].w / 2;
			shot[i].centerY = shot[i].y + shot[i].h / 2;

			// 画面外に出たらフラグをfalseに
			if (shot[i].x + shot[i].w < 0 || shot[i].x > screenW ||
				shot[i].y < 0 || shot[i].y > screenH) {
				shot[i].state = INACTIVE;
			}
		}
	}
}

// 相手を狙い撃つ弾
void AimShot(
	int* timer, int shot_num,
	Shot* shot, Enemy& enemy, Player& player
) {
	if (enemy.state == ACTIVE) {	// 敵が生きているときだけ

		// 最初の弾を撃つまでの時間
		(*timer)++;
		if (*timer < 80) return;

		if (*timer % 80 == 0) {
			AimShotStart(shot_num, shot,
				enemy.centerX, enemy.centerY, player.centerX, player.centerY);
			*timer = 0;
		}
	}
}

// 三方向弾を用意する
void ThreeWayShotStart(int shot_num, Shot* shot,
	float shooterX, float shooterY, int directionX, int directionY, float angleBase) {

	// 3発分まとめて空きを探す
	for (int i = 0; i < shot_num - 2; i++) {
		if (shot[i].state != ACTIVE &&
			shot[i + 1].state != ACTIVE &&
			shot[i + 2].state != ACTIVE) {

			for (int j = 0; j < 3; j++) {
				shot[i + j].state = ACTIVE;
				shot[i + j].x = shooterX - shot[i + j].w / 2;
				shot[i + j].y = shooterY - shot[i + j].h / 2;
				shot[i + j].centerX = shot[i + j].x + shot[i + j].w / 2;
				shot[i + j].centerY = shot[i + j].y + shot[i + j].h / 2;

				float angle = angleBase + (j - 1) * 30; // -1,0,1
				shot[i + j].angle = angle;
				shot[i + j].speedX = cosf(TO_RADIAN(angle)) * shot[i + j].speed;
				shot[i + j].speedY = sinf(TO_RADIAN(angle)) * shot[i + j].speed;
			}
			break;
		}
	}
}

// 三方向に撃つ弾
void ThreeWayShot(
	int* timer, int shot_num,
	Shot* shot, Enemy& enemy, int directionX, int directionY, float angleBase) {
	if (enemy.state != ACTIVE) return;

	// 最初の弾を撃つまでの時間
	(*timer)++;
	if (*timer < 50) return;

	if (*timer % 50 == 0) {
		ThreeWayShotStart(ENEMY_SHOT_NUM, shot, enemy.centerX, enemy.centerY, directionX, directionY, angleBase);
	}
}

//---------------------------------------------------------------------
// プレイヤーのショットパターン
//---------------------------------------------------------------------

// プレイヤーの通常ショット
void PlayerNormalShot() {
	if (playerShotPattern != NORMAL_SHOT) return;

	// 左クリックでショット
	if (player.shotTimer >= PLAYER_SHOT_INTERVAL) {
		for (int i = 0; i < PLAYER_SHOT_NUM; i++) {
			Shot* pShot = &playerShot[i];
			if (pShot->state != ACTIVE) {		// 空いている弾を探す

				ShotSEPlay();
				pShot->state = ACTIVE;
				pShot->x = player.x;
				pShot->y = player.centerY - pShot->h / 2;
				player.shotTimer = 0;
				player.shotTimer = 0;
				break;
			}
		}
	}

	// 弾の移動
	for (int i = 0; i < PLAYER_SHOT_NUM; i++) {
		Shot* pShot = &playerShot[i];

		switch (sceneNum) {
		case SCENE_STAGE1:
			if (pShot->state == ACTIVE) {
				pShot->x += pShot->speed;
			}
			// 画面外に出たらフラグをfalseに 
			if (pShot->x > screenW)
				pShot->state = INACTIVE;

			break;
		case SCENE_STAGE2:
			if (pShot->state == ACTIVE) {
				pShot->y -= pShot->speed;
			}
			// 画面外に出たらフラグをfalseに 
			if (pShot->y < 0)
				pShot->state = INACTIVE;

			break;
		}
	}
}

bool beforeMouseInput = false;
// プレイヤーがマウスに向かって撃つショット
void PlayerAimShot() {
	if (playerShotPattern != AIM_SHOT) return;
	// タイトル画面ではクリックでショット
	if (sceneNum == SCENE_TITLE || sceneNum == SCENE_RANKING) {
		if (CheckMouseInput() & MOUSE_INPUT_LEFT) {
			if (player.shotTimer >= PLAYER_SHOT_INTERVAL) {
				ShotSEPlay();
				AimShotStart(PLAYER_SHOT_NUM, playerShot,
					player.centerX, player.centerY, GetMouseX(), GetMouseY());
				player.shotTimer = 0;
			}
		}
	}
	else {
		// 自動でショット
		if (player.shotTimer >= PLAYER_SHOT_INTERVAL) {
			ShotSEPlay();
			AimShotStart(PLAYER_SHOT_NUM, playerShot,
				player.centerX, player.centerY, GetMouseX(), GetMouseY());
			player.shotTimer = 0;
		}
	}
	ShotUpdate(PLAYER_SHOT_NUM, playerShot);
}

// プレイヤーの三方向ショット
void PlayerThreeWayShot() {
	if (playerShotPattern != THREE_WAY_SHOT) return;

	if (player.shotTimer >= PLAYER_SHOT_INTERVAL) {
		// 左クリックでショット
		ShotSEPlay();
		if (sceneNum == SCENE_STAGE1) {
			ThreeWayShotStart(PLAYER_SHOT_NUM, playerShot,
				player.centerX, player.centerY, -1, 0, 0.0f);
		}
		if (sceneNum == SCENE_STAGE2) {
			ThreeWayShotStart(PLAYER_SHOT_NUM, playerShot,
				player.centerX, player.centerY, 0, 1, 270.0f);
			player.shotTimer = 0;
		}
	}
	ShotUpdate(PLAYER_SHOT_NUM, playerShot);
}


