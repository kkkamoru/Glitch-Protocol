#include "Main.h"
#include "Scene.h"
#include "GameInit.h"
#include "BossInit.h"
#include "EnemyInit.h"

Boss boss;
Shot bossShot[ENEMY_SHOT_NUM];
EnemyDieEffect bossDieEffect[BOSS_DIE_EFFECT_NUM];

BaseCharacter warning;
int warningTimer;

int shotPatternRand;

// ボスの初期化
void BossInit() {
	// 現在使用している画像
	boss.currentImage = 0;

	boss.w = 200;
	boss.h = 200;
	boss.x = gameSizeW / 2 - boss.w / 2;
	boss.y = 0 - boss.w * 2;
	boss.centerX = boss.x + boss.w / 2;
	boss.centerY = boss.y + boss.h / 2;

	boss.dir = 1;
	boss.speed = 1.0f;
	boss.hp = 100;
	boss.hpMax = (float)boss.hp;
	boss.shotTimer = 0;

	shotPatternRand = GetRand(1);

	boss.state = INACTIVE;
}

// ボスの死亡エフェクトの初期化
void BossDieEffectInit() {
	for (int i = 0; i < BOSS_DIE_EFFECT_NUM; i++) {
		EnemyDieEffect* pEffect = &bossDieEffect[i];
		pEffect->x = 0.0f;
		pEffect->y = 0.0f;
		pEffect->w = 200;
		pEffect->h = 200;
		pEffect->centerX = pEffect->x + pEffect->w / 2;
		pEffect->centerY = pEffect->y + pEffect->h / 2;

		pEffect->state = INACTIVE;
		pEffect->frame = 0;
		pEffect->timer = 0;
	}
}

// 警告表示の初期化
void warningInit() {
	warning.w = 358;
	warning.h = 358;
	warning.x = gameSizeW / 2 - warning.w / 2;
	warning.y = gameSizeH / 2 - warning.h / 2;
	warning.centerX = warning.x + warning.w / 2;
	warning.centerY = warning.y + warning.h / 2;

	warning.alpha = 255;
	warning.angle = 0.0f;
	warningTimer = 150;
}

void BossInitAll() {
	BossInit();
	BossDieEffectInit();
	warningInit();
}