# Host Tests

`wifi_repeater_state_test.cpp` exercises `wifi_repeater::RepeaterState`, the state machine behind
the WiFi Repeater feature, without needing real ESP32 hardware. It covers: claiming the WiFi mode
before the connection result is known, building the correct cleanup plan when the access point,
station, or NAPT steps fail partway through setup, retrying only the cleanup actions still
pending after a partial failure, cancellation while connecting, and losing the upstream
connection after the repeater is already running.

Run the suite with one command:

```
bash tests/run_host_tests.sh
```

This compiles the test against `src/modules/wifi/wifi_repeater_state.cpp` with `g++ -std=c++17`
and runs the resulting binary, so a g++ with C++17 support must be on PATH. The script exits
non-zero if any assertion fails.
