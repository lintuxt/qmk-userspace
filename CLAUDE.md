# CLAUDE.md

Project-specific guidance for working in this repo. See `README.md` for general
setup, build, and flash instructions.

## What this repo is

External QMK userspace for the Corne (crkbd rev1) keymap. Builds against an
unmodified upstream QMK at `../qmk` (pinned to 0.32.14). All custom code lives
in `keyboards/crkbd/keymaps/lintuxt/`:

- `keymap.c` — keymap, custom font, RGB matrix, OLED rendering
- `rgb_matrix_user.inc` — custom RGB effects
- `config.h`, `rules.mk` — build config

The right half (RHS) is the master; the left half (LHS) is the slave.

## OLED font: design system

The custom `corne_font` array in `keymap.c` (search `static const corne_letter_t corne_font`)
defines a lowercase-only font drawn pixel-by-pixel on the OLED. The font is
being incrementally redesigned in **Inter / SF Pro Display Bold** style.

### Bitmap format

- Each glyph: `width` (1–16) + 24 rows of `uint16_t`, col 0 in MSB
- x-height letters occupy **rows 5–18** (baseline at row 18)
- Ascender letters (b, d, l) extend into **rows 0–4**
- Descender letters (g, j, q, y) extend into **rows 19–23**
- Rendering rotates the bitmap 90° CCW; bitmap col → display y (inverted),
  bitmap row → display x. So the letter's "top" points to the OLED's left
  edge after `OLED_ROTATION_270`.

### Bowl-family chrome (the redesign convention)

All bowled letters share the same outline geometry, chosen for consistency:

- **Width 14**, stem at **cols 10–13** (right) or **cols 0–3** (left)
- **2-step chamfer** on the rounded corners (was 3-step in the original Corne
  logo; the new design is slightly more square but reads cleaner at 4-col stem
  weight)
- Belly/bowl interior: **3-col walls**, ~7-col counter
- Stem against the flat edge has no chamfer — only the rounded side does

When designing a new bowled letter, reuse the existing bowl from `d` (or its
mirrors) so the family stays coherent. `a` is the exception: double-story
(top bar + gap + belly), but its belly uses the same 2-step chamfer.

### Letter-redesign status

- **Redesigned (new Inter Bold style)**: a, b, d, e, g, i, l, q, x
- **Original Corne logo style (3-step chamfer)**: c, n, o, r — these read fine
  on their own but visibly mismatch the redesigned letters when stacked
- **Not yet touched**: j, k, m, s, t, u, w, y

Letters actually rendered on the OLEDs (union of `alexi` + the seven layer
names): `a b c d e g i j k l m n o q r s t u w x y`. Letters `f h p v z` are
unused — don't bother adding them.

## OLED rendering pipeline

In `keymap.c`:

- `render_corne_letter(ch, top_dy)` — draws one glyph with its topmost display-y
  at `top_dy`. The glyph occupies `[top_dy - width + 1, top_dy]` on display y.
  Width-0 chars (and chars outside `a..z`) are skipped.
- `render_corne_word(word, n)` — stacks letters vertically with **proportional
  spacing** (`CORNE_LETTER_SPACING`, currently 6 empty pixels between adjacent
  letters). Word is centered on the 128-px display.

Don't add a fixed cell height — variable widths in fixed cells produce uneven
inter-letter gaps. Proportional spacing is the right model.

## OLED views

- **Master (RHS)**: renders the current layer name (7 chars, padded with
  trailing space). Layer names: `qwerty colemak symbols nums system magnet`.
  Note: `nums` is stored as `"nums   "` (4 chars + 3 trailing spaces) — the
  proportional-spacing renderer skips spaces, so the slave just stacks
  `n u m s`.
- **Slave (LHS)**: debug view controlled by `DEBUG_STRING` macro in
  `oled_task_user`:
  - Single char (e.g. `"x"`) → render 7 stacked copies (focus on one glyph)
  - Multi-char (e.g. `"alexi"`) → render the string as-is

After redesigning a letter, bump `DEBUG_STRING` to that letter, rebuild, flash,
and visually verify on the LHS.

## Workflow for redesigning a letter

1. Get a reference image (or describe the target style — typically Inter Bold).
2. Sketch the design in ASCII art and get user approval before editing.
3. Encode the bitmap as `uint16_t` values, set width, replace the entry in
   `corne_font`.
4. Set `DEBUG_STRING` to the letter for focused testing.
5. Build: `qmk userspace-compile` (output: `crkbd_rev1_lintuxt.hex`).
6. User flashes manually (caterina bootloader + `qmk flash` or QMK Toolbox).
7. Iterate based on visual feedback.

The clang diagnostics that fire on `keymap.c` (undeclared `SAFE_RANGE`,
`uint16_t`, etc.) are noise from clang's standalone parser missing QMK's
include paths — they're not real compile errors. The actual `qmk userspace-compile`
build is authoritative.

## RGB matrix quirk

The Corne RHS has dead LEDs. Underglow output must use a `+4` chain shift for
RHS firmware indices ≥ 27, and `U1` is a hardware phantom of `U5`. See
`rgb_matrix_user.inc` and the `qmk-rhs-dead-leds` memory for details.

## Don't touch

- The upstream QMK checkout at `../qmk` — that's pristine, only updated via
  `git fetch --tags && git checkout <newer-tag> && qmk git-submodule`
- Letters `c`, `n`, `o`, `r` unless explicitly redesigning them — they come
  from the original Corne logo bitmap and currently work
