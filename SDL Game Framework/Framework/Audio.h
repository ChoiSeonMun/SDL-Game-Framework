#pragma once

#include "Type.h"

typedef struct Music
{
	Mix_Music* Music;
} Music;


/// <summary>
/// ����� ���� ���̺귯���� �ʱ�ȭ�Ѵ�.
/// </summary>
/// <returns>�����ߴٸ� true, �ƴϸ� false</returns>
bool Audio_Init(void);

/// <summary>
/// ����� ���� ���̺귯���� �����Ѵ�.
/// </summary>
void Audio_Cleanup(void);

/// <summary>
/// ������ �ҷ��´�.
/// </summary>
/// <param name="music">���� ��ü</param>
/// <param name="filename">���� �̸�(.mp3, .wav, .flac ����)</param>
void Audio_LoadMusic(Music* music, const char* filename);

/// <summary>
/// ���� ��ü�� ���õ� �ڿ��� �����Ѵ�. �� Release()�� �������.
/// </summary>
/// <param name="music">���� ��ü</param>
void Audio_FreeMusic(Music* music);

/// <summary>
/// ���� ������ �����Ѵ�.
/// </summary>
/// <param name="volume">0.0 ~ 1.0������ ����ȭ�� ��</param>
void Audio_SetVolume(float volume);

/// <summary>
/// ���� ������ ���´�.
/// </summary>
/// <returns>����ȭ�� BGM ������</returns>
float Audio_GetVolume(void);

/// <summary>
/// ���� ����� �����.
/// </summary>
void Audio_Pause(void);

/// <summary>
/// ���� ����� �簳�Ѵ�.
/// </summary>
void Audio_Resume(void);

/// <summary>
/// ������ �ǰ��´�.
/// </summary>
void Audio_Rewind(void);

/// <summary>
/// ������ ����Ѵ�.
/// </summary>
/// <param name="music">���� ��ü</param>
/// <param name="loops">�ݺ� Ƚ��</param>
void Audio_Play(const Music* music, int32 loops);

/// <summary>
/// ������ ���̵� �ΰ� �Բ� ����Ѵ�.
/// </summary>
/// <param name="music">���� ��ü</param>
/// <param name="loops">�ݺ� Ƚ��</param>
/// <param name="milliseconds">���̵� �� �ð�</param>
void Audio_PlayFadeIn(const Music* music, int32 loops, int32 milliseconds);

/// <summary>
/// ���� ����� �ߴ��Ѵ�.
/// </summary>
void Audio_Stop(void);

/// <summary>
/// ���� ����� ���̵� �ƿ��� �Բ� �Ѵ�.
/// </summary>
/// <param name="milliseconds">���̵� �ƿ� �ð�</param>
void Audio_FadeOut(int32 milliseconds);

/// <summary>
/// ���� ����� ���� �� �ݹ��� �߰��Ѵ�.
/// </summary>
/// <param name="callback">�ݹ�</param>
void Audio_HookMusicFinished(void(*callback)(void));

/// <summary>
/// ���� ������ ��� ������ �Ǻ��Ѵ�.
/// </summary>
/// <returns>��� ���̶�� true, �ƴϸ� false</returns>
bool Audio_IsMusicPlaying(void);

/// <summary>
/// ���� ������ ������� �Ǻ��Ѵ�.
/// </summary>
/// <returns>����ٸ� true, �ƴϸ� false</returns>
bool Audio_IsMusicPaused(void);

typedef enum MusicFading
{
	MF_NO_FADING,
	MF_FADING_OUT,
	MF_FADING_IN
} EMusicFading;

/// <summary>
/// ���� ������ ���̵� ��/�ƿ� ������ �Ǻ��Ѵ�.
/// </summary>
/// <returns>���̵� ����</returns>
EMusicFading Audio_IsMusicFading(void);


typedef struct SoundEffect
{
	Mix_Chunk*	Chunk;
	float		Volume;
} SoundEffect;

/// <summary>
/// ����Ʈ�� �ҷ��´�.
/// </summary>
/// <param name="soundEffect">����Ʈ ��ü</param>
/// <param name="filename">���� �̸�(.wav�� ����)</param>
void Audio_LoadSoundEffect(SoundEffect* soundEffect, const char* filename);

/// <summary>
/// ����Ʈ ���� �ڿ��� �����Ѵ�. �ݵ�� Release()�� ����Ѵ�.
/// </summary>
/// <param name="soundEffect">����Ʈ ��ü</param>
void Audio_FreeSoundEffect(SoundEffect* soundEffect);

/// <summary>
/// ����Ʈ ������ �����Ѵ�.
/// </summary>
/// <param name="soundEffect">����Ʈ ��ü</param>
/// <param name="volume">0.0 ~ 1.0���� ����ȭ�� ����</param>
void Audio_SetEffectVolume(SoundEffect* soundEffect, float volume);

/// <summary>
/// ����Ʈ�� ����Ѵ�.
/// </summary>
/// <param name="soundEffect">����Ʈ ��ü</param>
/// <param name="loops">�ݺ� Ƚ��</param>
void Audio_PlaySoundEffect(const SoundEffect* soundEffect, int32 loops);

/// <summary>
/// ����Ʈ�� ���̵� �ΰ� �Բ� ����Ѵ�.
/// </summary>
/// <param name="soundEffect">����Ʈ ��ü</param>
/// <param name="loops">�ݺ� Ƚ��</param>
/// <param name="milliseconds">���̵� �� �ð�</param>
void Audio_PlaySoundEffectFadeIn(SoundEffect* soundEffect, int32 loops, int32 milliseconds);

/// <summary>
/// ����Ʈ ����� �����.
/// </summary>
void Audio_PauseSoundEffect(void);

/// <summary>
/// ����Ʈ ����� �簳�Ѵ�.
/// </summary>
void Audio_ResumeSoundEffect(void);

/// <summary>
/// ����Ʈ ����� �ߴ��Ѵ�.
/// </summary>
void Audio_StopSoundEffect(void);

/// <summary>
/// ����Ʈ ����� ���̵� �ƿ��� �Բ� �ߴ��Ѵ�.
/// </summary>
/// <param name="milliseconds">���̵� �ƿ� �ð�</param>
void Audio_FadeOutSoundEffect(int32 milliseconds);

/// <summary>
/// ����Ʈ ����� ���� �� �ݹ��� ����Ѵ�.
/// </summary>
/// <param name="callback">�ݹ�</param>
void Audio_HookSoundEffectFinished(void(*callback)(int32));

/// <summary>
/// ���� ���� ����Ʈ�� ��� ������ Ȯ���Ѵ�.
/// </summary>
/// <returns>��� ���̶�� true, �ƴϸ� false</returns>
bool Audio_IsSoundEffectPlaying(void);

/// <summary>
/// ���� ���� ����Ʈ�� ������� Ȯ���Ѵ�.
/// </summary>
/// <returns>����ٸ� true, �ƴϸ� false</returns>
bool Audio_IsSoundEffectPaused(void);

// ���� ���� �ÿ� ����Ѵ�.
#define INFINITY_LOOP -1