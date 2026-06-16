#include "Main.h"
#include "Scene.h"
#include "GameInit.h"
#include "PlayerInit.h"
#include "PlayerUpdate.h"
#include "GameUpdate.h"
#include "Effect.h"
#include "Sound.h"
//---------------------------------------------------------------------------------
// 更新処理
// ---------------------------------------------------------------------------------
// プレイヤーのエフェクトパターン : 1,2
void PlayerEffectPattern() {
	effectChangeCount++;

	// 向き
	enum Direction {
		UP = 0,
		DOWN,
		RIGHT,
		LEFT
	};

	Direction direction;
	direction = UP;

	// 向きの初期化
	if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))		direction = UP;
	if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))	direction = DOWN;
	if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))	direction = RIGHT;
	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))	direction = LEFT;

	const int EFFECT_CHENGE_TIME = 20;
	// 20秒ごとに2パターンを切り替えている
	if (effectChangeCount < EFFECT_CHENGE_TIME) {
		// パターン１
		if (direction == UP)		playerPattern = PLAYER_UP1;
		if (direction == DOWN)		playerPattern = PLAYER_DOWN1;
		if (direction == RIGHT)		playerPattern = PLAYER_RIGHT1;
		if (direction == LEFT)		playerPattern = PLAYER_LEFT1;
	}
	else {
		// パターン２
		if (direction == UP)		playerPattern = PLAYER_UP2;
		if (direction == DOWN)		playerPattern = PLAYER_DOWN2;
		if (direction == RIGHT)		playerPattern = PLAYER_RIGHT2;
		if (direction == LEFT)		playerPattern = PLAYER_LEFT2;
	}

	if (direction == UP) {
		playerEffect.y = player.y + player.h;
		playerEffect.x = player.x + (player.w - playerEffect.w) / 2;
		playerEffectAngle = 270;
	}
	else if (direction == DOWN) {
		playerEffect.y = player.y - player.h;
		playerEffect.x = player.x + (player.w - playerEffect.w) / 2;
		playerEffectAngle = 90;
	}
	else if (direction == RIGHT) {
		playerEffect.y = player.y;
		playerEffect.x = player.x - playerEffect.w;
		playerEffectAngle = 0;
	}
	else if (direction == LEFT) {
		playerEffect.y = player.y;
		playerEffect.x = player.x + player.w;
		playerEffectAngle = 0;
	}

	playerEffect.centerX = playerEffect.x + playerEffect.w / 2;
	playerEffect.centerY = playerEffect.y + playerEffect.h / 2;

	if (effectChangeCount > 40)	effectChangeCount = 0;
}
// プレイヤーの移動 : 1,2
void PlayerUpdate() {
	playerEffect.y = player.y;
	player.shotTimer++;
	{
		// 移動
		bool move = false;
		if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)) {
			player.x += player.speed;
			PlayerEffectPattern();
			move = true;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A)) {
			player.x -= player.speed;
			PlayerEffectPattern();
			move = true;
		}
		if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W)) {
			player.y -= player.speed;
			PlayerEffectPattern();
			move = true;
		}
		if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S)) {
			player.y += player.speed;
			PlayerEffectPattern();
			move = true;
		}
		if (!move) {
			playerPattern = PLAYER_STAND;
		}
	}

	ClampPosition(player, gameSizeW, gameSizeH);

	// centerの更新
	player.centerX = player.x + player.w / 2;
	player.centerY = player.y + player.h / 2;

	// 無敵時間と点滅時間
	if (player.damageTimer > 0) {
		player.damageTimer--;
	}

	if (player.flashTimer < 60 && player.damageTimer > 0) {
		player.flashTimer++;
	}
	else {
		player.flashTimer = 0;
	}

	// hpの処理
	if (player.hp <= 0) {
		player.hp = 0;
		player.state = DIE;
		// ゲームオーバーへ
		sceneNext = SCENE_GAMEOVER;
		Stage1BGMStop();
		Stage2BGMStop();
		BossBGMStop();
	}
}

void PlayerDamage() {
	if (player.hit) {
		player.hp--;
		ScoreDown(200);
		SpownPointEffect(player.x, player.y, -200);

		player.damageTimer = 60;	// 無敵時間セット
		player.flashTimer = 0;

		noise.pActivateFunc(&noise);
	}
	if (player.damageTimer > 0) {
		player.hit = false;
	}
}
