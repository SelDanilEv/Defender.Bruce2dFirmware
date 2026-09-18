# AGENTS.md - Bruce Firmware

Instructions for AI coding agents working in this repo. English, terse, technically accurate.

## Knowledge graph (always use)

Before any code search or change: query `graphify-out/` first.
- `graphify-out/GRAPH_REPORT.md` - god nodes (most-connected core abstractions), community hubs, communities, surprising connections. Read this to orient before touching unfamiliar code.
- `graphify-out/graph.json` - full node/edge relations, consumed by the graphify CLI.
- Use the `graphify` skill/CLI when available: `graphify query "<question>"` (BFS over graph.json), `graphify path "A" "B"` (shortest path between two symbols), `graphify explain "X"` (plain-language explanation of a node and neighbors), `graphify affected "X"` (reverse-impact search).
- Fall back to grep/glob only when the graph has no answer (new files not yet indexed, non-code text, etc).
- After a significant structural change (new module, renamed/moved files, new menu item, changed includes): refresh the graph. Graph was last built scoped to `src/` (see `graphify-out/.graphify_root`). Refresh with:
  ```
  graphify update src
  graphify cluster-only src
  ```
  `update` re-extracts changed files (no LLM call, uses `graphify-out/manifest.json` mtime/hash cache). `cluster-only` rebuilds communities and regenerates `GRAPH_REPORT.md`. If these commands fail or the CLI is unavailable: rerun graphify on repo root.
- `graphify-out/graph.json` and `graphify-out/GRAPH_REPORT.md` are versioned in git (see `.gitignore`); everything else under `graphify-out/` (cache/, manifest.json, graph.html, cost.json, .graphify_*) is local state, do not commit it.

## Project overview

Bruce is an ESP32 firmware for offensive-security / red-team tooling (WiFi, BLE, RF sub-GHz, RFID/NFC, IR, NRF24, GPS, FM, USB/BLE HID injection, JS interpreter). Built with PlatformIO + Arduino framework, C++17-ish (Arduino core), targets 30+ boards (M5Stack, LILYGO, CYD clones, RockBase, Elecrow, custom Bruce PCBs). AGPL licensed. Upstream docs: https://wiki.bruce.computer.

Primary target board: the LILYGO T-Embed CC1101, env `lilygo-t-embed-cc1101` (`boards/lilygo-t-embed-cc1101/lilygo-t-embed-cc1101.ini`; distinct from its `lilygo-t-embed-cc1101-slim` variant). Prioritize this env when a change forces a board-specific tradeoff, and keep every other board env building.

## Repo layout

Verified against actual directory tree at repo root:

- `src/main.cpp` - firmware entry point.
- `src/core/` - platform-independent core: display, config, settings, menu system, keyboard/input, SD/LittleFS, connectivity glue, serial commands (`src/core/serial_commands/`), USB (`src/core/USBSerial/`), WiFi common helpers (`src/core/wifi/`).
- `src/core/menu_items/` - one class per top-level menu (`WifiMenu`, `BleMenu`, `RFMenu`, `RFIDMenu`, `IRMenu`, `NRF24.{h,cpp}`, `GpsMenu`, `FMMenu`, `EthernetMenu`, `LoRaMenu`, `ScriptsMenu`, `ClockMenu`, `OthersMenu`, `ConfigMenu`, `FileMenu`, `ConnectMenu`).
- `src/modules/` - feature implementations grouped by domain: `wifi/`, `ble/`, `ble_api/`, `rf/`, `rfid/`, `ir/`, `NRF24/`, `gps/`, `fm/`, `lora/`, `ethernet/`, `pwnagotchi/`, `bjs_interpreter/` (JS engine), `badusb_ble/`, `reverseShell/`, `others/`.
- `boards/<board>/` - per-board PlatformIO `.ini` fragment, `interface.cpp`/pin headers, board `.json`. `boards/_boards_json/` holds PlatformIO board defs, `boards/_New-Device-Model/` is the template for adding a board, `boards/pinouts/` has shared pin headers.
- `include/` - generated/shared headers (e.g. embedded web assets, build-year define). Do not hand-edit generated ones (see do-not-touch).
- `lib/` - vendored/third-party libraries pulled in as PlatformIO libs. Treat as do-not-touch (see below).
- `embedded_resources/`, `sd_files/`, `media/`, `pcbs/` - static assets, example SD content, images, PCB design files.
- `tools/` - standalone helper scripts (e.g. `gen_mfcodes.py`).
- `tests/` - host-side (non-ESP32) unit tests, see Testing below.
- `docker/` - CI build container (`Dockerfile.ci`, `run_all_envs.sh`).
- `graphify-out/` - knowledge graph, see rule above.
- Root build scripts/config: `platformio.ini`, `build.py`, `patch.py`, `patch_library_conflicts.py`, `pre_build_current_year.py`, `flto_prep.py`, `gen_mqjs_headers.py`, `build-firmware.ps1`, `custom_*.csv` (partition tables), `docker-compose.yml`.

