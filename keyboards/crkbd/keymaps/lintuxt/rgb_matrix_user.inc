/* @lintuxt - custom RGB Matrix effect: American flag.
 *
 *   LINTUXT_AMERICAN  - Two American flags, one per split half, mirrored
 *                      so each flag's canton sits on its OUTER edge.
 *                      Blue canton + 5 red/dim-white stripes per flag,
 *                      with a 2D wind-ripple wave; transitions anti-
 *                      aliased over LP_FL_BLEND_BAND.
 *
 * RM_NEXT is bound on layer 4 but the cycle is a single-effect no-op.
 *
 * Live controls (persist via QMK's rgb_matrix_config sync + EEPROM):
 *   - RM_HUED / RM_HUEU  -> no-op (palette is baked to preserve flag identity)
 *   - RM_SATD / RM_SATU  -> no-op (same reason)
 *   - RM_VALD / RM_VALU  -> brightness ceiling
 *   - UGH_DN  / UGH_UP   -> underglow hue (stored in rgb_matrix_config.speed,
 *                          which is part of the split-sync transport so both
 *                          halves stay in lockstep)
 * Defaults from RGB_MATRIX_DEFAULT_HUE / _SAT / _SPD in config.h.
 * RGB_RST resets everything.
 *
 * Right-half hardware note: the underglow ring is mostly bypassed. Only U5
 * (g_led_config 31) and U6 (g_led_config 32) are live in the chain; U2, U3,
 * U4 are dead. U1 is alive but wired in parallel with the bypass jumper, so
 * it shows whatever color the chain's first slot receives — a phantom of the
 * U5 LED that the firmware can't drive independently.
 *
 * Effect: a +4 chain shift on the right half. Firmware (chain) index i in
 * 27-49 drives the LED that g_led_config describes at index i+4. Firmware
 * indices 50-53 fall off the end of the shortened right chain. lp_real_index()
 * applies the +4 shift.
 */

RGB_MATRIX_EFFECT(LINTUXT_AMERICAN)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// --- Tunables ---------------------------------------------------------------
// Per-key hue and saturation come live from rgb_matrix_config (see header).
// Underglow saturation and brightness are fixed here.
#define LP_UG_SAT          255   // underglow saturation (fully saturated)
#define LP_UG_VAL           80   // underglow brightness

// Flag wave.
// The wave displaces each LED by an ellipse over time:
//   y_off = AMP_Y * sin(x * FREQ_X + t)
//   x_off = AMP_X * sin(y * FREQ_Y + t + 64)     // 64 = 90° phase offset
// The 90° offset makes LEDs orbit small ellipses (fabric-like) rather
// than tracking a single diagonal axis.
#define LP_FL_TIME_STEP     16   // per-frame time advance (~4 s per full cycle).
#define LP_FL_WAVE_AMP_Y    10   // peak vertical displacement, board units
                                 // (board height ~64; stripes ~13 each).
#define LP_FL_WAVE_AMP_X    12   // peak horizontal displacement, board units
                                 // (~21% of the 56-unit canton width). Raised
                                 // from 8 so col 3 of the canton (local_x≈36,
                                 // i.e. L1/L2/L3) sees a strong cross-fade
                                 // over the LP_US_CANTON_X=38 right edge.
#define LP_FL_WAVE_FREQ_X    2   // y-wave's spatial freq along x.
                                 // wavelength ≈ 256/2 = 128 board units.
#define LP_FL_WAVE_FREQ_Y    4   // x-wave's spatial freq along y.
                                 // 256/4 = 64 ≈ board height → one full
                                 // wavelength fits vertically, so top and
                                 // bottom flap in opposite directions.
#define LP_FL_POLE_DAMP    144   // 0..256: amplitude scale at each flag's
                                 // implied flagpole (local_x = 0, the OUTER
                                 // edge of each half). Ramps linearly up
                                 // to ~240 (~94%) at the theoretical inner
                                 // edge (local_x = 112); the real hardware
                                 // maximum local_x is ~95 (Corne has a gap
                                 // around led_x ≈ 96..128), so the actual
                                 // peak is ~223 (~87%). Pins each canton
                                 // so it reads as a fixed "stars" panel
                                 // while the trailing stripes whip toward
                                 // the center gap.
                                 //   256 = no damping (cantons ripple fully)
                                 //   128 ≈ cantons at ~50% amplitude (subtle)
                                 //    64 ≈ cantons barely move
                                 //     0 = cantons pinned dead at the corners
