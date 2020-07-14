#include QMK_KEYBOARD_H
#include "analog.h"
#include "report.h"
#include "print.h"

#define KC_X0 LT(_FN, KC_ESC)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
     KC_Q, KC_LSHIFT, KC_E, KC_SPACE
  ),

};
// clang-format on

// Joystick
// Set Pins
uint8_t xPin  = F5;   // VRx / /B4
uint8_t yPin  = F4;   // VRy // B5

// Set Parameters
uint16_t triggerOffset = 100;

int8_t xPolarity = 1;
int8_t yPolarity = -1;

int16_t xOrigin = 123;
int16_t yOrigin = 123;

uint16_t lastCursor = 0;
uint8_t cursorTimeout = 10;


int8_t axisToMovement(uint8_t pin, uint16_t origin, int8_t polarity) {
    int16_t position = analogReadPin(pin);
    #if DEBUG_PHILIP
    xprintf("%d - position - ", position);
    #endif

    if (position > (origin + triggerOffset)) {
        return 1 * polarity;
    } else if (position < (origin - triggerOffset)) {
        return -1 * polarity;
    }

    return 0;
}


uint16_t i = 0;
void getWASD(void) {
    if (timer_elapsed(lastCursor) > cursorTimeout) {
        lastCursor = timer_read();
        int8_t x = axisToMovement(xPin, xOrigin, xPolarity);
        #if DEBUG_PHILIP
        xprintf("%d X - origin - %d\n", x, xOrigin);
        #endif
        int8_t y = axisToMovement(yPin, yOrigin, yPolarity);
        #if DEBUG_PHILIP
        xprintf("%d Y - origin - %d\n", y, yOrigin);
        #endif
        if (x < 0) {
            // KC_A
            add_key(KC_A);
            del_key(KC_D);
        } else if (x > 0) {
            // KC_D
            del_key(KC_A);
            add_key(KC_D);
        } else {
            // Release KC_A/KC_D
            del_key(KC_A);
            del_key(KC_D);
        }
        if (y < 0) {
            // KC_W
            add_key(KC_W);
            del_key(KC_S);
        } else if (y > 0) {
            // KC_S
            del_key(KC_W);
            add_key(KC_S);
        } else {
            // Release KC_W/KC_S
            del_key(KC_W);
            del_key(KC_S);
        }
        send_keyboard_report();
    }
}

void matrix_scan_user() {
    getWASD();
}

void matrix_init_keymap(void) {
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  #if DEBUG_PHILIP
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
  #endif

    // Account for drift
  xOrigin = analogReadPin(xPin);
  yOrigin = analogReadPin(yPin);
}
