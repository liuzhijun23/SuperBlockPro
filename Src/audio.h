#ifndef AUDIO_H_
#define AUDIO_H_

#define AUDIO_VOLUME_PERCENT 200

void Audio_PlayShutdown(void);
void Audio_Start(void);       /* Boot chime */
void Audio_PlayPass(void);    /* Success chime */
void Audio_PlayResult(void);  /* Timed grade chime */
void Audio_PlayCountdown(void);
void Audio_CancelCountdown(void);
void Audio_StopPlayback(void);
void Audio_PlayTimeout(void);
void Audio_OnTimerTick(void); /* Called by TIM17 at 8 kHz */

#endif
