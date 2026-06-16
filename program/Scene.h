#ifndef __SCENE_H__
#define __SCENE_H__

void LoadAll();

void SceneInit();	//	初期化処理
void SceneUpdate();	//	更新処理
void SceneRender();	//	描画処理
void SceneExit();	//	終了処理

// 各シーン
enum GameScene {
	SCENE_OP,
	SCENE_TITLE,	// 0: タイトル
	SCENE_STAGE1,	// 1:ステージ
	SCENE_STAGE2,	// 2:ステージ
	SCENE_GAMEOVER,	// 3: ゲームオーバー画面
	SCENE_CLEAR,	// 4: クリア画面
	SCENE_RANKING,	// 5: ランキング画面
	SCENE_OPTION
};

extern int sceneNext;
extern int sceneNum;
extern bool continueFlag;

extern int screenW;
extern int screenH;

extern bool all;

#endif