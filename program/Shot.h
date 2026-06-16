#ifndef __SHOT_H__
#define __SHOT_H__
#include "Source.h"

//------------------------------------------------------------
// 汎用的な弾の処理
// ------------------------------------------------------------
void EnemyStraightShot(
	int* timer, int shot_num,
	Shot* shot, Enemy& enemy
);

void AimShotStart
(int shot_num, Shot* shot,
	float shooterX, float shooterY, float targetX, float targetY);

void ShotUpdate
(int shot_num, Shot* shot);

void AimShot(
	int* timer, int shot_num,
	Shot* shot, Enemy& enemy, Player& player);

void ThreeWayShotStart(int shot_num, Shot* shot,
	float shooterX, float shooterY, int directionX, int directionY,float angleBase);

void ThreeWayShot(
	int* timer, int shot_num,
	Shot* shot, Enemy& enemy, int directionX, int directionY,float angleBase);

//---------------------------------------------------------------------
// プレイヤーのショットパターン
//---------------------------------------------------------------------

// プレイヤーの通常ショット
void PlayerNormalShot();

extern bool beforeMouseInput;
// プレイヤーがマウスに向かって撃つショット
void PlayerAimShot();

// プレイヤーの三方向ショット
void PlayerThreeWayShot();

void ObjectHoming(float* angle, float x, float y, float targetX, float targetY);


#endif