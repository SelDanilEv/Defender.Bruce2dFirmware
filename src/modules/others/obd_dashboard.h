#if !defined(LITE_VERSION)
#ifndef __OBD_DASHBOARD_H__
#define __OBD_DASHBOARD_H__

// Reads fuel tank level, engine load, throttle position and battery voltage over WiFi from an
// ELM327-compatible OBD-II dongle, probing several PIDs per value and logging every exchange
// to a per-session log file on SD/LittleFS.
void obd_dashboard_setup();

#endif // __OBD_DASHBOARD_H__
#endif // LITE_VERSION
