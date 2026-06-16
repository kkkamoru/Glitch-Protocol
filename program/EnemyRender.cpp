#include "Main.h"
#include "EnemyInit.h"
#include "Scene.h"

#include "EnemyRender.h"

// 敵の描画
void DrawEnemy() {
	// 盾の敵
	for (int i = 0; i < ENEMY_SHIELD_NUM; i++) {
		Enemy* pEnemy = &enemyShield[i];
		if (pEnemy->state == ACTIVE)
			Draw(enemyShield[i], 0.0);
	}
	// 目の敵
	for (int i = 0; i < ENEMY_EYE_NUM; i++) {
		Enemy* pEnemy = &enemyEye[i];
		if (pEnemy->state == ACTIVE) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, pEnemy->alpha);
			Draw(enemyEye[i], TO_RADIAN(pEnemy->angle));
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		// 出現エフェクト
		for (int j = 0; j < CREATE_EFFECT_NUM; j++) {
			EnemyEyeCreateEffect* pEffect = &enemyEye[i].createEffect[j];
			//render
			if (pEffect->isActive == true)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, pEffect->alpha);
				DrawCircleAA(pEffect->x, pEffect->y, pEffect->size, 100, GetColor(0, 255, 255), FALSE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}

	// 回転の敵
	if (enemyRot.state == ACTIVE) {
		Draw(enemyRot, enemyRotAngle);
	}

	// 弾
	for (int i = 0; i < ENEMY_SHOT_NUM; i++) {
		if (enemyShot[i].state == ACTIVE) {
			Draw(enemyShot[i], TO_RADIAN(enemyShot[i].angle));
		}
	}

	// 敵の死亡エフェクト
	for (int i = 0; i < ENEMY_DIE_EFFECT_NUM; i++) {
		if (enemyDieEffect[i].state != ACTIVE) continue;
		int effectX = enemyDieEffect[i].frame * enemyDieEffect[i].w;
		int effectW = enemyDieEffect[i].w;
		DrawRectGraph(
			enemyDieEffect[i].x, enemyDieEffect[i].y,
			effectX, 0,
			effectW, enemyDieEffect[i].h,
			enemyDieEffect[i].image, TRUE
		);
	}
}
