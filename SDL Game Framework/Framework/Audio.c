#include "stdafx.h"
#include "Audio.h"

#define ALL_CHANNEL -1

static float s_MusicVolume = 0.0f;
static char s_path[MAX_PATH];

bool Audio_Init(void)
{
	int flags = MIX_INIT_FLAC | MIX_INIT_MP3;
	int initResult = Mix_Init(flags);
	if (flags != (flags & initResult))
	{
		return false;
	}

	if (0 != Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096))
	{
		return false;
	}

	Audio_SetVolume(0.5f);

	return true;
}

void Audio_Cleanup(void)
{
	Mix_CloseAudio();
	Mix_Quit();
}

void Audio_SetVolume(float volume)
{
	s_MusicVolume = Clamp(0.0f, volume, 1.0f);
	
	int32 realVolume = 0 + s_MusicVolume * MIX_MAX_VOLUME;
	Mix_VolumeMusic(realVolume);
}

float Audio_GetVolume(void)
{
	return s_MusicVolume;
}

void Audio_Pause(void)
{
	Mix_PauseMusic();
}

void Audio_Resume(void)
{
	Mix_ResumeMusic();
}

void Audio_Rewind(void)
{
	Mix_RewindMusic();
}

void Audio_Play(const Music* music, int32 loops)
{
	Mix_PlayMusic(music->Music, loops);
}

void Audio_PlayFadeIn(const Music* music, int32 loops, int32 milliseconds)
{
	Mix_FadeInMusic(music->Music, loops, milliseconds);
}

void Audio_Stop(void)
{
	Mix_HaltMusic();
}

void Audio_FadeOut(int32 milliseconds)
{
	Mix_FadeOutMusic(milliseconds);
}

void Audio_HookMusicFinished(void(*callback)(void))
{
	Mix_HookMusicFinished(callback);
}

bool Audio_IsMusicPlaying(void)
{
	if (0 == Mix_PlayingMusic())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Audio_IsMusicPaused(void)
{
	if (0 == Mix_PausedMusic())
	{
		return false;
	}
	else
	{
		return true;
	}
}

EMusicFading Audio_IsMusicFading(void)
{
	Mix_Fading result = Mix_FadingMusic();

	return result;
}

void Audio_LoadMusic(Music* music, const char* filename)
{
	LogInfo("Sound Loading... %s", filename);

	sprintf_s(s_path, sizeof(s_path), "%s/%s", SOUND_DIRECTORY, filename);
	music->Music = Mix_LoadMUS(s_path);
}

void Audio_FreeMusic(Music* music)
{
	Mix_FreeMusic(music->Music);
	music->Music = NULL;
}

void Audio_LoadSoundEffect(SoundEffect* soundEffect, const char* filename)
{
	LogInfo("Sound Effect Loading... %s", filename);

	sprintf_s(s_path, sizeof(s_path), "%s/%s", SOUND_DIRECTORY, filename);
	soundEffect->Chunk = Mix_LoadWAV(s_path);
	Audio_SetEffectVolume(soundEffect, 1.0f);
}

void Audio_FreeSoundEffect(SoundEffect* soundEffect)
{
	Mix_FreeChunk(soundEffect->Chunk);
	soundEffect->Chunk = NULL;
}

void Audio_SetEffectVolume(SoundEffect* soundEffect, float volume)
{
	soundEffect->Volume = Clamp(0.0f, volume, 1.0f);

	int32 realVolume = 0 + soundEffect->Volume * MIX_MAX_VOLUME;
	Mix_VolumeChunk(soundEffect->Chunk, soundEffect->Volume);
}

void Audio_PlaySoundEffect(const SoundEffect* soundEffect, int32 loops)
{
	Mix_PlayChannel(-1, soundEffect->Chunk, loops);
}

void Audio_PlaySoundEffectFadeIn(SoundEffect* soundEffect, int32 loops, int32 milliseconds)
{
	Mix_FadeInChannel(-1, soundEffect->Chunk, loops, milliseconds);
}

void Audio_PauseSoundEffect(void)
{
	Mix_Pause(-1);
}

void Audio_ResumeSoundEffect(void)
{
	Mix_Resume(-1);
}

void Audio_StopSoundEffect(void)
{
	Mix_HaltChannel(-1);
}

void Audio_FadeOutSoundEffect(int32 milliseconds)
{
	Mix_FadeOutChannel(-1, milliseconds);
}

void Audio_HookSoundEffectFinished(void(*callback)(int32))
{
	Mix_ChannelFinished(callback);
}

bool Audio_IsSoundEffectPlaying(void)
{
	if (0 == Mix_Playing(-1))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Audio_IsSoundEffectPaused(void)
{
	if (0 == Mix_Paused(-1))
	{
		return false;
	}
	else
	{
		return true;
	}
}
