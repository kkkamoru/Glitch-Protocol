#include "Main.h"
#include "Scene.h"

#include "GameInit.h"
#include "GameUpdate.h"

#include "BossInit.h"
#include "BossUpdate.h"

#include "EnemyInit.h"
#include "PlayerInit.h"

#include "Shot.h"
#include "Sound.h"


void SpownBossDieEffect(int x, int y) {
	// ボスが死んだときにエフェクトを出す。
	// 非アクティブのエフェクトを探して、再生させる。
	for (int i = 0; i < BOSS_DIE_EFFECT_NUM; i++) {
		EnemyDieEffect* pEffect = &bossDieEffect[i];
		if (pEffect->state == ACTIVE) continue;

		pEffect->state = ACTIVE;
		pEffect->x = (x - pEffect->w / 2) + GetRandomF(-100, 100);
		pEffect->y = (y - pEffect->h / 2) + GetRandomF(-100, 100);
		pEffect->centerX = pEffect->x + pEffect->w / 2;
		pEffect->centerY = pEffect->y + pEffect->h / 2;
		pEffect->frame = 0;
		pEffect->timer = 0 - (i * 3);
	}
}

// ボスが死んだときの処理
void BossDie() {
	if (boss.state != ACTIVE) return;

	if (boss.hp < 0) {
		boss.hp = 0;
		ScoreUp(5000);
		boss.state = DIE;

		// 死んだときのエフェクトを出す
		SpownBossDieEffect(boss.centerX, boss.centerY);
		SpownPointEffect(boss.x, boss.y, +5000);
	}
}

// ボスの死亡エフェクトの更新
void BossDieEffectUpdate() {
	for (int i = 0; i < BOSS_DIE_EFFECT_NUM; i++) {
		EnemyDieEffect* pEffect = &bossDieEffect[i];
		if (pEffect->state != ACTIVE) continue;
		pEffect->timer++;
		if (pEffect->timer % 10 == 0) {
			pEffect->frame++;
		}
		if (pEffect->frame > 5) {
			// エフェクトは消す（再利用可能にする）
			pEffect->state = INACTIVE;
			pEffect->frame = 0;
			pEffect->timer = 0;
		}
	}
}

void BossUpdate()
{
	// ボスの動き
	if (enemyAlive.enemyAliveCount <= 0) {
		// ボス登場の時、1回だけ音を鳴らす(updateし続けない)
		if (warningTimer == 1) {
			Stage2BGMStop();
			BossBGMPlay();
		}

		if (warningTimer < 0) {
			boss.y += 2.0f; // ボスがゆっくりと下に移動する
		}
	}

	if (boss.y > 100 && boss.hp > 0) {
		boss.y = 100; // 位置を固定
		boss.state = ACTIVE; // ボスがアクティブになる
	}

	if (boss.state == ACTIVE) {
		boss.x += boss.speed * boss.dir;
		if (boss.x < 0 || boss.x > gameSizeW - boss.w) {
			boss.dir *= -1; // 画面端で方向転換
		}
	}

	boss.centerX = boss.x + boss.w / 2;
	boss.centerY = boss.y + boss.h / 2;

	// ボスはランダムに攻撃パターンを変える
	if (shotPatternRand == 0) {
		ThreeWayShot(&boss.shotTimer, ENEMY_SHOT_NUM,
			enemyShot, boss, 1, 0, 90.0f);
		ShotUpdate(ENEMY_SHOT_NUM, enemyShot);
	}
	else if (shotPatternRand == 1) {
		AimShot(
			&boss.shotTimer, ENEMY_SHOT_NUM,
			enemyShot, boss, player);
		ShotUpdate(ENEMY_SHOT_NUM, enemyShot);
	}
	else if (shotPatternRand == 2) {
		EnemyStraightShot(
			&boss.shotTimer, ENEMY_SHOT_NUM,
			enemyShot, boss);
	}
	shotPatternRand = GetRand(2);

	// 残りHPに応じて画像を変える
	if (boss.hp < boss.hpMax * 0.66) {
		boss.currentImage = 1;
	}
	if (boss.hp < boss.hpMax * 0.33) {
		boss.currentImage = 2;
	}

	if (boss.state == ACTIVE) {
		BossDie();
	}

}

void WarningUpdate() {
	if (enemyAlive.enemyAliveCount > 0) return;
	if (warningTimer >= 150) {
		WarningSEPlay();
	}
	warningTimer--;
	warning.alpha -= 5.0f;
	if (warning.alpha < 0.0f) {
		warning.alpha = 255.0f;
	}
}