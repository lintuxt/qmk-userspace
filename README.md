*Custom QMK firmware for my hand-built Corne (crkbd rev1). Bespoke OLED font, an American flag RGB Matrix effect, and a hardware-bypass workaround for three dead LEDs. Builds against unmodified upstream QMK — no fork to maintain.*

[![License: ISC](https://img.shields.io/badge/License-ISC-blue.svg)](https://github.com/lintuxt/qmk-userspace/blob/trunk/keyboards/crkbd/keymaps/lintuxt/keymap.c)
[![QMK 0.32.14](https://img.shields.io/badge/QMK-0.32.14-2ea44f)](https://github.com/qmk/qmk_firmware/releases/tag/0.32.14)

## Install

Requires the `qmk` CLI and an upstream QMK checkout (kept at `../qmk`, pinned to QMK 0.32.14).

```sh
qmk config user.qmk_home="$(cd ../qmk && pwd)"
qmk config user.overlay_dir="$(pwd)"
qmk userspace-compile
```

The build emits `crkbd_rev1_lintuxt.hex` at the repo root.

## Quickstart

Put the Corne into the caterina bootloader (reset button on the half you're flashing) and run:

```sh
qmk flash crkbd_rev1_lintuxt.hex
```

Or drop the hex into [QMK Toolbox](https://github.com/qmk/qmk_toolbox). Flash both halves — they share the same firmware image.

## Why it exists

I built my Corne in 2020. For six years I ran essentially stock firmware on it — the default QMK splash on the OLEDs, a generic rainbow on the underglow, and three dead LEDs on the right half that I'd hardware-bypassed with a jumper but never worked around in firmware.

Every customization I wanted was its own multi-day project. I had a list. I never shipped it.

The whole list closed in one afternoon with Claude Code: a bespoke OLED font drawn pixel-by-pixel, a custom RGB Matrix effect (`LINTUXT_AMERICAN` — mirrored American flag with a wind-ripple wave, per half), and a chain-shift workaround for the dead RHS LEDs. The full story: [Six years of "someday", shipped in an afternoon](https://lintuxt.ai/blog/six-years-of-someday-shipped-in-an-afternoon/).

This repo is the firmware that came out of that afternoon.

## Documentation

The keymap, font, and RGB effect live under [`keyboards/crkbd/keymaps/lintuxt/`](https://github.com/lintuxt/qmk-userspace/tree/trunk/keyboards/crkbd/keymaps/lintuxt):

- [`keymap.c`](https://github.com/lintuxt/qmk-userspace/blob/trunk/keyboards/crkbd/keymaps/lintuxt/keymap.c) — layers, custom font, OLED rendering
- [`rgb_matrix_user.inc`](https://github.com/lintuxt/qmk-userspace/blob/trunk/keyboards/crkbd/keymaps/lintuxt/rgb_matrix_user.inc) — `LINTUXT_AMERICAN` effect
- [`config.h`](https://github.com/lintuxt/qmk-userspace/blob/trunk/keyboards/crkbd/keymaps/lintuxt/config.h), [`rules.mk`](https://github.com/lintuxt/qmk-userspace/blob/trunk/keyboards/crkbd/keymaps/lintuxt/rules.mk) — build config

To bump QMK: `cd ../qmk && git fetch --tags && git checkout <newer-tag> && qmk git-submodule`, then rebuild and resolve any keymap drift.

## License

ISC — see the header on [`keymap.c`](https://github.com/lintuxt/qmk-userspace/blob/trunk/keyboards/crkbd/keymaps/lintuxt/keymap.c).
