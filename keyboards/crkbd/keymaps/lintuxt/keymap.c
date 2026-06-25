/* @lintuxt - January 2024 - NO WARRANTY - ISC License */

#include QMK_KEYBOARD_H

enum custom_keycodes {
    RGB_RST = SAFE_RANGE,
    MAG_HL,
    MAG_HR,
    MAG_UP,
    MAG_DOWN,
    MAG_TL,
    MAG_TR,
    MAG_BL,
    MAG_BR,
    MAG_L13,
    MAG_L23,
    MAG_C3,
    MAG_R23,
    MAG_R13,
    MAG_ND,
    MAG_PD,
    MAG_MAX,
    MAG_C,
    MAG_RST,
    ONEPSAF,
    UGH_DN,
    UGH_UP
};

// Underglow hue lives in rgb_matrix_config.speed, which is already part
// of QMK's RGB split sync and EEPROM path. RM_SPD keys aren't bound, so
// repurposing .speed has no functional cost.
#define LP_UG_HUE_STEP 8

void mag(uint16_t code) {
    SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_RALT));
    switch (code) {
        case MAG_HL:
            SEND_STRING(SS_TAP(X_LEFT));
            break;
        case MAG_HR:
            SEND_STRING(SS_TAP(X_RIGHT));
            break;
        case MAG_UP:
            SEND_STRING(SS_TAP(X_UP));
            break;
        case MAG_DOWN:
            SEND_STRING(SS_TAP(X_DOWN));
            break;
        case MAG_TL:
            SEND_STRING(SS_TAP(X_U));
            break;
        case MAG_TR:
            SEND_STRING(SS_TAP(X_I));
            break;
        case MAG_BL:
            SEND_STRING(SS_TAP(X_J));
            break;
        case MAG_BR:
            SEND_STRING(SS_TAP(X_K));
            break;
        case MAG_L13:
            SEND_STRING(SS_TAP(X_D));
            break;
        case MAG_L23:
            SEND_STRING(SS_TAP(X_E));
            break;
        case MAG_C3:
            SEND_STRING(SS_TAP(X_F));
            break;
        case MAG_R23:
            SEND_STRING(SS_TAP(X_T));
            break;
        case MAG_R13:
            SEND_STRING(SS_TAP(X_G));
            break;
        case MAG_ND:
            SEND_STRING(SS_DOWN(X_LCMD) SS_TAP(X_RIGHT) SS_DELAY(50) SS_UP(X_LCMD));
            break;
        case MAG_PD:
            SEND_STRING(SS_DOWN(X_LCMD) SS_TAP(X_LEFT) SS_DELAY(50) SS_UP(X_LCMD));
            break;
        case MAG_MAX:
            SEND_STRING(SS_TAP(X_ENTER));
            break;
        case MAG_C:
            SEND_STRING(SS_TAP(X_C));
            break;
        case MAG_RST:
            SEND_STRING(SS_TAP(X_BACKSPACE));
            break;
    }
    SEND_STRING(SS_DELAY(100) SS_UP(X_LCTL) SS_UP(X_RALT));
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   KC_LGUI,   MO(2),  KC_SPC,              KC_ENT,   MO(3), KC_RALT
                               //`-----------------------------------'  `--------------------------'
    ),

    [1] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   KC_LGUI,   MO(2),  KC_SPC,              KC_ENT,   MO(3), KC_RALT
                               //`-----------------------------------'  `--------------------------'
    ),

    [2] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_ESC, KC_EXLM,   KC_AT, KC_HASH, KC_LPRN, KC_RPRN,                      KC_UNDS, KC_PLUS, KC_TILD, XXXXXXX, XXXXXXX,  KC_DEL,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL,  KC_DLR, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC,                      KC_MINS,  KC_EQL,  KC_GRV, XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_AMPR, KC_ASTR, KC_PIPE, KC_LCBR, KC_RCBR,                      KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______,  KC_SPC,     KC_ENT,   MO(4), KC_RALT
                                        //`--------------------------'  `--------------------------'
    ),

    [3] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_ESC,    KC_1,    KC_2,    KC_3,    KC_0, XXXXXXX,                      XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, XXXXXXX,  KC_DEL,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL,    KC_4,    KC_5,    KC_6,   TG(5), XXXXXXX,                      XXXXXXX, KC_LEFT, KC_DOWN,KC_RIGHT, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI,   MO(4),  KC_SPC,     KC_ENT, _______, KC_RALT
                                        //`--------------------------'  `--------------------------'
    ),

    [4] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RGB_RST, RM_HUED, RM_HUEU, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_F7, KC_MUTE,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        RM_TOGG, RM_SATD, RM_SATU, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_F8, KC_VOLD,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        RM_NEXT, RM_VALD, RM_VALU, UGH_DN, UGH_UP, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_F9, KC_VOLU,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            XXXXXXX, _______, XXXXXXX,    XXXXXXX, _______, XXXXXXX
                                        //`--------------------------'  `--------------------------'
    ),

    [5] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
          TG(5), ONEPSAF, MAG_L23, XXXXXXX, MAG_R23, XXXXXXX,                      XXXXXXX,  MAG_TL,  MAG_UP,  MAG_TR, XXXXXXX, MAG_RST,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
          DF(0), XXXXXXX, MAG_L13,  MAG_C3, MAG_R13, XXXXXXX,                      XXXXXXX,  MAG_HL,   MAG_C,  MAG_HR, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
          DF(1), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  MAG_PD,                       MAG_ND,  MAG_BL,MAG_DOWN,  MAG_BR, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            XXXXXXX, XXXXXXX,   MAG_C,    MAG_MAX, XXXXXXX, XXXXXXX
                                        //`--------------------------'  `--------------------------'
    ),

};

