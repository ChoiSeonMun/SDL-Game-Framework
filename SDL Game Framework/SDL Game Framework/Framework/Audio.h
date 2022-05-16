#pragma once

#include "Type.h"

typedef struct Music
{
	Mix_Music* Music;
} Music;

typedef enum MusicFading
{
	MF_NO_FADING,
	MF_FADING_OUT,
	MF_FADING_IN
} EMusicFading;

bool Audio_Init(void);
void Audio_Cleanup(void);
void Audio_SetVolume(float volume);
float Audio_GetVolume(void);
void Audio_Pause(void);
void Audio_Resume(void);
void Audio_Rewind(void);
void Audio_Play(const Music* music, int32 loops);
void Audio_PlayFadeIn(const Music* music, int32 loops, int32 milliseconds);
void Audio_Stop(void);
void Audio_FadeOut(int32 milliseconds);
void Audio_HookMusicFinished(void(*callback)(void));
bool Audio_IsMusicPlaying(void);
bool Audio_IsMusicPaused(void);
EMusicFading Audio_IsMusicFading(void);
void Audio_LoadMusic(Music* music, const char* filename);
void Audio_FreeMusic(Music* music);

typedef struct SoundEffect
{
	Mix_Chunk*	Chunk;
	float		Volume;
} SoundEffect;

void Audio_LoadSoundEffect(SoundEffect* soundEffect, const char* filename);
void Audio_FreeSoundEffect(SoundEffect* soundEffect);
void Audio_SetEffectVolume(SoundEffect* soundEffect, float volume);
void Audio_PlaySoundEffect(const SoundEffect* soundEffect, int32 loops);
void Audio_PlaySoundEffectFadeIn(SoundEffect* soundEffect, int32 loops, int32 milliseconds);
void Audio_PauseSoundEffect(void);
void Audio_ResumeSoundEffect(void);
void Audio_StopSoundEffect(void);
void Audio_FadeOutSoundEffect(int32 milliseconds);
void Audio_HookSoundEffectFinished(void(*callback)(int32));
bool Audio_IsSoundEffectPlaying(void);
bool Audio_IsSoundEffectPaused(void);
#define INFINITY_LOOP -1