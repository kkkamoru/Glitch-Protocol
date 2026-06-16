#ifndef __GAMEUPDATE_H__
#define __GAMEUPDATE_H__

bool StageStart();
void TargetCursorUpdate();

void SpownItem(float x, float y, BaseCharacter item[]);
void ItemUpdate();

bool CheckHitEnemiesToPlayer();
bool CheckHitEnemyShotToPlayer();
bool CheckHitPlayerShotToEnemies();
bool CheckHitItemToPlayer();
void TextUpdate();
void Stage1Clear();
void Stage2Clear();
void BackUpdate(Star stars[]);

void ScoreDown(int down);
void ScoreUp(int up);
void KillScore(float x1, float y1, float x2, float y2, int score);
void ScoreUpdate();

void SpownPointEffect(float x, float y, int score);
void PointEffectUpdate();
#endif