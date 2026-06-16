#include "Main.h"
#include "Scene.h"

#include "PlayerInit.h"
#include "PlayerUpdate.h"
#include "PlayerRender.h"

#include "GameInit.h"
#include "GameUpdate.h"

#include "FontManager.h"
#include "Shot.h"
#include "Sound.h"

#include "Title.h"

//タイトル
BaseCharacter titleBack;
float titlePlayerX;
float titlePlayerY;

BaseCharacter executeButton;
BaseCharacter rankingButton;
BaseCharacter exitButton;

//--------------------------------タイトル画面-----------------------------------
void TitleInit() {
	screenW = 800;
	screenH = 450;
	SetGraphMode(screenW, screenH, 32);
	LoadAll();
	titleBack.w = screenW;
	titleBack.h = screenH;
	titleBack.x = 0;
	titleBack.y = 0;
	titleBack.centerX = titleBack.x + titleBack.w / 2;
	titleBack.centerY = titleBack.y + titleBack.h / 2;

	executeButton.x = 178;
	executeButton.y = 309;
	executeButton.w = 128;
	executeButton.h = 36;

	rankingButton.x = 346;
	rankingButton.y = 309;
	rankingButton.w = 128;
	rankingButton.h = 36;

	exitButton.x = 509;
	exitButton.y = 309;
	exitButton.w = 83;
	exitButton.h = 36;

	gameSizeW = screenW;
	gameSizeH = screenH;

	PlayerInitAll();
	playerShotPattern = AIM_SHOT;
	player.x = screenW / 2;
	player.y = screenH / 2;
}

void TitleUpdate() {
	PlayerUpdate();
	TargetCursorUpdate();
	PlayerAimShot();

	for (int i = 0; i < PLAYER_SHOT_NUM; i++) {
		if (playerShot[i].state != ACTIVE) continue;

		if (CheckBoxHit(executeButton, playerShot[i])) {
			SelectSEPlay();
			sceneNext = SCENE_STAGE1;
		}

		if (CheckBoxHit(rankingButton, playerShot[i])) {
			// ランキング画面へ
			SelectSEPlay();
			sceneNext = SCENE_RANKING;
		}

		if (CheckBoxHit(exitButton, playerShot[i])) {
			// ゲーム終了
			SelectSEPlay();
			DxLib_End();
		}
	}
}

void TitleRender() {
	Draw(titleBack, 0.0f);
	DrawPlayer();
	Draw(targetCursor, 0.0);
}
