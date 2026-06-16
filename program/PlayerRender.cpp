#include "Main.h"
#include "PlayerInit.h"
#include "PlayerRender.h"

// プレイヤーの描画 : 1,2
void DrawPlayer() {
	// 弾
	for (int i = 0; i < PLAYER_SHOT_NUM; i++) {
		if (playerShot[i].state == ACTIVE) {
			Draw(playerShot[i],0.0);
		}
	}
	// 点滅処理
	bool flash = true;
	if (player.damageTimer > 0) {
		flash = (player.flashTimer / 5) % 2 == 0;
		// flashTimerを5で割ることで、5フレームごとにまとめている
		// それを2で割ることで５フレームで点滅させている
	}

	// プレイヤー
	if (flash)
		Draw(player,0.0);

	// エフェクト
	if (playerPattern != PLAYER_STAND) {
		DrawRectRotaGraph(
			playerEffect.centerX, playerEffect.centerY,
			playerEffectSrcX[playerPattern], 0,
			playerEffect.w, playerEffect.h,
			1.0, TO_RADIAN(playerEffectAngle),
			playerEffect.image, TRUE, FALSE);
	}
}
