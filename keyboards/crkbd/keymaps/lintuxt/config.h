/* @lintuxt - September 2021 - NO WARRANTY - ISC License */

#pragma once

#define MASTER_RIGHT

#define TAPPING_TERM 125
#define TAPPING_TERM_PER_KEY

#ifdef RGB_MATRIX_ENABLE
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120
  #define RGB_MATRIX_HUE_STEP 8
  #define RGB_MATRIX_SAT_STEP 4
  #define RGB_MATRIX_VAL_STEP 4
  #define RGB_MATRIX_SPD_STEP 10

  // LINTUXT_AMERICAN has a baked palette, so .hue and .sat are ignored.
  // .speed carries the underglow hue (UGH_DN/UGH_UP — .speed is part of
  // the split-sync transport so both halves stay in lockstep).
  #define RGB_MATRIX_DEFAULT_HUE   0  // unused (palette baked)
  #define RGB_MATRIX_DEFAULT_SAT 255  // unused (palette baked)
  #define RGB_MATRIX_DEFAULT_SPD 170  // underglow: blue (stored in .speed)

  #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_LINTUXT_AMERICAN
#endif

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
