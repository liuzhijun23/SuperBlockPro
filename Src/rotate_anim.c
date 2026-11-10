#include "rotate_anim.h"
#include <string.h>

uint8_t Rotate_Render(uint32_t elapsed_ms, uint8_t frame[8])
{
    uint32_t remaining;
    int top = 0, bottom = 7, left = 0, right = 7;
    int r, c;

    memset(frame, 0xFF, 8);
    if (elapsed_ms < ROTATE_HOLD_MS)
        return 0;

    remaining = (elapsed_ms - ROTATE_HOLD_MS) / ROTATE_STEP_MS;
    if (remaining > 64u)
        remaining = 64u;

    /* bit0 is the left column. Begin at the bottom left:
     * right along bottom, up right, left along top, down left, then inward.
     */
    while (left <= right && top <= bottom)
    {
        for (c = left; c <= right; ++c)
        {
            if (remaining == 0u) goto done;
            frame[bottom] &= (uint8_t)~(1u << c);
            --remaining;
        }
        --bottom;
        for (r = bottom; r >= top; --r)
        {
            if (remaining == 0u) goto done;
            frame[r] &= (uint8_t)~(1u << right);
            --remaining;
        }
        --right;
        for (c = right; c >= left; --c)
        {
            if (remaining == 0u) goto done;
            frame[top] &= (uint8_t)~(1u << c);
            --remaining;
        }
        ++top;
        for (r = top; r <= bottom; ++r)
        {
            if (remaining == 0u) goto done;
            frame[r] &= (uint8_t)~(1u << left);
            --remaining;
        }
        ++left;
    }

done:
    return elapsed_ms >= ROTATE_DURATION_MS;
}
