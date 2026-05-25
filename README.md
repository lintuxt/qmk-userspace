# qmk_userspace

External QMK userspace for @lintuxt's Corne (crkbd rev1) keymap.

Builds against an unmodified upstream QMK — no fork to maintain.
Currently targets QMK **0.32.14**.

## Layout

- `keyboards/crkbd/keymaps/lintuxt/` — the keymap (`keymap.c`, `config.h`, `rules.mk`)
- `qmk.json` — build-target manifest
- `crkbd_rev1_lintuxt.hex` — latest built firmware

## Building

Requires the `qmk` CLI and an upstream QMK checkout (kept at `../qmk`).

One-time setup:

```bash
qmk config user.qmk_home="$(cd ../qmk && pwd)"
qmk config user.overlay_dir="$(pwd)"
```

Build:

```bash
qmk userspace-compile
```

## Upgrading QMK

Bump the upstream checkout — no fork to merge:

```bash
cd ../qmk && git fetch --tags && git checkout <newer-tag> && qmk git-submodule
```

Then rebuild and fix any newly surfaced breaking changes in the keymap.

## Flashing

Manual step: put the Corne into the caterina bootloader (reset button) and flash
`crkbd_rev1_lintuxt.hex` with `qmk flash` or QMK Toolbox.