## Build commands

PlatformIO-based. Environments are defined in `platformio.ini` under `[platformio] default_envs` (all commented out except the active default) plus per-board `.ini` fragments pulled in via `extra_configs = boards/*.ini / boards/*/*.ini`. Example env names (verified in `platformio.ini` / `.github/workflows/PR_All_envs.yml`): `m5stack-cardputer`, `m5stack-cplus2`, `m5stack-cores3`, `lilygo-t-embed-cc1101`, `nm-cyd-c5`, `arduino-nesso-n1`, `CYD-2432S028`, `reaper`. `LAUNCHER_<env>` variants build the M5Launcher-compatible LITE_VERSION.

Direct PlatformIO:
```
pio run -e <environment>
```
Merged flashable binary is written to repo root as `Bruce2D-<tag>-v<X.Y.Z>.bin` (`<tag>` is `tembed` for
`lilygo-t-embed-cc1101`, `tembed-slim` for `lilygo-t-embed-cc1101-slim`, otherwise the raw env name). The
version comes from root `VERSION` (`X.Y`, hand-edited) plus an auto-bumped patch tracked in local, git-ignored
`build_version.txt`: each build increments the patch unless `VERSION` changed, in which case it resets to 0.

Windows helper script `build-firmware.ps1` (repo root, local convenience script):
```
./build-firmware.ps1 -Environment lilygo-t-embed-cc1101 [-CopyTo <dir>] [-TargetName bruce.bin]
```
Wraps `pio run -e <Environment>`, verifies the merged bin was produced, optionally copies it, opens Explorer at the result.

Docker (matches CI): `docker-compose.yml` builds `docker/Dockerfile.ci` and runs `docker/run_all_envs.sh` inside; override target envs via the `PIO_ENVS` env var in `docker-compose.yml`.
```
docker compose up --build
```

CI (`.github/workflows/`): `PR_check.yml` and `buil_parallel.yml` build a matrix of envs on every PR touching `**.yml|.h|.cpp|.py|.html|.css|.js|.ini|.json|.csv`; `manual_build_sel_env.yml` and `PR_All_envs.yml` are `workflow_dispatch` variants for building one or all envs on demand.

## Coding conventions

**Mandatory. Every AI agent MUST follow these rules and match the surrounding code in any file it touches. `clang-format` is authoritative for formatting: run it before committing; do not fight it by hand.** Rules below are extracted from the real codebase; each cites example files.

