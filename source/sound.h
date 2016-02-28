#pragma once
#include <3ds.h>

typedef struct themeSound {
    u8* sndbuffer;
    u32 sndsize;
    int channel;
    bool loaded;
    int duration;
} themeSound;

bool audioIsActive = true;
bool audio_load(const char *audio, themeSound * aThemeSound){
	if (!audioIsActive) debugPrint("Audio is disabled.");
	FILE *file = fopen(audio, "rb");
	if(file != NULL && audioIsActive){
		fseek(file, 0, SEEK_END);
		aThemeSound->sndsize = ftell(file);
		fseek(file, 0, SEEK_SET);
		aThemeSound->sndsize = aThemeSound->sndsize - 0x48;
		fseek(file, 0x48, SEEK_SET);
		aThemeSound->sndbuffer = (u8*)linearAlloc(aThemeSound->sndsize);
		fread(aThemeSound->sndbuffer, 1, aThemeSound->sndsize, file);
		fclose(file);
		if (aThemeSound->sndbuffer != NULL) {
            aThemeSound->loaded = true;
		}
		else {
            aThemeSound->loaded = false;
		}
	}
	else {
        aThemeSound->loaded = false;
	}

	if (aThemeSound->loaded) {
        aThemeSound->duration = aThemeSound->sndsize / 88244;
	}
	else {
        aThemeSound->duration = 0;
	}
	return aThemeSound->loaded;
}

void audio_play(themeSound * aThemeSound, bool loop) {
if (!audioIsActive) debugPrint("Audio is disabled.");
   if (aThemeSound->loaded && audioIsActive) {
    u32 flags;

    if (loop) {
        flags = SOUND_FORMAT_16BIT | SOUND_REPEAT;
    }
    else {
        flags = SOUND_FORMAT_16BIT;
    }

    csndPlaySound(aThemeSound->channel, flags, 44100, 1, 0, aThemeSound->sndbuffer, aThemeSound->sndbuffer, aThemeSound->sndsize);
   }
}

void audio_free(themeSound * aThemeSound) {
if (!audioIsActive) debugPrint("Audio is disabled.");
    if (audioIsActive) {
        memset(aThemeSound->sndbuffer, 0, aThemeSound->sndsize);
        GSPGPU_FlushDataCache(aThemeSound->sndbuffer, aThemeSound->sndsize);
        linearFree(aThemeSound->sndbuffer);
    }
}

void audio_stop(void){
if (!audioIsActive) debugPrint("Audio is disabled.");
    if (audioIsActive) {
        csndExecCmds(true);

        CSND_SetPlayState(0x8, 0);
        CSND_SetPlayState(0x9, 0);
        CSND_SetPlayState(0x10, 0);

        csndExecCmds(true);

        csndExecCmds(true);
    }
}
