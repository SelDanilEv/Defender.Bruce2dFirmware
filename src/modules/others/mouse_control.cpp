// USB Mouse Control - encoder-driven HID mouse

#include "mouse_control.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include "globals.h"
#include <USB.h>

#ifdef USB_as_HID
#include <USBHIDMouse.h>

static USBHIDMouse *Mouse = nullptr; // Lazy init to avoid global HID descriptor registration

// Flip to true to swap CW/CCW mapping after hardware test, without touching the mode logic below.
static const bool INVERT_DIRECTION = false;

static const int8_t CURSOR_STEP = 6;
static const int8_t SCROLL_STEP = 3;

enum MouseMode { MODE_VERTICAL = 0, MODE_HORIZONTAL, MODE_CLICK, MODE_SCROLL, NUM_MOUSE_MODES };

static const char *MODE_NAMES[NUM_MOUSE_MODES] = {"Vertical", "Horizontal", "Click", "Scroll"};

void initMouseControlUSB() {
    if (Mouse == nullptr) Mouse = new USBHIDMouse();
    USB.begin();
    if (Mouse != nullptr) Mouse->begin();
}

void cleanupMouseControlUSB() {
    if (Mouse != nullptr) {
        Mouse->end();
        delete Mouse;
        Mouse = nullptr;
    }
    USB.~ESPUSB();
    delay(100);
    USB.enableDFU();
    delay(100);
}

void drawMouseModeLabel(MouseMode mode) {
    printSubtitle("Mode: " + String(MODE_NAMES[mode]));
    padprintln("OK: next mode | BACK: exit");
    padprintln("Rotate to control mouse");
}

void drawMouseControlScreen(MouseMode mode) {
    drawMainBorderWithTitle("USB Mouse");
    drawMouseModeLabel(mode);
}

void applyEncoderStep(MouseMode mode, bool forward) {
    if (Mouse == nullptr) return;
    bool goPositive = INVERT_DIRECTION ? !forward : forward;

    switch (mode) {
        case MODE_VERTICAL: Mouse->move(0, goPositive ? -CURSOR_STEP : CURSOR_STEP, 0); break;
        case MODE_HORIZONTAL: Mouse->move(goPositive ? CURSOR_STEP : -CURSOR_STEP, 0, 0); break;
        case MODE_CLICK: Mouse->click(goPositive ? MOUSE_LEFT : MOUSE_RIGHT); break;
        case MODE_SCROLL: Mouse->move(0, 0, goPositive ? -SCROLL_STEP : SCROLL_STEP); break;
        default: break;
    }
}

void mouseControl_setup() {
    initMouseControlUSB();

    drawMainBorderWithTitle("USB Mouse");
    printSubtitle("Starting USB...");
    delay(1500); // let the host enumerate the HID device before sending events

    MouseMode mode = MODE_VERTICAL;
    drawMouseControlScreen(mode);

    bool exitRequested = false;
    while (!exitRequested) {
        InputHandler();

        if (check(SelPress)) {
            mode = (MouseMode)((mode + 1) % NUM_MOUSE_MODES);
            drawMouseControlScreen(mode);
        }

        if (check(NextPress)) { applyEncoderStep(mode, true); }

        if (check(PrevPress)) { applyEncoderStep(mode, false); }

        if (check(EscPress)) { exitRequested = true; }

        delay(1);
    }

    cleanupMouseControlUSB();
}

#endif // USB_as_HID
