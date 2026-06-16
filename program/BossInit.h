#ifndef __BOSS_H__
#define __BOSS_H__

void BossInitAll();


extern Boss boss;
extern int shotPatternRand;
const int BOSS_DIE_EFFECT_NUM = 5;
extern EnemyDieEffect bossDieEffect[];

extern BaseCharacter warning;
extern int warningTimer;

#endif