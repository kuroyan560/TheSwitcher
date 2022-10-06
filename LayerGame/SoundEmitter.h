#pragma once
enum SEName {
	FLOOR, MAGIC, WALK, GOALED, RESET, SHINE, MOVE
};

enum BGMName {
	TITLE, SELECT, GAME
};

void LoadSounds();
void SetFadeOut(BGMName what, int FadeSpeed);
void SoundUpdate();
void PlaySE(SEName what);
void PlayBGM(BGMName what);
void StopBGM(BGMName what);