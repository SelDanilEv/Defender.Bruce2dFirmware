#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd "$script_dir/.." && pwd)"
wifi_exe_path="$script_dir/wifi_repeater_state_test.exe"
obd_exe_path="$script_dir/obd_pids_test.exe"

g++ -std=c++17 -Wall -Wextra -DT_EMBED_1101 -I"$repo_root/src" \
    "$script_dir/wifi_repeater_state_test.cpp" \
    "$repo_root/src/modules/wifi/wifi_repeater_state.cpp" \
    -o "$wifi_exe_path"

"$wifi_exe_path"

g++ -std=c++17 -Wall -Wextra -I"$repo_root/src" \
    "$script_dir/obd_pids_test.cpp" \
    "$repo_root/src/modules/obd/obd_pids.cpp" \
    "$repo_root/src/modules/obd/obd_poll_scheduler.cpp" \
    -o "$obd_exe_path"

"$obd_exe_path"
