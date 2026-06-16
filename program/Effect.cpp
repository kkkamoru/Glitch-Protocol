#include "Main.h"
#include "Effect.h"
#include "GameUpdate.h"
#include "Scene.h"

// エフェクトの基本初期化
void InitEffect
(
	Effect* pEffect,
	float x, float y,
	void (*pUpdateFunc)(Effect*),
	void (*pDrawFunc)(Effect*)
)
{
	pEffect->x = x;
	pEffect->y = y;
	pEffect->pUpdateFunc = pUpdateFunc;
	pEffect->pDrawFunc = pDrawFunc;
}


void UpdateEffectNoise(Effect* pEffect);
void DrawEffectNoise(Effect* pEffect);
void ActivateEffectNoise(Effect* pEffect);

// ノイズエフェクトの初期化
void InitEffectNoise(Effect* pEffect)
{
	EffectNoise* self = (EffectNoise*)pEffect;

	InitEffect(pEffect, 0.0f, 0.0f, UpdateEffectNoise, DrawEffectNoise);

	self->pActivateFunc = ActivateEffectNoise;
	self->image = LoadGraph("data/effect/damage.png");
	self->timer = 0;
}

// ノイズエフェクトの更新
void UpdateEffectNoise(Effect* pEffect) {
	EffectNoise* self = (EffectNoise*)pEffect;
	switch (sceneNum) {
	case SCENE_STAGE1:
		// ランダムな位置に描画しノイズを表現させる
		self->x = GetRandomF(-200.0f, 0.0f);
		self->y = GetRandomF(-550.0f, 0.0f);

		break;
	case SCENE_STAGE2:
		self->x = GetRandomF(-550.0f, 0.0f);
		self->y = GetRandomF(-200.0f, 0.0f);
		break;
	}
	self->timer--;
	if (0 >= self->timer) self->timer = 0;
}

// ノイズエフェクトの描画
void DrawEffectNoise(Effect* pEffect) {
	EffectNoise* self = (EffectNoise*)pEffect;

	if (self->timer > 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawGraph(self->x, self->y, self->image, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// ノイズエフェクトの発動
void ActivateEffectNoise(Effect* pEffect)
{
	EffectNoise* self = (EffectNoise*)pEffect;
	self->timer = 10;
}


EffectNoise noise;
