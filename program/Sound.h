#ifndef __SOUND_H__
#define __SOUND_H__

void Stage1BGMPlay();
void Stage1BGMStop();

void Stage2BGMPlay();
void Stage2BGMStop();

void ClearBGMPlay();
void ClearBGMStop();

void BossBGMPlay();
void BossBGMStop();

void ShotSEPlay();
void ItemSEPlay();
void SelectSEPlay();
void WarningSEPlay();
void HitSEPlay();
void TipingSEPlay();

extern int stage1BGM;
extern int stage2BGM;
extern int clearBGM;
extern int bossBGM;
extern int shotSE;
extern int itemSE;
extern int selectSE;
extern int warningSE;
extern int hitSE;
extern int tipingSE;

#endif