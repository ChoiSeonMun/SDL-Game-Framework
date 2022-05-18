#pragma once

#include "Type.h"

typedef struct Music
{
	Mix_Music* Music;
} Music;


/// <summary>
/// 오디오 관련 라이브러리를 초기화한다.
/// </summary>
/// <returns>성공했다면 true, 아니면 false</returns>
bool Audio_Init(void);

/// <summary>
/// 오디오 관련 라이브러리를 정리한다.
/// </summary>
void Audio_Cleanup(void);

/// <summary>
/// 음악을 불러온다.
/// </summary>
/// <param name="music">음악 객체</param>
/// <param name="filename">파일 이름(.mp3, .wav, .flac 지원)</param>
void Audio_LoadMusic(Music* music, const char* filename);

/// <summary>
/// 음악 객체와 관련된 자원을 해제한다. 꼭 Release()에 등록하자.
/// </summary>
/// <param name="music">음악 객체</param>
void Audio_FreeMusic(Music* music);

/// <summary>
/// 음악 볼륨을 조절한다.
/// </summary>
/// <param name="volume">0.0 ~ 1.0까지의 정규화된 값</param>
void Audio_SetVolume(float volume);

/// <summary>
/// 음악 볼륨을 얻어온다.
/// </summary>
/// <returns>정규화된 BGM 볼륨값</returns>
float Audio_GetVolume(void);

/// <summary>
/// 음악 재생을 멈춘다.
/// </summary>
void Audio_Pause(void);

/// <summary>
/// 음악 재생을 재개한다.
/// </summary>
void Audio_Resume(void);

/// <summary>
/// 음악을 되감는다.
/// </summary>
void Audio_Rewind(void);

/// <summary>
/// 음악을 재생한다.
/// </summary>
/// <param name="music">음악 객체</param>
/// <param name="loops">반복 횟수</param>
void Audio_Play(const Music* music, int32 loops);

/// <summary>
/// 음악을 페이드 인과 함께 재생한다.
/// </summary>
/// <param name="music">음악 객체</param>
/// <param name="loops">반복 횟수</param>
/// <param name="milliseconds">페이드 인 시간</param>
void Audio_PlayFadeIn(const Music* music, int32 loops, int32 milliseconds);

/// <summary>
/// 음악 재생을 중단한다.
/// </summary>
void Audio_Stop(void);

/// <summary>
/// 음악 재생을 페이드 아웃과 함께 한다.
/// </summary>
/// <param name="milliseconds">페이드 아웃 시간</param>
void Audio_FadeOut(int32 milliseconds);

/// <summary>
/// 음악 재생이 끝날 때 콜백을 추가한다.
/// </summary>
/// <param name="callback">콜백</param>
void Audio_HookMusicFinished(void(*callback)(void));

/// <summary>
/// 현재 음악이 재생 중인지 판별한다.
/// </summary>
/// <returns>재생 중이라면 true, 아니면 false</returns>
bool Audio_IsMusicPlaying(void);

/// <summary>
/// 현재 음악이 멈췄는지 판별한다.
/// </summary>
/// <returns>멈췄다면 true, 아니면 false</returns>
bool Audio_IsMusicPaused(void);

typedef enum MusicFading
{
	MF_NO_FADING,
	MF_FADING_OUT,
	MF_FADING_IN
} EMusicFading;

/// <summary>
/// 현재 음악이 페이드 인/아웃 중인지 판별한다.
/// </summary>
/// <returns>페이드 여부</returns>
EMusicFading Audio_IsMusicFading(void);


typedef struct SoundEffect
{
	Mix_Chunk*	Chunk;
	float		Volume;
} SoundEffect;

/// <summary>
/// 이펙트를 불러온다.
/// </summary>
/// <param name="soundEffect">이펙트 객체</param>
/// <param name="filename">파일 이름(.wav만 지원)</param>
void Audio_LoadSoundEffect(SoundEffect* soundEffect, const char* filename);

/// <summary>
/// 이펙트 관련 자원을 정리한다. 반드시 Release()에 등록한다.
/// </summary>
/// <param name="soundEffect">이펙트 객체</param>
void Audio_FreeSoundEffect(SoundEffect* soundEffect);

/// <summary>
/// 이펙트 볼륨을 조절한다.
/// </summary>
/// <param name="soundEffect">이펙트 객체</param>
/// <param name="volume">0.0 ~ 1.0까지 정규화된 볼륨</param>
void Audio_SetEffectVolume(SoundEffect* soundEffect, float volume);

/// <summary>
/// 이펙트를 재생한다.
/// </summary>
/// <param name="soundEffect">이펙트 객체</param>
/// <param name="loops">반복 횟수</param>
void Audio_PlaySoundEffect(const SoundEffect* soundEffect, int32 loops);

/// <summary>
/// 이펙트를 페이드 인과 함께 재생한다.
/// </summary>
/// <param name="soundEffect">이펙트 객체</param>
/// <param name="loops">반복 횟수</param>
/// <param name="milliseconds">페이드 인 시간</param>
void Audio_PlaySoundEffectFadeIn(SoundEffect* soundEffect, int32 loops, int32 milliseconds);

/// <summary>
/// 이펙트 재생을 멈춘다.
/// </summary>
void Audio_PauseSoundEffect(void);

/// <summary>
/// 이펙트 재생을 재개한다.
/// </summary>
void Audio_ResumeSoundEffect(void);

/// <summary>
/// 이펙트 재생을 중단한다.
/// </summary>
void Audio_StopSoundEffect(void);

/// <summary>
/// 이펙트 재생을 페이드 아웃과 함께 중단한다.
/// </summary>
/// <param name="milliseconds">페이드 아웃 시간</param>
void Audio_FadeOutSoundEffect(int32 milliseconds);

/// <summary>
/// 이펙트 재생이 끝날 때 콜백을 등록한다.
/// </summary>
/// <param name="callback">콜백</param>
void Audio_HookSoundEffectFinished(void(*callback)(int32));

/// <summary>
/// 지금 현재 이펙트가 재생 중인지 확인한다.
/// </summary>
/// <returns>재생 중이라면 true, 아니면 false</returns>
bool Audio_IsSoundEffectPlaying(void);

/// <summary>
/// 지금 현재 이펙트가 멈췄는지 확인한다.
/// </summary>
/// <returns>멈췄다면 true, 아니면 false</returns>
bool Audio_IsSoundEffectPaused(void);

// 무한 루프 시에 사용한다.
#define INFINITY_LOOP -1