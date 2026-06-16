#ifndef __EFFECT_H__
#define __EFFECT_H__

// エフェクト構造体
struct Effect {
	float x, y;
	void (*pUpdateFunc)(Effect* pEffect);
	void (*pDrawFunc)(Effect* pEffect);
};

void InitEffect
(
	Effect* pEffect,
	float x, float y,
	void (*pUpdateFunc)(Effect*) = NULL,
	void (*pDrawFunc)(Effect*) = NULL
);

struct EffectNoise : public Effect {
	int image;
	int timer;
	void (*pActivateFunc)(Effect*);
};

void InitEffectNoise(Effect* pEffect);

extern EffectNoise noise;

#endif