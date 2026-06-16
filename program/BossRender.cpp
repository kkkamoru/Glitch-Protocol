#include "Main.h"
#include "BossInit.h"
#include "BossRender.h"
#include "GameInit.h"

void BossRender() {
	// ボスの描画(状態に合わせて変化)
	if (boss.state != DIE) {
		DrawGraph(
			boss.x, boss.y,
			boss.images[boss.currentImage],
			TRUE
		);
	}

	// ボスの死亡エフェクトの描画
	for (int i = 0; i < BOSS_DIE_EFFECT_NUM; i++) {
		if (bossDieEffect[i].state != ACTIVE) continue;
		int effectX = bossDieEffect[i].frame * bossDieEffect[i].w;
		int effectW = bossDieEffect[i].w;
		DrawRectGraph(
			bossDieEffect[i].x, bossDieEffect[i].y,
			effectX, 0,
			effectW, bossDieEffect[i].h,
			bossDieEffect[i].image, TRUE
		);
	}

	// 警告表示
	if (warningTimer > 0 && enemyAlive.enemyAliveCount <= 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, warning.alpha);
		Draw(warning, 0.0);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}