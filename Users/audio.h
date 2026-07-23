#ifndef AUDIO_H_
#define AUDIO_H_

#include "stm8s.h"

#define AUDIO_SAMPLE_RATE     8000
#define AUDIO_TOTAL_SAMPLES   8022
#define AUDIO_ADPCM_SIZE      4011

extern const uint8_t audio_adpcm_data[];
extern s16 predictor;
extern s8  step_index;
extern u16 adpcm_byte_pos;
extern u8  use_high_nibble;  // 0=低4bit, 1=高4bit
extern u8  playing;

void Audio_Start(void);
int16_t ADPCM_Decode(uint8_t nibble);














#endif