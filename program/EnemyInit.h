#ifndef __ENEMYINIT_H__
#define __ENEMYINIT_H__

void EnemyRotInit(bool all);
void EnemyInitAll();

// “G‚Ì€–SƒGƒtƒFƒNƒg
const int ENEMY_DIE_EFFECT_NUM = 20;
extern EnemyDieEffect enemyDieEffect[];

// “G‚Ì’e
const int ENEMY_SHOT_NUM = 100;
extern Shot enemyShot[];

// “G(–Ú)
const int ENEMY_EYE_NUM = 8;
extern Enemy enemyEye[];
extern float speedX[];
extern float speedY[];

// “G(‚)
const int ENEMY_SHIELD_NUM = 5;
extern Enemy enemyShield[];

// “G(‰ñ“])
extern Enemy enemyRot;
extern float enemyRotAngle;

extern bool spownRight;
extern bool spownUp;


#endif