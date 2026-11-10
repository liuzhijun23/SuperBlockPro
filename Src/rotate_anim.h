#ifndef ROTATE_ANIM_H_
#define ROTATE_ANIM_H_

#include <stdint.h>

/* Full board -> counterclockwise inward spiral -> short dark pause. */
#define ROTATE_HOLD_MS       200u
#define ROTATE_STEP_MS        42u
#define ROTATE_DARK_MS      1000u
#define ROTATE_DURATION_MS (ROTATE_HOLD_MS + 64u * ROTATE_STEP_MS + ROTATE_DARK_MS)

/* Render into an inactive 8-row buffer. Returns 1 when the effect is finished. */
uint8_t Rotate_Render(uint32_t elapsed_ms, uint8_t frame[8]);

#endif
