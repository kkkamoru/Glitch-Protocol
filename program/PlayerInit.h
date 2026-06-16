#ifndef __PLAYERINIT_H__
#define __PLAYERINIT_H__

void PlayerInitAll();

// プレイヤー
extern Player player;
extern PlayerPattern playerPattern;
extern PlayerShotPattern playerShotPattern;

const int PLAYER_SHOT_NUM = 20;				// 弾は２０発（とりあえず）
extern Shot playerShot[];
extern float playerShotDirX[];		// 弾の進む方向
extern float playerShotDirY[];
const int PLAYER_SHOT_INTERVAL = 15;		// 弾の発射間隔
// プレイヤーのエフェクト
extern BaseCharacter playerEffect;
extern int playerEffectSrcX[];	// 横幅の切り出し位置

extern int effectChangeCount;
extern int playerEffectAngle;

// エイムショット用のカーソル
extern BaseCharacter targetCursor;



#endif