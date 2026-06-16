#ifndef __SOURCE_H__
#define	__SOURCE_H__
// 星
class Star {
public:
	float x, y;
	float radius;
	int speed;

	void DrawStar(Star& star);
};

// 状態
enum State {
	INACTIVE = 0,	// 準備中
	ACTIVE,			// 活動中
	DIE				// 死亡

	// 弾はINACTIVEとACTIVEのみ使用
};

// 基本キャラクター構造体
struct BaseCharacter {
	float x, y;
	float centerX, centerY;
	int w, h;
	int image;

	float angle;
	int alpha;
	
	State state;
};

// 基本キャラクター描画関数
void Draw(BaseCharacter& basecharacter,float rot);

// 弾構造体
struct Shot : public BaseCharacter {
	float speed;

	float targetX;	// 発射する瞬間のプレイヤーの位置を記録する
	float targetY;
	float speedX;	// 弾の進む方向
	float speedY;
};

// プレイヤー構造体
struct Player : public BaseCharacter {
	int speed;
	int hp;
	bool hit;
	int shotTimer;
	
	int damageTimer;
	int flashTimer;

	Shot shot;
};

// プレイヤーの移動パターン
enum PlayerPattern {
	PLAYER_STAND = 0,
	PLAYER_RIGHT1,
	PLAYER_RIGHT2,
	PLAYER_LEFT1,
	PLAYER_LEFT2,
	PLAYER_UP1,
	PLAYER_UP2,
	PLAYER_DOWN1,
	PLAYER_DOWN2,
	PLAYER_MAX
};
extern PlayerPattern playerPattern;

// プレイヤーの射撃パターン
enum PlayerShotPattern {
	NORMAL_SHOT = 0,
	AIM_SHOT,
	THREE_WAY_SHOT
};
extern PlayerShotPattern playerShotPattern;

enum EnemyType {
	NULL_TYPE = 0,
	ENEMY_SHIELD = 1,
	ENEMY_EYE,
	ENEMY_ROT,
	ENEMY_BOSS
};
enum EnemyMoveMode {
	MOVE,
	TURN,
	MODE_NUM
};

// 目の敵出現エフェクト
struct EnemyEyeCreateEffect {
	int x;
	int y;
	int size;
	int alpha;
	bool isActive;
};

const int CREATE_EFFECT_NUM = 3;
// 敵構造体
struct Enemy : public BaseCharacter {
	float speed;
	int hp;

	int dir;	// 動く方向

	int shotTimer;
	int moveModeTimer;
	int createTimer;

	EnemyType enemyType;	// 敵の種類
	EnemyMoveMode enemyMoveMode;
	EnemyEyeCreateEffect createEffect[CREATE_EFFECT_NUM];
};

// 敵の死亡エフェクト構造体
struct EnemyDieEffect : public BaseCharacter {
	int timer;
	int frame;

	EnemyType enemyType;// 死んだ敵の種類を記録する
};

const int BOSS_IMAGE_NUM = 3;
// ボス
struct Boss : public Enemy {
	int images[BOSS_IMAGE_NUM];
	int currentImage;
	float hpMax;
};

struct Text: public BaseCharacter {
	char text[128];
	int enemyAliveCount;
};

struct PointEffect {
	float x, y;
	int frame;
	bool active;
	int alpha;
	char text[16];
};
const int POINT_EFFECT_NUM = 10;

void ClampPosition(BaseCharacter& basecharacter,int gameSizeW,int gameSizeH);


#endif