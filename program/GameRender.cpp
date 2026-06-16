#include "Main.h"
#include "Scene.h"
#include "GameInit.h"
#include "FontManager.h"

#include "GameRender.h"


//------------------------------------------------------------
// •`‰æ
// ------------------------------------------------------------
// ƒAƒCƒeƒ€‚Ì•`‰æ
void DrawItem() {
	for (int i = 0; i < ITEM_MAX; i++) {
		if (aimItem[i].state == ACTIVE)
			Draw(aimItem[i], 0.0);
	}

	for (int i = 0; i < ITEM_MAX; i++) {
		if (threeWayItem[i].state == ACTIVE)
			Draw(threeWayItem[i], 0.0);
	}
}

// ”wŒi‚Ì•`‰æ
void DrawBack() {
	switch (sceneNum) {
	case SCENE_STAGE1:
		Draw(stage1Back, 0.0);
		for (int i = 0; i < STAR_NUM; i++) {
			farStar->DrawStar(farStar[i]);
		}

		for (int i = 0; i < BACK_NUM; i++) {
			Draw(sparkling[i], 0.0);
			Draw(errorWindow[i], 0.0);
			Draw(loading[i], 0.0);
			Draw(errorTriangle[i], 0.0);
		}

		for (int i = 0; i < STAR_NUM; i++) {
			nearStar->DrawStar(nearStar[i]);
		}

		break;

	case SCENE_STAGE2:
		Draw(stage2Back, 0.0);

		for (int i = 0; i < STAR_NUM; i++) {
			farStar->DrawStar(farStar[i]);
			nearStar->DrawStar(nearStar[i]);
		}

		for (int i = 0; i < BACK_NUM; i++) {
			Draw(noiseBack[i], 0.0);
		}


		break;
	}
}

// ƒeƒLƒXƒg‚Ì•`‰æ
void DrawText() {
	DrawStringToHandle(
		score.x, score.y,
		score.text,
		GetColor(0, 0, 0),
		gameFonts.mainFont
	);

	DrawStringToHandle(
		shot.x, shot.y,
		shot.text,
		GetColor(0, 0, 0),
		gameFonts.mainFont
	);

	if (timeCount / 30 % 2 == 0) {
		DrawStringToHandle(
			enemyAlive.x, enemyAlive.y,
			enemyAlive.text,
			GetColor(255, 255, 255),
			gameFonts.mainFont
		);
	}
}

// ƒ|ƒCƒ“ƒg‚Ì•`‰æ
void PointEffectRender() {
	for (int i = 0; i < POINT_EFFECT_NUM; i++) {
		if (pointEffect[i].active) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, pointEffect[i].alpha);
			DrawStringToHandle(
				pointEffect[i].x,
				pointEffect[i].y,
				pointEffect[i].text,
				GetColor(255, 255, 255),
				gameFonts.mainFont
			);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}