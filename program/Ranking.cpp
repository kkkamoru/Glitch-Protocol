#include "Main.h"
#include "Scene.h"

#include "PlayerInit.h"
#include "PlayerUpdate.h"
#include "PlayerRender.h"

#include "GameUpdate.h"
#include "Title.h"

#include "FontManager.h"
#include "Sound.h"
#include "Shot.h"
#include "Ranking.h"

const int SCORE_MAX = 10;
int scores[SCORE_MAX];

BaseCharacter rankingBack;
BaseCharacter rankingExit;

void RankingInit() {
	rankingBack.w = screenW;
	rankingBack.h = screenH;
	rankingBack.x = 0;
	rankingBack.y = 0;

	rankingExit.x = 567;
	rankingExit.y = 382;
	rankingExit.w = 83;
	rankingExit.h = 36;
}

void RankingUpdate() {
	PlayerUpdate();
	TargetCursorUpdate();
	PlayerAimShot();

	for (int i = 0; i < PLAYER_SHOT_NUM; i++) {
		if (playerShot[i].state != ACTIVE) continue;
		if (CheckBoxHit(rankingExit, playerShot[i])) {
			SelectSEPlay();
			sceneNext = SCENE_TITLE;
		}
	}
}

void RankingRender() {
	Draw(rankingBack, 0.0);
	for (int i = 0; i < SCORE_MAX; i++) {
		char scoreText[32];
		sprintf_s(scoreText, "%2d : %08d", i + 1, scores[i]);
		DrawStringToHandle(
			300, 100 + i * 30,
			scoreText,
			GetColor(255, 255, 255),
			gameFonts.mainFont);
	}
	DrawStringToHandle(
		80, 20,
		"BGM: LeaF",
		GetColor(255, 255, 255),
		gameFonts.mainFont
	);
	Draw(targetCursor, 0.0);
	DrawPlayer();

}