#include "Main.h"
#include "Scene.h"
#include "GameInit.h"
#include "FontManager.h"
#include "Sound.h"

// テキスト
const int TEXT_NUM = 4;
const char* texts[TEXT_NUM];

char drawText[256];	// 描画用テキスト
int textLength = 0;	// テキストの長さ
int drawLength = 0;	// 描画している長さ
int count = 0;			// 表示カウント
float waitTime;		// 表示待機カウント

int currentTextIndex;	// どのテキストを表示しているか

void OPInit() {
	currentTextIndex = 0;

	texts[0] =
		"システムを起動中. . .\n"
		"メモリチェック[■■]　OK\n"
		"ハードウェアを検出中. . . 　OK\n"
		"コアモジュールを読み込み中. . . 　OK\n"
		"ユーザーインターフェースを読み込み中. . . 　OK\n"
		"セキュリティモジュールを読み込み中. . . 　OK\n"
		"> システム準備完了\n"
		"> 入力を待機しています. . .";

	texts[1] =
		"実行中: START.EXE\n"
		"メインプロセス起動中. . .\n"
		"プラグイン読み込み中: BUG.EXE\n"
		"ネットワークにアクセス中. . .\n"
		".\n"
		". .\n"
		". . .\n"
		"> 入力を待機しています. . .";

	texts[2] =
		"警告: 不明なモジュールを検出\n"
		"エラー: データ構造が破損しました。\n"
		"システム安定度: 42%\n"
		"自動修復を試行中. . .\n"
		"> 修復に失敗しました。\n"
		"[重大エラー]\n"
		"コア整合性: 17%\n"
		"外部信号を検出. . .\n"
		"> 入力を待機しています. . .";

	texts[3] =
		"アクセス許可されました\n"
		"接続を開始しています. . .\n"
		"ノード[CORE_01]に接続中. . .\n"
		"ベイロード[BUG.EXE]を送信中. . . 　完了\n"
		"ターゲットシステムへの感染: 成功\n"
		"> ようこそ";

	textLength = strlen(texts[currentTextIndex]);
	screenW = 800;
	screenH = 450;
	SetGraphMode(screenW, screenH, 32);
	LoadAll();

	gameSizeW = screenW;
	gameSizeH = screenH;

}

// テキストをリセット
void ResetText() {
	textLength = strlen(texts[currentTextIndex]);
	drawLength = 0;
	drawText[0] = '\0';
	for (int i = 0; i < 256; i++) {
		drawText[i] = '\0';
	}

}

// 表示速度を更新
void UpdateWaitTime(int index, int drawLength) {
	// デフォルトの表示速度
	waitTime = 0.5f;

	// 今の文字を取得
	char currentChar = texts[index][drawLength];
	// テキストごとに表示速度を変える
	if (currentChar == '.') {
		waitTime = 10.0f;
	}
}

void OPUpdate() {
	UpdateWaitTime(currentTextIndex, drawLength);
	if (CheckHitKey(KEY_INPUT_S)) {
		SelectSEPlay();
		sceneNext = SCENE_TITLE;
	}

	count++;
	if (drawLength < textLength) {
		if (count >= waitTime) {
			count = 0;

			drawText[drawLength] = texts[currentTextIndex][drawLength];
			drawLength++;
			drawText[drawLength] = texts[currentTextIndex][drawLength];
			drawLength++;
			TipingSEPlay();
		}
	}
	else {
		// スペースで次へ
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			SelectSEPlay();
			if (currentTextIndex >= TEXT_NUM - 1) {
				sceneNext = SCENE_TITLE;
			}
			else {
				currentTextIndex++;
				// テキストリセット
				ResetText();
			}
		}
	}
}

void OPRender() {
	DrawBox(0, 0, screenW, screenH, GetColor(0, 0, 0), TRUE);

	DrawStringToHandle(
		10, 10,
		drawText,
		GetColor(255, 255, 255),
		gameFonts.mainFont);

	DrawStringToHandle(
		650, 390,
		"next: SPACE\nskip: S",
		GetColor(255, 255, 255),
		gameFonts.mainFont
	);
}

