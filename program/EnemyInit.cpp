#include "Main.h"
#include "Scene.h"
#include "GameInit.h"
#include "PlayerInit.h"

#include "EnemyInit.h"

//------------------------------“G‚Ì€–SƒGƒtƒFƒNƒg------------------------
EnemyDieEffect enemyDieEffect[ENEMY_DIE_EFFECT_NUM];

//------------------------------“G‚Ì’e-----------------------------------
Shot enemyShot[ENEMY_SHOT_NUM];

//------------------------------“G(–Ú)-----------------------------------
Enemy enemyEye[ENEMY_EYE_NUM];

float speedX[ENEMY_EYE_NUM];
float speedY[ENEMY_EYE_NUM];

//------------------------------“G(‚)-----------------------------------
Enemy enemyShield[ENEMY_SHIELD_NUM];

//------------------------------“G(‰ñ“])--------------------------------
Enemy enemyRot;
float enemyRotAngle;

bool spownRight;
bool spownUp;

// “G‚Ì€–SƒGƒtƒFƒNƒg‚Ì‰Šú‰»
void EnemyDieEffectInit() {
	for (int i = 0; i < ENEMY_DIE_EFFECT_NUM; i++) {
		EnemyDieEffect* pEffect = &enemyDieEffect[i];
		pEffect->x = 0.0f;
		pEffect->y = 0.0f;
		pEffect->w = 80;
		pEffect->h = 80;
		pEffect->centerX = pEffect->x + pEffect->w / 2;
		pEffect->centerY = pEffect->y + pEffect->h / 2;

		pEffect->state = INACTIVE;
		pEffect->frame = 0;
		pEffect->timer = 0;
	}
}

// “G‚Ì’e‚Ì‰Šú‰»
void EnemyShotInit() {
	for (int i = 0; i < ENEMY_SHOT_NUM; i++) {
		Shot* pShot = &enemyShot[i];
		pShot->x = 0;
		pShot->y = 0;
		pShot->w = 15;
		pShot->h = 15;
		pShot->centerX = pShot->x + pShot->w / 2;
		pShot->centerY = pShot->y + pShot->h / 2;
		pShot->state = INACTIVE;

		pShot->targetX = player.centerX;
		pShot->targetY = player.centerY;
		pShot->angle = 0.0f;
		if (sceneNum == SCENE_STAGE1)
			pShot->speed = 4;
		else if (sceneNum == SCENE_STAGE2)
			pShot->speed = 3;
	}
}

// “G(–Ú)‚Ì‰Šú‰»
void EnemyEyeInit(bool all) {
	if (all == true) {
		for (int i = 0; i < ENEMY_EYE_NUM; i++) {
			Enemy* pEnemy = &enemyEye[i];
			pEnemy->w = 50;
			pEnemy->h = 50;

			pEnemy->centerX = pEnemy->x + pEnemy->w / 2;
			pEnemy->centerY = pEnemy->y + pEnemy->h / 2;

			pEnemy->speed = 2.0f;
			pEnemy->hp = 3;
			pEnemy->state = INACTIVE;
			pEnemy->enemyType = ENEMY_EYE;
			pEnemy->shotTimer = 0;

			pEnemy->angle = 0.0f;
			pEnemy->alpha = 0;
			pEnemy->enemyMoveMode = MOVE;
			pEnemy->moveModeTimer = GetRandomF(30, 150);
			pEnemy->createTimer = 240 + (i * 240);

			speedX[i] = 0.0f;
			speedY[i] = 0.0f;

			for (int j = 0; j < CREATE_EFFECT_NUM; j++)
			{
				EnemyEyeCreateEffect* pEffect = &pEnemy->createEffect[j];
				pEffect->isActive = false;
				pEffect->x = pEnemy->centerX;
				pEffect->y = pEnemy->centerY;
				pEffect->size = 10;
				pEffect->alpha = 255;
			}

			if (sceneNum == SCENE_STAGE1)
			{
				pEnemy->x = GetRand(gameSizeW) + gameSizeW;	// ‰æ–ÊŠO‚©‚çoŒ»
				pEnemy->y = GetRand(gameSizeH - pEnemy->h);		// ‚±‚±‚Å‚‚³‚ğŒvZ‚Å‚«‚é‚æ‚¤‚ÉA•‚Æ‚‚³‚ğæ‚ÉŒˆ‚ß‚Ä‚¢‚é
			}
			else if (sceneNum == SCENE_STAGE2)
			{
				pEnemy->x = GetRand(gameSizeW - pEnemy->h);
				pEnemy->y = GetRand(gameSizeH) - gameSizeH;
			}
		}
	}
	else {
		for (int i = 0; i < ENEMY_EYE_NUM; i++) {
			Enemy* pEnemy = &enemyEye[i];
			for (int j = 0; j < CREATE_EFFECT_NUM; j++)
			{
				EnemyEyeCreateEffect* pEffect = &pEnemy->createEffect[j];
				pEffect->isActive = false;
				pEffect->x = pEnemy->centerX;
				pEffect->y = pEnemy->centerY;
				pEffect->size = 10;
				pEffect->alpha = 255;
			}

			if (sceneNum == SCENE_STAGE1)
			{
				pEnemy->x = GetRand(gameSizeW) + gameSizeW;	// ‰æ–ÊŠO‚©‚çoŒ»
				pEnemy->y = GetRand(gameSizeH - pEnemy->h);		// ‚±‚±‚Å‚‚³‚ğŒvZ‚Å‚«‚é‚æ‚¤‚ÉA•‚Æ‚‚³‚ğæ‚ÉŒˆ‚ß‚Ä‚¢‚é
			}
			else if (sceneNum == SCENE_STAGE2)
			{
				pEnemy->x = GetRand(gameSizeW - pEnemy->h);
				pEnemy->y = GetRand(gameSizeH) - gameSizeH;
			}
		}
	}
}

