#include "Main.h"

int stage1BGM;
int stage2BGM;
int bossBGM;
int clearBGM;
int shotSE;
int itemSE;
int selectSE;
int warningSE;
int hitSE;
int tipingSE;
//-----------------------------------------------------------------------------
void Stage1BGMPlay() {
	PlaySoundMem(stage1BGM, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(100, stage1BGM);
}
void Stage1BGMStop() {
	StopSoundMem(stage1BGM);
}

//-----------------------------------------------------------------------------
void Stage2BGMPlay() {
	PlaySoundMem(stage2BGM, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(100, stage2BGM);
}
void Stage2BGMStop() {
	StopSoundMem(stage2BGM);
}

//-----------------------------------------------------------------------------
void ClearBGMPlay() {
	//if( CheckMusic() == 0 ){
	//	PlayMusic("data/sound/clearBGM.mp3", DX_PLAYTYPE_LOOP);
	//}
	//SetVolumeMusic(100);
	if (CheckSoundMem(clearBGM) == 0) {
		PlaySoundMem(clearBGM, DX_PLAYTYPE_BACK);
	}
	ChangeVolumeSoundMem(100, clearBGM);
}
void ClearBGMStop() {
	StopSoundMem(clearBGM);
	//StopMusic();
}

//-----------------------------------------------------------------------------
void BossBGMPlay() {
	PlaySoundMem(bossBGM, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(100, bossBGM);
}
void BossBGMStop() {
	StopSoundMem(bossBGM);
}

//-----------------------------------------------------------------------------
void ShotSEPlay() {
	PlaySoundMem(shotSE, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(100, shotSE);
}

//-----------------------------------------------------------------------------
void ItemSEPlay() {
	PlaySoundMem(itemSE, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(150, itemSE);
}
//-----------------------------------------------------------------------------
void SelectSEPlay() {
	PlaySoundMem(selectSE, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(150, selectSE);
}
//-----------------------------------------------------------------------------
void WarningSEPlay() {
	PlaySoundMem(warningSE, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(150, warningSE);
}
//-----------------------------------------------------------------------------
void HitSEPlay() {
	PlaySoundMem(hitSE, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(200, hitSE);
}
//-----------------------------------------------------------------------------
void TipingSEPlay() {
	PlaySoundMem(tipingSE, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(60, tipingSE);
}