#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd "$script_dir/.." && pwd)"
exe_path="$script_dir/wifi_repeater_state_test.exe"

g++ -std=c++17 -Wall -Wextra -DT_EMBED_1101 -I"$repo_root/src" \
    "$script_dir/wifi_repeater_state_test.cpp" \
    "$repo_root/src/modules/wifi/wifi_repeater_state.cpp" \
    -o "$exe_path"

"$exe_path"