#define LP_FL_BLEND_BAND   256   // Q7 board units (= 2 board units). Width of
                                 // the soft transition zone at stripe and
                                 // canton boundaries. Smaller = crisper edges,
                                 // larger = more cross-fade. Must be a power
                                 // of 2 AND <= 256 — the canton-edge shortcut
                                 // `(uint8_t)(128 + dx)` below assumes
                                 // blend_half_q <= 128.

// Resolve a firmware LED index to the g_led_config entry that physically
// describes it. The right half is shifted by +4 (see file header).
static uint8_t lp_real_index(uint8_t i) {
    return (i >= 27) ? (uint8_t)(i + 4) : i;
}

// Handle the dead-tail and underglow branches. Returns true if the LED was
// rendered here (the caller's per-key path should skip).
static bool lp_render_shell(uint8_t i, uint8_t real) {
    if (real >= RGB_MATRIX_LED_COUNT) {
        rgb_matrix_set_color(i, 0, 0, 0);
        return true;
    }
    if (g_led_config.flags[real] & LED_FLAG_UNDERGLOW) {
        rgb_t ug = rgb_matrix_hsv_to_rgb((hsv_t){rgb_matrix_config.speed, LP_UG_SAT, LP_UG_VAL});
        rgb_matrix_set_color(i, ug.r, ug.g, ug.b);
        return true;
    }
    return false;
}

// Small RGB color carrier used by the flag effect below.
typedef struct { uint8_t r, g, b; } lp_rgb_t;

static lp_rgb_t lp_from_hsv(uint8_t h, uint8_t s, uint8_t v) {
    rgb_t c = rgb_matrix_hsv_to_rgb((hsv_t){h, s, v});
    return (lp_rgb_t){c.r, c.g, c.b};
}

// --- LINTUXT_AMERICAN ------------------------------------------------------
// Two flags, one per split half, mirrored so each flag's canton/pole sits
// on the OUTER edge of its half (LHS pole at led_x=0, RHS pole at led_x=224).
// Each flag is a blue canton in its outer top corner + 5 red/dim-white
// horizontal stripes, with a 2D "wind ripple" wave: each LED's effective
// (x, y) is displaced by a pair of sin waves with a 90° phase offset, so
// each LED traces a small ellipse over time and the stripes undulate as
// if a breeze were crossing the fabric. Both flags share time and
// local_x, so they ripple in sync; their physical wave directions
// mirror each other (LHS waves run leftward, RHS waves run rightward —
// like a wind blowing outward from the center gap).
//
// Layout (per-LED): local_x = (led_x < 112) ? led_x : 224 - led_x. All
// x-dependent math (canton boundary, pole damp, y-wave spatial phase,
// static_x) uses local_x; led_x only picks the half. led_y is shared.
//
// All boundary checks (stripe red↔dim-white transitions, canton right/
// bottom edges) are anti-aliased: math runs in Q7 fixed point (board
// units × 128) so the wave's sub-pixel motion drives smooth cross-fades
// over LP_FL_BLEND_BAND board units instead of snapping in single frames.
// The canton's TOP edge stays sharp on purpose (it's the implied "top
// of the flag" and no LEDs render above y=0 anyway).
//
// "White" stripes are intentionally dim (LP_US_WHITE_LUMA, default 96 /
// 256 ≈ 38% linear). At pure-white (v,v,v) the stripes are perceptually
// 3× brighter than the red stripes and burn the eyes at night. With the
// luma cap, the white reads as a soft gray-pink that balances better
// against the red and blue.
//
// Wave amplitude is damped near each flag's pole (LP_FL_POLE_DAMP,
// default 128 / 256). At local_x = 0 (the outer edge of each half, the
// pole) the wave runs at ~50% amplitude, ramping linearly to ~90% at
// the inner edge (continuous ratio 93.75%; integer truncation in the
// amp_x/amp_y multiply drops it to 9/10 = 90%). The innermost 2×2 of
// each canton (LP_US_CANTON_FIXED_X/Y) is hard-pinned at damp = 0 — a
// rock-solid corner anchor; the outer L-shaped ring of the 3×3 canton
// still wobbles with the ramp, and the trailing stripes flap toward
// the center gap.
//
// Board coords from g_led_config (Corne): per-key LEDs span roughly
// x ∈ [0, 224], y ∈ [0, 64]. Canton 38 × 45 per half ≈ 3 cols × 3 rows
// (top + home + bottom alphabetic rows). The right edge sits 2 units past
// col 3 (x=36) and the bottom edge 3 units past row 3 (y=42) — close
// enough that the wave's swing pushes the L-ring LEDs well across the
// canton boundary, so they visibly cross-fade between blue and stripe
// color as the flag waves. Earlier values (45 × 53 then 40 × 45) left
// col 3 either fully inside or only barely straddling — L2 (home-inner)
// and L3 (bot-inner) barely wobbled. With LP_FL_WAVE_AMP_X=12 and
// LP_FL_POLE_DAMP=144, col-3 LEDs see ~±8 board units of x swing at
// local_x=36, fully crossing the 38 edge. The inner 2×2 of each canton
// (LP_US_CANTON_FIXED_X/Y) is still hard-pinned — those 4 LEDs nearest
// the pole never move. Stripes have period 64; odd count puts red at
// top and bottom like the real US flag.
#define LP_US_CANTON_X         38   // total canton width per half (3 cols);
                                    // edge sits 2 units past col 3 (x=36),
                                    // so the col-3 L-ring (E/D/C on LHS,
                                    // I/K/, on RHS) straddles the boundary
                                    // for most of the wave swing. Earlier
                                    // value (40) left col 3 mostly inside
                                    // and L2/L3 barely wobbled.
