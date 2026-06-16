#include "Source.h"
#include "Main.h"
#include "Scene.h"
#include "GameOver.h"
#include "FontManager.h"
#include "GameInit.h"
#include "PlayerInit.h"
#include "Sound.h"

BaseCharacter gameOverBack;
const char* text;
//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameOverInit() {
	text =
		":(\n"
		"[SYSTEM FAILURE]\n"
		"データ構造が破損しました\n"
		"システムを復旧しますか？\n"
		"[Y] YES\n"
		"[N] NO\n";
}

//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameOverUpdate() {
	// コンティニュー
	if (PushHitKey(KEY_INPUT_Y))
		if (continueScene == SCENE_STAGE1) {
			SelectSEPlay();
			sceneNext = SCENE_STAGE1;
		}
		else if (continueScene == SCENE_STAGE2) {
			SelectSEPlay();
			player.hp = 10;
			sceneNext = SCENE_STAGE2;
		}

	// タイトルへ
	if (PushHitKey(KEY_INPUT_N)) {
		SelectSEPlay();
		sceneNext = SCENE_OP;	
	}
}

//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameOverRender() {
	DrawBox(0, 0, screenW, screenH, GetColor(0, 50, 255), TRUE);

	DrawStringToHandle(
		10, 10,
		text,
		GetColor(255, 255, 255),
		gameFonts.mainFont);
}
