#include "SoundEmitter.h"
#include"DxLib.h"

static int seHandle[7];
static int bgmHandle[3];

static int pal;
static bool fadeFlag;
static int speed;
static BGMName fadeBGM;
static const int NORMAL_PAL[3] = { 140,140,140 };

void LoadSounds(){
	seHandle[FLOOR] = LoadSoundMem("_resource/sound/SE/floorSE.mp3");
	seHandle[MAGIC] = LoadSoundMem("_resource/sound/SE/magicSE.mp3");
	seHandle[WALK] = LoadSoundMem("_resource/sound/SE/walkSE.mp3");
	seHandle[GOALED] = LoadSoundMem("_resource/sound/SE/goalSE.mp3");
	seHandle[RESET] = LoadSoundMem("_resource/sound/SE/resetSE.mp3");
	seHandle[SHINE] = LoadSoundMem("_resource/sound/SE/shineSE.mp3");
	seHandle[MOVE] = LoadSoundMem("_resource/sound/SE/moveSE.mp3");
	ChangeVolumeSoundMem(230, seHandle[GOALED]);
	ChangeVolumeSoundMem(200, seHandle[MOVE]);

	bgmHandle[TITLE] = LoadSoundMem("_resource/sound/BGM/bgmFantasy.wav");
	bgmHandle[SELECT] = LoadSoundMem("_resource/sound/BGM/bgmFantasy.wav");
	bgmHandle[GAME] = LoadSoundMem("_resource/sound/BGM/bgmFantasy.wav");
 	ChangeVolumeSoundMem(NORMAL_PAL[TITLE],bgmHandle[TITLE]);
	ChangeVolumeSoundMem(NORMAL_PAL[SELECT], bgmHandle[SELECT]);
	ChangeVolumeSoundMem(NORMAL_PAL[GAME], bgmHandle[GAME]);
}

void SetFadeOut(BGMName what,int FadeSpeed){
	fadeBGM = what;
	fadeFlag = true;
	pal = NORMAL_PAL[what];
	speed = FadeSpeed;
}

void SoundUpdate(){
	if (fadeFlag) {
		ChangeVolumeSoundMem(pal, bgmHandle[fadeBGM]);
		pal -= speed;
		if (pal < 0) {
			StopSoundMem(bgmHandle[fadeBGM]);
			ChangeVolumeSoundMem(NORMAL_PAL[fadeBGM], bgmHandle[fadeBGM]);
			fadeFlag = false;
		}
	}
}

void PlaySE(SEName what){
	if (CheckSoundMem(seHandle[what])) {
		StopSoundMem(seHandle[what]);
	}
	PlaySoundMem(seHandle[what], DX_PLAYTYPE_BACK);
}

void PlayBGM(BGMName what){
	if (!CheckSoundMem(bgmHandle[what])) {
		PlaySoundMem(bgmHandle[what], DX_PLAYTYPE_LOOP);
	}
}

void StopBGM(BGMName what){
	if (CheckSoundMem(bgmHandle[what])) {
		StopSoundMem(bgmHandle[what]);
	}
}
