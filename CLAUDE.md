@AGENTS.md

Read AGENTS.md first for project overview, layout, build/test/PR conventions, and do-not-touch list. The AGENTS.md "Coding conventions" section is mandatory for all agents: follow those rules and match surrounding code; clang-format is authoritative for formatting.

Primary target board (see AGENTS.md "Project overview"): LILYGO T-Embed CC1101, env `lilygo-t-embed-cc1101`. When a change forces a board-specific tradeoff, favor this env first, without breaking other board builds.

Knowledge graph (always use): before searching or changing code, check `graphify-out/GRAPH_REPORT.md` and `graphify-out/graph.json` (graphify skill: query/path/explain/affected). Refresh with `graphify update src` then `graphify cluster-only src` after structural changes. Grep/glob only as fallback.

Claude Code specifics:
- Environment is Windows 11, PowerShell primary shell; use PowerShell-safe commands (no bash-only syntax) unless invoking `tests/run_host_tests.sh`, which needs bash + g++.
- Use the `graphify` skill directly when available instead of shelling out to the CLI by hand.
- `.pio/`, `lib/`, and generated headers under `include/` are off-limits, per AGENTS.md do-not-touch list.