#define LP_US_CANTON_Y         45   // total canton height (3 rows); edge
                                    // sits 3 units past row 3 (y=42), in
                                    // the gap before thumbs at y ≈ 55.
#define LP_US_CANTON_FIXED_X   30   // inner pinned-canton width (2 cols);
                                    // LEDs with local_x < this AND led_y <
                                    // LP_US_CANTON_FIXED_Y skip the wave
                                    // entirely (damp = 0). Boundary sits in
                                    // the gap between cols 2 (x=18) and 3
                                    // (x=36), so no LED straddles it.
#define LP_US_CANTON_FIXED_Y   32   // inner pinned-canton height (2 rows);
                                    // covers top + home row, ends before
                                    // the bottom row at y ≈ 34.
#define LP_US_WHITE_LUMA    96   // 0..256: white-stripe brightness as a
                                 // fraction of v. 256 = pure white (R=G=B=v).
                                 // 96 ≈ 38% linear (~60% perceptual on
                                 // gamma-curve LEDs) — noticeably dim,
                                 // easy on the eyes at night. Drop further
                                 // (64, 48) if still too hot. Red and blue
                                 // are unaffected.

bool LINTUXT_AMERICAN(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t time = scale16by8(g_rgb_timer, LP_FL_TIME_STEP);
    uint8_t v    = rgb_matrix_config.hsv.v;

    // Fixed palette — RM_HUE/RM_SAT have no effect. RM_VAL still controls
    // overall brightness via .hsv.v above; LP_US_WHITE_LUMA caps the
    // "white" stripes separately (default ~38% of v) so they don't burn
    // the eyes at night.
    //
    //   red stripe:        (v, 0, 0)
    //   dim-white stripe:  (k, k, k)   where k = v * LP_US_WHITE_LUMA / 256
    //   blue canton:       lp_from_hsv(170, 255, v)         (unaffected)
    lp_rgb_t      blue = lp_from_hsv(170, 255, v);
    const uint8_t k    = (uint8_t)(((uint16_t)v * LP_US_WHITE_LUMA) >> 8);

    // Pre-compute canton edges in Q7 (board units * 128) for the
    // anti-aliased boundary math.
    const int16_t  canton_x_edge_q = (int16_t)LP_US_CANTON_X << 7;
    const int16_t  canton_y_edge_q = (int16_t)LP_US_CANTON_Y << 7;
    const int16_t  blend_half_q    = LP_FL_BLEND_BAND >> 1;

    // Anti-alias band in stretched stripe-space (where each stripe = 8192).
    const uint16_t band_stretched  = LP_FL_BLEND_BAND * 5;       // 1280
    const uint16_t band_half_s     = band_stretched >> 1;        // 640
    const uint16_t trail_start     = (uint16_t)8192 - band_half_s;

    for (uint8_t i = led_min; i < led_max; i++) {
        uint8_t real = lp_real_index(i);
        if (lp_render_shell(i, real)) continue;

        uint8_t led_x = g_led_config.point[real].x;
        uint8_t led_y = g_led_config.point[real].y;

        // Two-flag layout: each half is a full flag mirrored so the
        // canton/pole sits on the OUTER edge. local_x is the within-half
        // x position: 0 at the outer edge (pole), ~112 at the inner edge
        // (near the gap, trailing stripes). led_x only picks the half;
        // everything x-dependent below uses local_x. The 112 split is the
        // midpoint of the board's [0, 224] x-range — no LED actually sits
        // at led_x = 112 on Corne (~96..128 is the inter-half gap), so
        // the strict-less-than is safe either way.
        uint8_t local_x = (led_x < 112) ? led_x : (uint8_t)(224 - led_x);

        // Pole damping: amplitude scales linearly from LP_FL_POLE_DAMP/256
        // at local_x = 0 (pole) to ~256/256 at local_x = 112 (inner edge).
        // The >> 7 (instead of /112) makes the inner edge land at ~94%
        // rather than 100%; imperceptible and saves a runtime division.
        //
        // Exception: the inner 2×2 of each canton (LP_US_CANTON_FIXED_*)
        // is hard-pinned at damp = 0 — zero wave displacement, the corner
        // is a rock-solid stars anchor. The outer L-shaped ring of the
        // 3×3 canton still wobbles with the ramp below.
        uint16_t damp;
        if (local_x < LP_US_CANTON_FIXED_X && led_y < LP_US_CANTON_FIXED_Y) {
            damp = 0;
        } else {
            damp = LP_FL_POLE_DAMP
                 + (((uint16_t)(256 - LP_FL_POLE_DAMP) * local_x) >> 7);
        }
        uint8_t  amp_y = (uint8_t)(((uint16_t)LP_FL_WAVE_AMP_Y * damp) >> 8);
        uint8_t  amp_x = (uint8_t)(((uint16_t)LP_FL_WAVE_AMP_X * damp) >> 8);

        // Wave: each LED displaces by a small ellipse over time (90° phase
        // offset between the x and y waves). Computed in Q7 fixed point
        // (board units * 128) so we keep sub-pixel precision for the
        // anti-aliased boundary checks below. amp_x / amp_y carry the
        // pole-damp factor so each flag pivots on its outer (pole) edge.
        // wphase_x uses led_y (not local_x), so the x-wave is shared across
        // both halves; the spatial mirror in static_x_q below is what makes
        // RHS ripple as a mirror image of LHS.
        //
        // Wavelength note: local_x * LP_FL_WAVE_FREQ_X spans 0..~224 across
        // each half (= ~7/8 of a full sin8 period), so each half shows less
        // than one full wave at a time — intentional; the old single-flag
        // code spanned ~1.75 wavelengths across the full board.
        uint8_t wphase_y   = (uint8_t)(local_x * LP_FL_WAVE_FREQ_X) + time;
        int16_t woff_y_q   = (int8_t)(sin8(wphase_y) - 128) * amp_y;
        int16_t static_y_q = ((int16_t)led_y << 7) - woff_y_q;

        uint8_t wphase_x   = (uint8_t)(led_y * LP_FL_WAVE_FREQ_Y) + time + 64;
        int16_t woff_x_q   = (int8_t)(sin8(wphase_x) - 128) * amp_x;
        int16_t static_x_q = ((int16_t)local_x << 7) - woff_x_q;

        // --- Stripe color (anti-aliased) ---------------------------------
        // Stripes repeat with period 64 board units = 8192 Q7. Stretch by 5
        // so each stripe occupies an even 8192 of the [0, 40960) range:
        // stripe index = y5 >> 13, position-within-stripe = y5 & 8191.
        // C's `%` can be negative for negative operands; add 8192 once and
        // mask, since 8192 is a power of 2.
        uint16_t y_mod_q = (uint16_t)((static_y_q % 8192 + 8192) & 8191);
        uint16_t y5      = y_mod_q * 5;
        uint8_t  stripe  = (uint8_t)(y5 >> 13);          // 0..4 (>> 13 = / 8192, one full stripe in stretched space)
        uint16_t pos_q   = y5 & 8191;                    // 0..8191

        // Stripe targets — each stripe contributes an R target and a GB
        // target. Red stripes (0,2,4): R=v, G=B=0. Dim-white stripes (1,3):
        // R=k, G=B=k. Two parallel lerps blend with the neighbor stripe
        // across LP_FL_BLEND_BAND so transitions cross-fade.

        uint8_t this_r      = (stripe & 1) ? k : v;
        uint8_t this_gb     = (stripe & 1) ? k : 0;
        uint8_t neighbor_r  = this_r;
        uint8_t neighbor_gb = this_gb;
        uint8_t blend       = 0;

        if (pos_q < band_half_s) {
            // Near start of stripe — blending with PREVIOUS stripe.
            // pos_q=0 → blend=128 (50/50), pos_q=band_half_s → blend=0.
            uint8_t prev = (stripe == 0) ? 4 : (stripe - 1);
            neighbor_r  = (prev & 1) ? k : v;
            neighbor_gb = (prev & 1) ? k : 0;
            blend = (uint8_t)(128 - ((uint32_t)pos_q * 128) / band_half_s);
        } else if (pos_q >= trail_start) {
            // Near end of stripe — blending with NEXT stripe.
            // pos_q=trail_start → blend=0, pos_q=8191 → blend=128.
            uint8_t next = (stripe == 4) ? 0 : (stripe + 1);
            neighbor_r  = (next & 1) ? k : v;
            neighbor_gb = (next & 1) ? k : 0;
            blend = (uint8_t)(((uint32_t)(pos_q - trail_start) * 128) / band_half_s);
        }

        // Two-channel lerp (R and GB independently). Safe in uint16:
        // weights (256 - blend) and blend sum to 256, and both operands
        // are ≤ v ≤ 255, so each pre-shift sum is ≤ 255 * 256 = 65280
        // (fits uint16).
        uint8_t r  = (uint8_t)(((uint16_t)this_r  * (256 - blend)
                               + (uint16_t)neighbor_r  * blend) >> 8);
        uint8_t gb = (uint8_t)(((uint16_t)this_gb * (256 - blend)
                               + (uint16_t)neighbor_gb * blend) >> 8);
        lp_rgb_t stripe_c = { r, gb, gb };

        // --- Canton color blend (anti-aliased right + bottom edges) ------
        // canton_a ∈ [0, 255]: 0 = pure stripe, 255 = pure blue.
        // Right edge straddles canton_x_edge_q ± blend_half_q.
        // Bottom edge straddles canton_y_edge_q ± blend_half_q.
        // Top edge (static_y_q < 0) is a hard boundary — sharp.
        int16_t dx_q = canton_x_edge_q - static_x_q;   // >0 inside (left of edge)
        int16_t dy_q = canton_y_edge_q - static_y_q;   // >0 inside (above bottom edge)

        uint8_t a_right, a_bottom;
        if (dx_q <= -blend_half_q)      a_right = 0;
        else if (dx_q >=  blend_half_q) a_right = 255;
        else                            a_right = (uint8_t)(128 + dx_q);  // band=256

        if (static_y_q < 0)             a_bottom = 0;   // top-edge sharp
        else if (dy_q <= -blend_half_q) a_bottom = 0;
        else if (dy_q >=  blend_half_q) a_bottom = 255;
        else                            a_bottom = (uint8_t)(128 + dy_q);

        uint8_t canton_a = (a_right < a_bottom) ? a_right : a_bottom;

        // --- Final color = lerp(stripe_c, blue, canton_a) ----------------
        uint16_t inv = (uint16_t)(256 - canton_a);
        uint8_t  fr  = (uint8_t)(((uint16_t)stripe_c.r * inv + (uint16_t)blue.r * canton_a) >> 8);
        uint8_t  fg  = (uint8_t)(((uint16_t)stripe_c.g * inv + (uint16_t)blue.g * canton_a) >> 8);
        uint8_t  fb  = (uint8_t)(((uint16_t)stripe_c.b * inv + (uint16_t)blue.b * canton_a) >> 8);

        rgb_matrix_set_color(i, fr, fg, fb);
    }
    return rgb_matrix_check_finished_leds(led_max);
}


#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
