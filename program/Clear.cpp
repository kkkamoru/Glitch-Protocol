#include "Main.h"
#include "Clear.h"
#include "Scene.h"
#include "FontManager.h"
#include "GameInit.h"
#include "Ranking.h"
#include "Sound.h"

BaseCharacter clearBack;

Text clear;

void ClearInit() {
	GameInit();
	clearBack.w = screenW;
	clearBack.h = screenH;
	clearBack.x = 0;
	clearBack.y = 0;
	clearBack.centerX = clearBack.x + clearBack.w / 2;
	clearBack.centerY = clearBack.y + clearBack.h / 2;

	sprintf_s(clear.text,
		":)\n"
		"clear"
		"\n\n"
		"score : %5d\n"
		"time  : %3d\n\n"
		"TITLE?\n"
		"[Y] YES"
		"[N] NO",
		scoreCount, second
	);
}

void SaveScore(int score) {
	// すでに同じスコアがある場合は何もしない
	 for (int i = 0; i < SCORE_MAX; i++) {
	     if (scores[i] == score) return;
	 }

	 // 挿入する位置を探す
	 // すでに保存されているスコアより大きい場合はその位置に挿入
	int insertPos = SCORE_MAX;
	for (int i = 0; i < SCORE_MAX; i++) {
		if (score > scores[i]) {
			insertPos = i;
			break;
		}
	}
	if (insertPos < SCORE_MAX) {
		// 下にずらす
		for (int j = SCORE_MAX - 1; j > insertPos; j--) {
			scores[j] = scores[j - 1];
		}
		scores[insertPos] = score;
	}
	else {
		// まだ0が残っている場合は一番下に挿入
		for (int i = 0; i < SCORE_MAX; i++) {
			if (scores[i] == 0) {
				scores[i] = score;
				break;
			}
		}
	}
}

void ClearUpdate() {
	SaveScore(scoreCount);

	if (PushHitKey(KEY_INPUT_Y)) {
		ClearBGMStop();
			SelectSEPlay();
		sceneNext = SCENE_TITLE;
	}
	if (PushHitKey(KEY_INPUT_N)) {
		SelectSEPlay();
		DxLib_End();
	}
}

void ClearRender() {
	Draw(clearBack, 0.0);

	DrawStringToHandle(
		10, 100,
		clear.text,
		GetColor(255, 255, 255),
		gameFonts.mainFont
	);
}