// “G(‚)‚Ì‰Šú‰»
void EnemyShieldInit(bool all) {
	if (all == true) {
		for (int i = 0; i < ENEMY_SHIELD_NUM; i++) {
			Enemy* pEnemy = &enemyShield[i];
			pEnemy->w = 43;
			pEnemy->h = 50;
			pEnemy->centerY = pEnemy->y + pEnemy->h / 2;
			pEnemy->centerX = pEnemy->x + pEnemy->w / 2;

			pEnemy->speed = 1.5f;
			pEnemy->hp = 5;
			pEnemy->state = ACTIVE;
			pEnemy->enemyType = ENEMY_SHIELD;

			pEnemy->shotTimer = 0;
			pEnemy->moveModeTimer = 0;
			pEnemy->enemyMoveMode = MOVE;
			pEnemy->createTimer = 240 + (i * 240);

			pEnemy->dir = 1;	//	“G‚ÌˆÚ“®•ûŒü

			if (sceneNum == SCENE_STAGE1)
			{
				pEnemy->x = GetRandomF(gameSizeW / 2, gameSizeW);	// ‰æ–Ê^‚ñ’†‚æ‚è‰E
				pEnemy->y = 0 - pEnemy->h;		// ‚±‚±‚Å‚‚³‚ğŒvZ‚Å‚«‚é‚æ‚¤‚ÉA•‚Æ‚‚³‚ğæ‚ÉŒˆ‚ß‚Ä‚¢‚é
			}
			else if (sceneNum == SCENE_STAGE2)
			{
				pEnemy->x = GetRand(gameSizeW - pEnemy->h);
				pEnemy->y = GetRandomF(0 - pEnemy->h, 0 - gameSizeH);
			}
		}
	}
	else {
		for (int i = 0; i < ENEMY_SHIELD_NUM; i++) {
			Enemy* pEnemy = &enemyShield[i];
			pEnemy->dir = 1;	//	“G‚ÌˆÚ“®•ûŒü

			if (sceneNum == SCENE_STAGE1)
			{
				pEnemy->x = GetRandomF(gameSizeW / 2, gameSizeW);	// ‰æ–Ê^‚ñ’†‚æ‚è‰E
				pEnemy->y = 0 - pEnemy->h;		// ‚±‚±‚Å‚‚³‚ğŒvZ‚Å‚«‚é‚æ‚¤‚ÉA•‚Æ‚‚³‚ğæ‚ÉŒˆ‚ß‚Ä‚¢‚é
			}
			else if (sceneNum == SCENE_STAGE2)
			{
				pEnemy->x = GetRand(gameSizeW - pEnemy->h);
				pEnemy->y = GetRand(gameSizeH) - gameSizeH;
			}
		}
	}
}

// “G(‰ñ“])‚Ì‰Šú‰»
void EnemyRotInit(bool all) {
	if (all == true) {
		enemyRot.w = 50;
		enemyRot.h = 50;

		enemyRot.centerX = enemyRot.x + enemyRot.w / 2;
		enemyRot.centerY = enemyRot.y + enemyRot.h / 2;

		enemyRot.speed = 2.0f;
		enemyRot.hp = 3;
		enemyRot.enemyType = ENEMY_ROT;
		enemyRot.shotTimer = 0;

		enemyRotAngle = 0.0f;

		spownRight = (GetRand(1) == 0) ? true : false;

		if (sceneNum == SCENE_STAGE1)
		{
			enemyRot.state = INACTIVE;
		}
		else if (sceneNum == SCENE_STAGE2)
		{
			enemyRot.state = ACTIVE;
			enemyRot.x = 0;
			enemyRot.y = 0 - enemyRot.h;
			enemyRot.createTimer = GetRand(300);
		}
	}
	else {
		enemyRotAngle = 0.0f;

		spownRight = (GetRand(1) == 0) ? true : false;

		if (sceneNum == SCENE_STAGE1)
		{
			enemyRot.state = INACTIVE;
		}
		else if (sceneNum == SCENE_STAGE2)
		{
			enemyRot.state = ACTIVE;
			enemyRot.x = 0;
			enemyRot.y = 0 - enemyRot.h;
			enemyRot.createTimer = GetRand(300);
		}
	}
}


//-------------------------------
// : 1,2
void EnemyInitAll() {
	EnemyDieEffectInit();
	EnemyShotInit();
	EnemyShieldInit(all);
	EnemyEyeInit(all);
	EnemyRotInit(all);
}
//-------------------------------