1. Formatting (from `.clang-format`, LLVM base): 4-space indent, no tabs, column limit 110. Attached braces (`BreakBeforeBraces: Attach`), no bin-packed function arguments. Short functions/lambdas/ifs/loops/case labels may stay on one line where they already fit (`AllowShort*: All/Always`). Case labels indented (`IndentCaseLabels: true`).
2. Naming: classes/structs `PascalCase` (`WifiMenu`, `ARPScanner`, `AuthBypassEngine`). Methods and free functions `lowerCamelCase` (`optionsMenu`, `drawIcon`, `themePath`, `configMenu`). Member variables: mixed, no single enforced rule. Majority (272 counted declarations) is plain `lowerCamelCase` with no prefix, e.g. `config`, `stats`, `currentIndex`, `lastBroadcastTime` in `ActiveBroadcastAttack` (`src/modules/wifi/karma_attack.h`). A sizeable minority (141 counted) uses a leading-underscore `_lowerCamelCase` for private state, e.g. `_channel`, `_deauth`, `_autoMode` in `EvilPortal` (`src/modules/wifi/evil_portal.h`), and even `_active` inside the otherwise-unprefixed `ActiveBroadcastAttack` class above. Default to no prefix for new members; match the surrounding class if it already uses `_prefix`. Macros/`#define`/compile-time constants `UPPER_SNAKE_CASE` (`LITE_VERSION`, `BORDER_PAD_X`, `CC1101_GDO2_PIN`). Files `snake_case` for modules (`wifi_repeater.cpp/h`, `karma_attack.cpp/h`), `PascalCase` for menu classes (`WifiMenu.cpp/h`).
3. Header guards: use `#ifndef NAME_H` / `#define NAME_H` / `#endif`, not `#pragma once` (154 headers use `#ifndef` guards vs 24 `#pragma once`, out of 202 headers under `src/`+`include/`; guards are the standard, match it). Naming of the guard token is mixed (`__WIFI_MENU_H__` in `src/core/menu_items/WifiMenu.h`, `COLOR_STORAGE_H` in `src/core/settingsColor.h`); pick a unique guard per header, either style is acceptable, prefer matching the sibling file in the same directory.
4. One feature (class or free-function group) per `.cpp`/`.h` pair, named after the feature (`src/modules/wifi/wifi_repeater.*`, `karma_attack.*`).
5. Includes: quoted relative paths from `src/` root for project headers (`"core/display.h"`, `"modules/wifi/karma_attack.h"`); angle brackets for library/framework headers (`<MenuItemInterface.h>`, Arduino/lib headers). See `src/core/menu_items/WifiMenu.cpp` header block.
6. Board/feature gating via preprocessor around both includes and menu entries (`#if defined(T_EMBED_1101)`, `#ifndef LITE_VERSION`), never a runtime check for hardware that physically does not exist on a board.
7. Strings: use Arduino `String` (~3400 word occurrences repo-wide) not `std::string` (~110, mostly confined to `src/core/net_utils.cpp/h`, BLE modules like `src/modules/ble/ble_sniffer.cpp`, and `src/modules/ethernet/ARPScanner.cpp/h`; match the file's existing type). `F("...")` is used sparingly (46 real call sites in 6 files, e.g. `src/modules/rfid/PN532.cpp`) and `PROGMEM` likewise (26 occurrences in 6 files, e.g. `src/core/display.h`, `src/modules/wifi/karma_attack.cpp`); neither is a required convention, reach for them only in tight-RAM paths.
8. User-facing UI output: use the shared display helpers, not raw `tft.*` calls, so themes/borders stay consistent. Common ones (by frequency): `padprintln`, `displayError`, `displaySuccess`, `displayInfo`, `displayWarning`, `printSubtitle`, `drawMainBorder`, `displayRedStripe` (declared in `src/core/display.h`). Raw `tft.*` is for custom drawing only (icons, canvases).
9. Debug/diagnostic logging: mixed, both idioms current. `Serial.println` / `Serial.printf` / `Serial.print` (~720 call sites) is the majority idiom, e.g. `src/core/bus_HAL.cpp`, `src/core/connect/esp_connection.cpp`. ESP-IDF `log_i()` / `log_e()` / `log_d()` / `log_w()` (156 call sites) is used for internal diagnostics in newer/core code, e.g. `src/core/config.cpp`, `src/core/display.cpp`, `src/core/mykeyboard.cpp`. Match whichever idiom the file already uses; keep debug prints minimal and remove noisy ones before commit.
10. No i18n/translation system exists in the repo (no translate/`_()`/i18n macro). User-facing strings are English literals inline. Do not invent a translation layer.
11. Comments: self-documenting names over comments. Add a comment only for a non-obvious hardware/protocol constraint or deliberate workaround, kept to one line. No restating code, no commented-out code left behind.

## How to add a menu item / module

1. Implement the feature under `src/modules/<domain>/your_feature.{h,cpp}` (or a new `src/modules/<domain>/` if it is a new domain). Gate hardware-specific code with `#if defined(...)` / `#ifndef LITE_VERSION` as needed, following `src/modules/wifi/wifi_repeater.*`.
2. If it belongs under an existing top-level menu (WiFi, BLE, RF, ...), add an entry in that menu's `optionsMenu()` in `src/core/menu_items/<Menu>.cpp`, e.g. `WifiMenu::optionsMenu()` in `src/core/menu_items/WifiMenu.cpp`, and `#include` the new module header at the top of that file.
3. If it needs a brand-new top-level menu, create `src/core/menu_items/YourMenu.{h,cpp}` implementing `MenuItemInterface` (see `WifiMenu.h`: constructor sets the display name, implement `optionsMenu()`, `drawIcon()`, optionally `hasTheme()`/`themePath()`), then register it:
   - add `YourMenu yourMenu;` member in `src/core/main_menu.h`,
   - add `&yourMenu,` to the `_menuItems` initializer list in `MainMenu::MainMenu()` (`src/core/main_menu.cpp`), gated with `#if` the same way `loraMenu`/`ethernetMenu` are for `LITE_VERSION`.
4. Add any new source files to PlatformIO's default source filter is automatic (PlatformIO globs `src/`); no manual file list to update.
5. Refresh the knowledge graph after landing the change (see graph rule above).

## Board config notes

- Each board lives in `boards/<board-name>/` with its own `.ini` (PlatformIO env + build flags/pins), an `interface.cpp` for board-specific bring-up, and sometimes a board `.json`.
- `boards/_boards_json/` supplies `boards_dir` for PlatformIO (`boards_dir = boards/_boards_json` in `platformio.ini`).
- `boards/_New-Device-Model/` is the scaffold to copy when adding a new board.
- `boards/pinouts/` holds shared pin header files referenced by multiple boards.
- Root `platformio.ini` defines the common `[env]`, `[env_light]` (LITE_VERSION), `[env_4mb]` (4MB flash targets) sections that board `.ini` files extend; it pulls in every board fragment via `extra_configs = boards/*.ini` and `boards/*/*.ini`.
- Partition tables: `custom_4Mb.csv`, `custom_4Mb_full.csv`, `custom_8Mb.csv`, `custom_16Mb.csv` at repo root, selected per board/env.

## Testing notes

`tests/` contains host-side (desktop g++, not ESP32) unit tests, currently covering `src/modules/wifi/wifi_repeater_state.cpp` (`RepeaterState` state machine) via `tests/wifi_repeater_state_test.cpp`. Run with:
```
bash tests/run_host_tests.sh
```
Requires g++ with C++17 on PATH; compiles the test plus the production `.cpp` directly (no mocking framework), fails non-zero on any assertion failure. `tests/wifi_repeater_state_test.exe` is a local build artifact (git-ignored via `tests/*.exe`), not checked in. There is no on-device/hardware-in-the-loop test suite; CI validates by compiling every board env (see Build commands).

## Commit / PR conventions

- `.github/pull_request_template.md` defines the required PR body sections: Proposed Changes, Types of Changes, Verification, Testing, Linked Issues, User-Facing Change (a fenced `release-note` block, or literal `NONE`), Further Comments. Fill these in for every PR.
- `.github/ISSUE_TEMPLATE/bug_report.md` and `feature_request.md` are the issue templates.
- No commit-message convention file exists in the repo; commit history is free-form, imperative short summaries.
- CI (`PR_check.yml`) runs on every PR touching code/config files against `main`/`dev`; keep builds green for the affected board envs before requesting review.

## Upstream sync (monthly)

This repo is a fork of `upstream` (https://github.com/BruceDevices/firmware, branch `main`). Once a month, pull upstream changes in:
1. `git fetch upstream`, then `git log --oneline HEAD..upstream/main` to review what is new.
2. Branch `sync/upstream-YYYY-MM` from `main`, `git merge upstream/main`.
3. Resolve conflicts keeping fork features (Bruce-2D branding, WiFi Repeater, OBD Dashboard, `VERSION`/`Bruce2D-*.bin` versioning, CI bin globs) while taking upstream fixes.
4. Build `lilygo-t-embed-cc1101` (must pass), plus any env touched by conflicts; run `bash tests/run_host_tests.sh`.
5. Bump minor in `VERSION`, refresh graphify, merge to `main`, push.

Last sync base: upstream `a59213f3` (2026-09-09).

## Do-not-touch

- `.pio/` - PlatformIO build cache/output, git-ignored, never edit or commit.
- `lib/` - vendored third-party libraries pulled in as PlatformIO deps; treat as read-only unless a change is specifically about patching a vendored lib (see `patch_library_conflicts.py`).
- Generated/derived files listed in `.gitignore`: `include/webFiles.h`, `include/current_year.h`, `checksum.sha256`, `compile_commands.json`, `mqjs_build/`, `lib/mquickjs_headers/mqjs_stdlib_generator*`, root `*.bin` firmware artifacts, `docker-logs`.
- `graphify-out/cache/`, `graphify-out/manifest.json`, `graphify-out/graph.html`, `graphify-out/cost.json`, `graphify-out/.graphify_*` - local graphify state, git-ignored; only `graph.json` and `GRAPH_REPORT.md` under `graphify-out/` are versioned.
- `.vscode/` machine-specific files listed in `.gitignore` (`.browse.c_cpp.db*`, `c_cpp_properties.json`, `launch.json`, `extensions.json`, `ipch`).

## README conflicts

None found: `README.md` documents end-user features/flashing instructions and does not overlap with build/dev workflow claims made here.
