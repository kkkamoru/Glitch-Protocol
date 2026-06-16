#ifndef __GAMEINIT_H__
#define __GAMEINIT_H__

void GameInit();
void BackgroundInit();
void ScoreInit();

void ItemInit();

// text
extern Text enemyAlive;
extern int scoreCount;
extern PointEffect pointEffect[];

// 背景
extern BaseCharacter stage1Back;
extern BaseCharacter stage2Back;

extern const int BACK_NUM;
extern BaseCharacter sparkling[];
extern BaseCharacter loading[];
extern BaseCharacter errorWindow[];
extern BaseCharacter errorTriangle[];
extern BaseCharacter noiseBack[];
extern BaseCharacter stage1Text;

extern const int STAR_NUM;
extern Star nearStar[];
extern Star farStar[];

extern int gameSizeW;
extern int gameSizeH;

extern BaseCharacter stage1Score;
extern BaseCharacter stage2Score;

extern BaseCharacter stage2Text;
extern BaseCharacter clearText;

// スコア
extern Text score;
extern Text shot;
extern int timeCount;
extern int second;

// アイテム
const int ITEM_MAX = 20;
extern BaseCharacter aimItem[];
extern BaseCharacter threeWayItem[];

extern int continueScene;

#endif