#ifdef OLED_ENABLE

// Both halves render vertically-stacked letters in the same custom Corne
// lowercase font. Master (RHS) shows the active layer name (7 chars);
// slave (LHS) shows "alexi" (5 chars). Both use OLED_ROTATION_270 — if
// either side reads with the wrong handedness, flip its rotation to
// OLED_ROTATION_90.
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

// --- Corne lowercase font --------------------------------------------------
// Variable-width bitmaps, all 24 rows tall. Baseline at row 18.
// x-height letters fill rows 5..18.
// Ascender letters (b, d, k, l, t) extend into rows 0..4.
// Descender letters (g, j, q, y) extend into rows 19..23.
//
// 'i' has a 3-row tittle (rows 1..3) + 1-row gap + stem (rows 5..18).
// All glyphs are now custom — none remain from the original Corne
// logo bitmap.
//
// Storage: each row is a uint16_t with col 0 in the MSB. Letters narrower
// than 16 columns leave the low bits zero. Total ~1.3 KB in PROGMEM.

#define CORNE_BITMAP_H    24
#define CORNE_BASELINE    18    // bitmap row where letters sit

typedef struct {
    uint8_t  width;
    uint16_t rows[CORNE_BITMAP_H];
} corne_letter_t;

static const corne_letter_t corne_font[26] PROGMEM = {
    // 'a': two-story, Inter/SF-Pro-Bold style. Three stacked regions
    // (top to bottom):
    //   TOP BAR (rows 5..7) — horizontal cap with a 3-step chamfered
    //                         left end (matching 'o'), merging flat
    //                         into the stem on the right.
    //   GAP    (rows 8..9) — only the stem; this is the open notch
    //                         on the top-left that signals 'a' not 'd'.
    //   BELLY  (rows 10..18)— enclosed bowl, 2-step chamfer on both
    //                         left corners (slightly less rounded than
    //                         'o' to keep a visible counter), flat
    //                         right edge against the stem. Counter is
    //                         ~7 cols × 3 rows.
    // The stem (cols 10..13) is continuous from row 5 through row 18,
    // holding the top bar and belly together.
    ['a' - 'a'] = { 14, {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x1FFC,  // ...###########   top bar  ┐
        0x3FFC,  // ..############   top bar  │
        0x7FFC,  // .#############   top bar  ┘
        0x003C,  // ..........####   GAP (stem only)
        0x003C,  // ..........####   GAP (stem only)
        0x3FFC,  // ..############   belly top  ┐
        0x7FFC,  // .#############              ┘
        0xF03C,  // ####......####   counter opens
        0xE03C,  // ###........###   counter
        0xE03C,  // ###........###   counter
        0xE03C,  // ###........###   counter
        0xF03C,  // ####......####   counter closes
        0x7FFC,  // .#############   belly bot  ┐
        0x3FFC,  // ..############              ┘
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 'b': horizontal mirror of 'd'. Stem on the LEFT (cols 0..3),
    // bowl on the right with 2-step chamfer on top-right and
    // bottom-right corners. Same bowl geometry as 'd', so the two
    // letters form a clean mirrored pair. Counter is ~7 cols × 8 rows.
    ['b' - 'a'] = { 14, {
        0xF000,  // ####..........   ascender  ┐
        0xF000,  // ####..........             │
        0xF000,  // ####..........             │ (stem only)
        0xF000,  // ####..........             │
        0xF000,  // ####..........             ┘
        0xFFF0,  // ############..   bowl top  ┐
        0xFFF8,  // #############.             ┘ (2-step chamfer)
        0xF03C,  // ####......####   counter opens
        0xF01C,  // ####.......###   counter  ┐
        0xF01C,  // ####.......###            │
        0xF01C,  // ####.......###            │
        0xF01C,  // ####.......###            │
        0xF01C,  // ####.......###            │
        0xF01C,  // ####.......###            │
        0xF01C,  // ####.......###            │
        0xF01C,  // ####.......###            ┘
        0xF03C,  // ####......####   counter closes
        0xFFF8,  // #############.   bowl bot  ┐
        0xFFF0,  // ############..             ┘ (2-step chamfer)
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 'c': like 'e' without the crossbar. 2-step chamfer top + bottom,
    // 3-col walls on both sides (cols 0..2 left, 11..13 right), and a
    // 4-row opening on the right (rows 10..13) where only the left
    // wall remains. Same chamfer geometry as 'e' for family coherence.
    ['c' - 'a'] = { 14, {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x3FF0,  // ..##########..   top chamfer 2-step
        0x7FF8,  // .############.   top chamfer 1-step
        0xF03C,  // ####......####   transition
        0xE01C,  // ###........###   top wall  ┐
        0xE01C,  // ###........###             ┘ (bowl closes top)
        0xE000,  // ###...........   OPENING  ┐
        0xE000,  // ###...........            │
        0xE000,  // ###...........            │ (left wall only)
        0xE000,  // ###...........            ┘
        0xE01C,  // ###........###   bottom wall  ┐
        0xE01C,  // ###........###                ┘ (bowl closes bot)
        0xF03C,  // ####......####   transition
        0x7FF8,  // .############.   bottom chamfer 1-step
        0x3FF0,  // ..##########..   bottom chamfer 2-step
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 'd': ascender + full-height bowl. Reuses the 'a' belly geometry
    // (2-step chamfer on top-left and bottom-left, flat right edge
    // against the stem at cols 10..13) but the bowl fills the entire
    // x-height (rows 5..18) since there's no top bar or gap. Stem runs
    // continuously from row 0 (top of ascender) to row 18 (baseline).
    // Counter is ~7 cols × 8 rows.
    ['d' - 'a'] = { 14, {
        0x003C,  // ..........####   ascender  ┐
        0x003C,  // ..........####             │
        0x003C,  // ..........####             │ (stem only)
        0x003C,  // ..........####             │
        0x003C,  // ..........####             ┘
        0x3FFC,  // ..############   bowl top  ┐
        0x7FFC,  // .#############             ┘ (2-step chamfer)
        0xF03C,  // ####......####   counter opens
        0xE03C,  // ###........###   counter  ┐
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            ┘
        0xF03C,  // ####......####   counter closes
        0x7FFC,  // .#############   bowl bot  ┐
        0x3FFC,  // ..############             ┘ (2-step chamfer)
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 'e': symmetric closed bowl with a 3-row horizontal crossbar
    // and an opening on the right below the crossbar (the gap
    // that distinguishes 'e' from 'o'). 2-step chamfer on all
    // four corners, matching the bowl-family weight. 3-col walls
    // on both sides, 8-col counter.
    ['e' - 'a'] = { 14, {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x3FF0,  // ..##########..   top chamfer  ┐
        0x7FF8,  // .############.                ┘ (2-step)
        0xF03C,  // ####......####   transition
        0xE01C,  // ###........###   wall  ┐
        0xE01C,  // ###........###         ┘
        0xFFFC,  // ##############   crossbar  ┐
        0xFFFC,  // ##############             ┘ (2 rows)
        0xE000,  // ###...........   OPENING  ┐
        0xE000,  // ###...........            ┘ (2 rows, bigger gap)
        0xE01C,  // ###........###   wall  ┐
        0xE01C,  // ###........###         ┘
        0xF03C,  // ####......####   transition
        0x7FF8,  // .############.   bottom chamfer  ┐
        0x3FF0,  // ..##########..                   ┘ (2-step)
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 'g': single-story (Inter Bold style). Same bowl as 'd'/'q'
    // (rows 5..18, 2-step chamfer, ~7 cols × 8 rows counter), then
    // an L-shaped descender (rows 19..23): 3 rows of straight stem
    // continuing from the bowl, then a 2-row full-width foot with
    // sharp 90° corner — no chamfers, just a solid rectangular block.
    ['g' - 'a'] = { 14, {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x3FFC,  // ..############   bowl top  ┐
        0x7FFC,  // .#############             ┘ (2-step chamfer)
        0xF03C,  // ####......####   counter opens
        0xE03C,  // ###........###   counter  ┐
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            ┘
        0xF03C,  // ####......####   counter closes
        0x7FFC,  // .#############   bowl bot  ┐
        0x3FFC,  // ..############             ┘ (2-step chamfer)
        0x003C,  // ..........####   descender stem  ┐
        0x003C,  // ..........####                   │
        0x003C,  // ..........####                   ┘ (3 rows)
        0xFFFC,  // ##############   L-foot  ┐
        0xFFFC,  // ##############          ┘ (2-row block)
    }},
    // 'i': 3-row tittle (rows 1..3) + 2-row gap + 13-row stem
    // (rows 6..18). Width 4 to match the bowl-family stroke weight.
    ['i' - 'a'] = {  4, {
        0x0000, 0xF000, 0xF000, 0xF000, 0x0000,
        0x0000, 0xF000, 0xF000, 0xF000, 0xF000,
        0xF000, 0xF000, 0xF000, 0xF000, 0xF000,
        0xF000, 0xF000, 0xF000, 0xF000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 'j': 3-row tittle at the top (cols 4..7, aligned with stem),
    // 2-row gap, then stem at cols 4..7 from row 6 down past the
    // baseline (row 18) into the descender. Hook in rows 21..23
    // curls left and tapers from the right — same shape language as
    // 'g'-hook but mirrored to point left.
    ['j' - 'a'] = {  8, {
        0x0000, 0x0F00, 0x0F00, 0x0F00, 0x0000,
        0x0000, 0x0F00, 0x0F00, 0x0F00, 0x0F00,
        0x0F00, 0x0F00, 0x0F00, 0x0F00, 0x0F00,
        0x0F00, 0x0F00, 0x0F00, 0x0F00, 0x0F00,
        0x0F00, 0xFF00, 0xFE00, 0xFC00,
    }},
    // 'k': 4-col ascender stem on the left (cols 0..3, full height
    // including ascender), with two 4-col diagonal arms on the right.
    // Upper arm: starts at cols 10..13 (row 5), shifts left 1 col per
    // row, touches the stem at cols 4..7 (row 11). Lower arm mirrors:
    // starts at cols 4..7 (row 12), shifts right 1 col per row, ends
    // at cols 10..13 (row 18). The arms touch the stem for 2 rows
    // (11-12) creating a visible thickening at the meeting point.
    ['k' - 'a'] = { 14, {
        0xF000, 0xF000, 0xF000, 0xF000, 0xF000,
        0xF03C,  // ####......####   upper arm  ┐
        0xF078,  // ####.....####.              │
        0xF0F0,  // ####....####..              │
        0xF1E0,  // ####...####...              │ shifts left
        0xF3C0,  // ####..####....              │  1 col per row
        0xF780,  // ####.####.....              │
        0xFF00,  // ########......              ┘ meets stem
        0xFF00,  // ########......   meeting (2 rows)
        0xF780,  // ####.####.....   lower arm  ┐
        0xF3C0,  // ####..####....              │
        0xF1E0,  // ####...####...              │ shifts right
        0xF0F0,  // ####....####..              │  1 col per row
        0xF078,  // ####.....####.              │
        0xF03C,  // ####......####              ┘ ends at baseline
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 'l': clean 4-col stem matching the bowl-family stroke weight,
    // spanning the full ascender + x-height (rows 0..18). No chamfer,
    // no foot.
    ['l' - 'a'] = {  4, {
        0xF000, 0xF000, 0xF000, 0xF000, 0xF000,
        0xF000, 0xF000, 0xF000, 0xF000, 0xF000,
        0xF000, 0xF000, 0xF000, 0xF000, 0xF000,
        0xF000, 0xF000, 0xF000, 0xF000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 'm': three 4-col stems (cols 0..3, 6..9, 12..15) joined at the
    // top by arches with 2-step chamfer on the outer corners, full
    // transition row, then 11 rows of stems with 2-col counters
    // (cols 4..5, 10..11) open at the bottom. Width 16 — the widest
    // letter in the font, typographically correct for 'm'.
    ['m' - 'a'] = { 16, {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x3FFC,  // ..############..   arches top  ┐
        0x7FFE,  // .##############.               ┘ (2-step chamfer)
        0xFFFF,  // ################   transition (full)
        0xF3CF,  // ####..####..####   three stems  ┐
        0xF3CF,  // ####..####..####                │
        0xF3CF,  // ####..####..####                │
        0xF3CF,  // ####..####..####                │
        0xF3CF,  // ####..####..####                │
        0xF3CF,  // ####..####..####                │ + 2 counters
        0xF3CF,  // ####..####..####                │   open at bottom
        0xF3CF,  // ####..####..####                │
        0xF3CF,  // ####..####..####                │
        0xF3CF,  // ####..####..####                │
        0xF3CF,  // ####..####..####                ┘
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 'n': vertical mirror of 'u'. Same 4-col stems at cols 0..3
    // and 10..13, but the arch is at the top (closed) and the
    // counter opens at the bottom. 2-step chamfer arch top + full
    // connector + 11 rows of stems.
    ['n' - 'a'] = { 14, {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x3FF0,  // ..##########..   arch top  ┐
        0x7FF8,  // .############.             ┘ (2-step chamfer)
        0xFFFC,  // ##############   connector (full)
        0xF03C,  // ####......####   two stems  ┐
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             │ open at bottom
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             ┘
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 'o': symmetric closed bowl. 2-step chamfer on all four corners,
    // 3-col walls (cols 0..2 left, 11..13 right), 8-row × 8-col
    // counter. Matches 'd'/'q'/'g' bowl geometry but symmetric instead
    // of flat-right.
    ['o' - 'a'] = { 14, {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x3FF0,  // ..##########..   top chamfer 2-step
        0x7FF8,  // .############.   top chamfer 1-step
        0xF03C,  // ####......####   transition
        0xE01C,  // ###........###   walls  ┐
        0xE01C,  // ###........###         │
        0xE01C,  // ###........###         │
        0xE01C,  // ###........###         │ (8 rows
        0xE01C,  // ###........###         │   counter)
        0xE01C,  // ###........###         │
        0xE01C,  // ###........###         │
        0xE01C,  // ###........###         ┘
        0xF03C,  // ####......####   transition
        0x7FF8,  // .############.   bottom chamfer 1-step
        0x3FF0,  // ..##########..   bottom chamfer 2-step
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 'q': vertical mirror of 'd'. Same bowl geometry (2-step chamfer
    // on top-left and bottom-left, flat right edge against the stem),
    // but the stem extends BELOW the baseline as a 5-row descender
    // instead of above as an ascender. Counter is ~7 cols × 8 rows.
    ['q' - 'a'] = { 14, {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x3FFC,  // ..############   bowl top  ┐
        0x7FFC,  // .#############             ┘ (2-step chamfer)
        0xF03C,  // ####......####   counter opens
        0xE03C,  // ###........###   counter  ┐
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            │
        0xE03C,  // ###........###            ┘
        0xF03C,  // ####......####   counter closes
        0x7FFC,  // .#############   bowl bot  ┐
        0x3FFC,  // ..############             ┘ (2-step chamfer)
        0x003C,  // ..........####   descender  ┐
        0x003C,  // ..........####              │
        0x003C,  // ..........####              │ (stem only)
        0x003C,  // ..........####              │
        0x003C,  // ..........####              ┘
    }},
    // 'r': 4-col stem (cols 0..3, matching bowl-family) with a small
    // shoulder extending right at the top. Row 5 has a notch at cols
    // 2..3 (stem peak at cols 0..1, shoulder peak at cols 4..9, small
    // valley between). Row 6 merges them into a full row, then 2-step
    // chamfer at bottom-right (rows 7..8) drops the shoulder down to
    // the stem.
    ['r' - 'a'] = { 10, {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0xCFC0,  // ##..######   notch at cols 2-3
        0xFFC0,  // ##########   full (stem + shoulder merge)
        0xFF80,  // #########.   1-step chamfer bottom-right
        0xFF00,  // ########..   2-step chamfer bottom-right
        0xF000,  // ####......   stem only  ┐
        0xF000,  // ####......              │
        0xF000,  // ####......              │
        0xF000,  // ####......              │
        0xF000,  // ####......              │
        0xF000,  // ####......              │
        0xF000,  // ####......              │
        0xF000,  // ####......              │
        0xF000,  // ####......              │
        0xF000,  // ####......              ┘
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 's': two stacked chamfered half-bowls connected by a diagonal
    // middle bar (the S-curve). Top half is closed at the top and
    // opens to the right below (left wall descends); bottom half
    // opens to the left above (right wall comes down) and closes
    // at the bottom. The S-bar shifts from cols 0..9 at row 11 to
    // cols 4..13 at row 12, creating the diagonal sweep. Same 2-step
    // chamfer as 'e' for family coherence.
    ['s' - 'a'] = { 14, {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x3FF0,  // ..##########..   top chamfer 2-step
        0x7FF8,  // .############.   top chamfer 1-step
        0xF03C,  // ####......####   top transition (4-col walls)
        0xE000,  // ###...........   left wall  ┐
        0xE000,  // ###...........             │ (top half
        0xF000,  // ####..........             ┘  opens right)
        0xFFC0,  // ##########....   S-bar top (cols 0..9)
        0x0FFC,  // ....##########   S-bar bot (cols 4..13)
        0x003C,  // ..........####   right wall  ┐
        0x001C,  // ...........###              │ (bottom half
        0x001C,  // ...........###              ┘  opens left)
        0xF03C,  // ####......####   bottom transition
        0x7FF8,  // .############.   bottom chamfer 1-step
        0x3FF0,  // ..##########..   bottom chamfer 2-step
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 't': 4-col stem at cols 1..4, full-width 3-row crossbar at
    // rows 5..7 (top of x-height), 3-row foot at rows 16..18 that
    // matches the crossbar's right edge (col 7) with a chamfered
    // baseline for a rounded toe. Stem shifted 1 col left of center
    // so the right-extending foot balances the letter visually.
    ['t' - 'a'] = {  8, {
        0x0000, 0x7800, 0x7800, 0x7800, 0x7800,
        0xFF00, 0xFF00, 0xFF00, 0x7800, 0x7800,
        0x7800, 0x7800, 0x7800, 0x7800, 0x7800,
        0x7800, 0x7F00, 0x7F00, 0x7E00,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 'u': inverted bowl. Two 4-col stems open at the top (cols 0..3
    // and 10..13, matching the bowl-family), connected at the bottom
    // by a 3-row symmetric bowl curve: full-width connector at row
    // 16, then 2-step chamfer (1-step at row 17, 2-step at row 18)
    // mirroring the 'a' belly bottom but on both sides.
    ['u' - 'a'] = { 14, {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0xF03C,  // ####......####   two stems  ┐
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             │ open at top
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             │
        0xF03C,  // ####......####             ┘
        0xFFFC,  // ##############   bowl connector (full)
        0x7FF8,  // .############.   bowl bottom  ┐
        0x3FF0,  // ..##########..                ┘ (2-step chamfer,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    //  symmetric)
    }},
    // 'w': inverse of 'm'. Three 4-col stems open at the TOP (cols
    // 0..3, 6..9, 12..15, same positions as 'm') with 2-col counters
    // at cols 4..5 and 10..11. At the bottom, V-tips narrow inward
    // by 1 col each (row 15), then close fully (row 16), then the
    // standard 2-step outer chamfer (rows 17..18). Width 16.
    ['w' - 'a'] = { 16, {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0xF3CF,  // ####..####..####   three stems  ┐
        0xF3CF,  // ####..####..####                │
        0xF3CF,  // ####..####..####                │
        0xF3CF,  // ####..####..####                │
        0xF3CF,  // ####..####..####                │
        0xF3CF,  // ####..####..####                │ + 2 counters
        0xF3CF,  // ####..####..####                │   open at top
        0xF3CF,  // ####..####..####                │
        0xF3CF,  // ####..####..####                │
        0xF3CF,  // ####..####..####                ┘
        0xFBDF,  // #####.####.#####   V-tips narrow inward
        0xFFFF,  // ################   V-tips closed (full)
        0x7FFE,  // .##############.   outer chamfer  ┐
        0x3FFC,  // ..############..                  ┘ (2-step)
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 'x': two 3-col-thick diagonal strokes crossing at the center,
    // symmetric about both axes. Corners (rows 5-6 and 17-18) are
    // double-thick to keep them visually weighted like a bold sans
    // serif x. Strokes converge to a 4-col-wide pinch point at the
    // center crossing (rows 11-12).
    ['x' - 'a'] = { 14, {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0xE01C,  // ###........###   top-left & top-right corners ┐
        0xE01C,  // ###........###                                ┘
        0x7038,  // .###......###.
        0x3870,  // ..###....###..
        0x1CE0,  // ...###..###...
        0x0FC0,  // ....######....
        0x0780,  // .....####.....   center crossing ┐
        0x0780,  // .....####.....                   ┘
        0x0FC0,  // ....######....
        0x1CE0,  // ...###..###...
        0x3870,  // ..###....###..
        0x7038,  // .###......###.
        0xE01C,  // ###........###   bottom-left & bottom-right    ┐
        0xE01C,  // ###........###    corners                       ┘
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    }},
    // 'y': two 4-col arms at the top (parallel for 5 rows, then 4 rows
    // of diagonal convergence shifting 1 col inward each side per row)
    // merging into a single 4-col stem (cols 5..8) at row 14. The
    // single stem runs straight down through baseline into descender,
    // ending in a 2-row foot that extends LEFT from the stem (cols
    // 0..8 with slight taper) like the reference image.
    ['y' - 'a'] = { 14, {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0xF03C,  // ####......####   parallel arms  ┐
        0xF03C,  // ####......####                  │
        0xF03C,  // ####......####                  │
        0xF03C,  // ####......####                  │
        0xF03C,  // ####......####                  ┘
        0x7878,  // .####....####.   V convergence  ┐
        0x3CF0,  // ..####..####..                  │
        0x1FE0,  // ...########...                  │
        0x0FC0,  // ....######....                  ┘
        0x0780,  // .....####.....   single stem  ┐
        0x0780,  // .....####.....                │
        0x0780,  // .....####.....                │
        0x0780,  // .....####.....                │ x-height
        0x0780,  // .....####.....                ┘
        0x0780,  // .....####.....   descender   ┐
        0x0780,  // .....####.....               │
        0x0780,  // .....####.....               ┘
        0xFF80,  // #########.....   foot extends left
        0xFE00,  // #######.......   foot tapers right
    }},
};

// --- Rendering -------------------------------------------------------------
// Bitmap is rotated 90° counter-clockwise as it's drawn: natural row →
// display x, natural col → inverted display y (so the letter's "top"
// points toward decreasing display x, which is the OLED's left edge
// after ROTATION_270).
//
// Baseline alignment: bitmap row CORNE_BASELINE maps to a fixed display
// x position, so x-height letters, ascenders, and descenders share a
// common baseline. CORNE_X_OFF positions bitmap row 0 at display x = 5,
// so descender bottom (row 23) lands at display x = 28 — within the
// 32-px display-x span.
//
// Layout: each letter occupies its own `width` pixels of display y, and
// adjacent letters are separated by exactly CORNE_LETTER_SPACING empty
// pixels. The whole word is centered on the 128-px display. This keeps
// inter-letter gaps constant regardless of which letters are stacked
// (a fixed-cell layout creates uneven gaps when widths vary).

#define CORNE_X_OFF             5  // bitmap row 0 → display x = 5
#define CORNE_LETTER_SPACING    6  // empty pixels between adjacent letters

// Render a single letter with its topmost display-y at `top_dy`. The
// letter spans [top_dy - width + 1, top_dy] on display y.
static void render_corne_letter(char ch, uint8_t top_dy) {
    if (ch < 'a' || ch > 'z') return;
    uint8_t idx   = ch - 'a';
    uint8_t width = pgm_read_byte(&corne_font[idx].width);
    if (width == 0) return;

    for (uint8_t row = 0; row < CORNE_BITMAP_H; row++) {
        uint16_t bits = pgm_read_word(&corne_font[idx].rows[row]);
        if (bits == 0) continue;  // skip blank rows for speed
        uint8_t dx = CORNE_X_OFF + row;
        for (uint8_t col = 0; col < width; col++) {
            bool on = (bits >> (15 - col)) & 1;
            oled_write_pixel(dx, top_dy - col, on);
        }
    }
}

// Render a string of N letters stacked vertically. First letter at high
// dy (near user when reading head-tilted-left), last letter at low dy.
// Each letter takes exactly its own width; adjacent letters are
// separated by CORNE_LETTER_SPACING empty pixels. Chars outside 'a'..'z'
// (or any width-0 glyph) are skipped — they don't take space.
static void render_corne_word(const char *word, uint8_t n) {
    // First pass: sum widths of renderable letters
    uint16_t letters_width = 0;
    uint8_t  letter_count  = 0;
    for (uint8_t i = 0; i < n; i++) {
        if (word[i] < 'a' || word[i] > 'z') continue;
        uint8_t w = pgm_read_byte(&corne_font[word[i] - 'a'].width);
        if (w == 0) continue;
        letters_width += w;
        letter_count++;
    }
    if (letter_count == 0) return;

    uint16_t total = letters_width;
    if (letter_count > 1) total += (letter_count - 1) * CORNE_LETTER_SPACING;

    uint8_t margin = (128 - total) / 2;
    int16_t cursor = 127 - margin;   // top dy of first letter

    bool first = true;
    for (uint8_t i = 0; i < n; i++) {
        if (word[i] < 'a' || word[i] > 'z') continue;
        uint8_t w = pgm_read_byte(&corne_font[word[i] - 'a'].width);
        if (w == 0) continue;

        if (!first) cursor -= CORNE_LETTER_SPACING;
        first = false;

        render_corne_letter(word[i], (uint8_t)cursor);
        cursor -= w;
    }
}

// 7-char lowercase layer names. Pad shorter names with trailing space so
// the stack stays 7 cells tall and looks consistent across layers.
static const char PROGMEM layer_qwerty[]  = "qwerty ";
static const char PROGMEM layer_colemak[] = "colemak";
static const char PROGMEM layer_symbols[] = "symbols";
static const char PROGMEM layer_numbers[] = "nums   ";
static const char PROGMEM layer_system[]  = "system ";
static const char PROGMEM layer_magnet[]  = "magnet ";
static const char PROGMEM layer_unknown[] = "       ";

static const char * const PROGMEM layer_names[] = {
    layer_qwerty, layer_colemak, layer_symbols,
    layer_numbers, layer_system, layer_magnet,
};
#define LAYER_NAME_COUNT (sizeof(layer_names) / sizeof(layer_names[0]))
#define LAYER_NAME_LEN   7

static void render_layer_name(uint8_t layer) {
    const char *src = (layer < LAYER_NAME_COUNT)
        ? (const char *)pgm_read_ptr(&layer_names[layer])
        : layer_unknown;
    char buf[LAYER_NAME_LEN];
    for (uint8_t i = 0; i < LAYER_NAME_LEN; i++) {
        buf[i] = pgm_read_byte(&src[i]);
    }
    render_corne_word(buf, LAYER_NAME_LEN);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Re-render only on layer change.
        static uint8_t last_layer = 0xFF;
        uint8_t layer = get_highest_layer(layer_state | default_layer_state);
        if (layer != last_layer) {
            oled_clear();
            render_layer_name(layer);
            last_layer = layer;
        }
    } else {
        // Slave: DEBUG view. DEBUG_STRING controls what's rendered:
        //   - Single char  (e.g. "x")    → 7 copies stacked. Use when
        //                                   focused on one glyph; 7
        //                                   matches the RHS layout so
        //                                   the letter is evaluated in
        //                                   context.
        //   - Multi-char (e.g. "alexi") → render the string as-is.
        //                                   Use to verify letters read
        //                                   correctly together.
        #define DEBUG_STRING "alexi"
        #define DEBUG_LEN    (sizeof(DEBUG_STRING) - 1)
        static bool rendered = false;
        if (!rendered) {
            oled_clear();
            if (DEBUG_LEN == 1) {
                char buf[7] = {
                    DEBUG_STRING[0], DEBUG_STRING[0], DEBUG_STRING[0],
                    DEBUG_STRING[0], DEBUG_STRING[0], DEBUG_STRING[0],
                    DEBUG_STRING[0],
                };
                render_corne_word(buf, 7);
            } else {
                render_corne_word(DEBUG_STRING, DEBUG_LEN);
            }
            rendered = true;
        }
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_RST:
            if (record->event.pressed) {
                eeconfig_update_rgb_matrix_default();
                rgb_matrix_enable();
            }
            break;
        case UGH_DN:
            if (record->event.pressed) {
                // Underglow hue is stored in rgb_matrix_config.speed so the
                // split transport syncs it to the slave half automatically.
                rgb_matrix_set_speed(rgb_matrix_get_speed() - LP_UG_HUE_STEP);
            }
            break;
        case UGH_UP:
            if (record->event.pressed) {
                rgb_matrix_set_speed(rgb_matrix_get_speed() + LP_UG_HUE_STEP);
            }
            break;
        case MAG_HL:
        case MAG_HR:
        case MAG_UP:
        case MAG_DOWN:
        case MAG_TL:
        case MAG_TR:
        case MAG_BL:
        case MAG_BR:
        case MAG_L13:
        case MAG_L23:
        case MAG_C3:
        case MAG_R23:
        case MAG_R13:
        case MAG_ND:
        case MAG_PD:
        case MAG_MAX:
        case MAG_C:
        case MAG_RST:
            if(record->event.pressed) {
                mag(keycode);
            }
            break;
        case ONEPSAF:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_RALT) SS_TAP(X_BSLS) SS_DELAY(100) SS_UP(X_RALT) SS_UP(X_LGUI));
            }

    }
    return true;
}
