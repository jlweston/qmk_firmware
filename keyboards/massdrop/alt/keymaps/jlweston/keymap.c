/* Copyright 2021 jlweston
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "keymap.h"

// Layer declarations
enum layers {
    _WINDOWS = 0, //Default Windows layer
    _MAC, //Default Mac layer
    _GAMING, //Disable the Windows key for gaming
    _LIGHTS_MEDIA, //All LED and media controls
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, // USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              // USB Toggle Automatic GCR control
    DBG_TOG,               // DEBUG Toggle On / Off
    DBG_MTRX,              // DEBUG Toggle Matrix Prints
    DBG_KBD,               // DEBUG Toggle Keyboard Prints
    DBG_MOU,               // DEBUG Toggle Mouse Prints
    MD_BOOT,               // Restart into bootloader after hold timeout
    TH_WM,                 // Toggle Windows and Mac base layer
};

#include "tap_dances.c"
// #include "combos.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Windows
     * ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬────────────┬───────┐
     * │       │       │       │       │       │       │       │       │       │       │       │       │       │            │       │
     * │   `   │   1   │   2   │   3   │   4   │   5   │   6   │   7   │   8   │   9   │   0   │   -   │   =   │ BackSpace  │ Home  │
     * │       │       │       │       │       │       │       │       │       │       │       │       │       │            │       │
     * ├───────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬─────────┼───────┤
     * │          │       │       │       │       │       │       │       │       │       │       │       │       │         │       │
     * │    Tab   │   Q   │   W   │   E   │   R   │   T   │   Y   │   U   │   I   │   O   │   P   │   [   │   ]   │    \    │  Del  │
     * │          │       │       │       │       │       │       │       │       │       │       │       │       │         │       │
     * ├──────────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─────────┼───────┤
     * │            │       │       │       │       │       │       │       │       │       │       │       │               │       │
     * │  Caps      │   A   │   S   │   D   │   F   │   G   │   H   │   J   │   K   │   L   │   ;   │   '   │    Return     │ PgUp  │
     * │            │       │       │       │       │       │       │       │       │       │       │       │               │       │
     * ├────────────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴───────┬───────┼───────┤
     * │               │       │       │       │       │       │       │       │       │       │       │            │       │       │
     * │     Shift     │   Z   │   X   │   C   │   V   │   B   │   N   │   M   │   ,   │   .   │   /   │   Shift    │  Up   │ PgDn  │
     * │               │       │       │       │       │       │       │       │       │       │       │            │       │       │
     * ├─────────┬─────┴───┬───┴─────┬─┴───────┴───────┴───────┴───────┴───────┴─────┬─┴───────┼───────┴─┬──┬───────┼───────┼───────┤
     * │         │         │         │                                               │         │         │▒▒│       │       │       │
     * │  Ctrl   │   GUI   │   Alt   │                     Space                     │   Alt   │  Func   │▒▒│ Left  │ Down  │ Right │
     * │         │         │         │                                               │         │         │▒▒│       │       │       │
     * └─────────┴─────────┴─────────┴───────────────────────────────────────────────┴─────────┴─────────┴──┴───────┴───────┴───────┘
     */
    [_WINDOWS] = LAYOUT_65_ansi_blocker(
        TD(TD_GRAVE),    TD_F1,   TD_F2,      TD_F3,   TD_F4,   TD_F5,   TD_F6,   TD_F7,   TD_F8,   TD_F9,   TD_F10,        TD_F11,           TD_F12,  KC_BSPC, KC_DEL,  \
        MEH_T(KC_TAB),   KC_Q,    KC_W,       KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,          KC_LBRC,          KC_RBRC, KC_BSLS, KC_HOME, \
        KC_CAPS,         KC_A,    KC_S,       KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,       KC_QUOT,                   KC_ENT,  KC_PGUP, \
        LSFT_T(KC_LCBR), KC_Z,    KC_X,       KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,       RSFT_T(KC_RCBR),           KC_UP,   KC_PGDN, \
        KC_LCTL,         KC_LGUI, KC_LALT,                      KC_SPC,                             KC_RALT, TD_LAYER,                        KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    /* Mac
     * ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬────────────┬───────┐
     * │       │       │       │       │       │       │       │       │       │       │       │       │       │            │       │
     * │   `   │   1   │   2   │   3   │   4   │   5   │   6   │   7   │   8   │   9   │   0   │   -   │   =   │ BackSpace  │ Home  │
     * │       │       │       │       │       │       │       │       │       │       │       │       │       │            │       │
     * ├───────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬─────────┼───────┤
     * │          │       │       │       │       │       │       │       │       │       │       │       │       │         │       │
     * │    Tab   │   Q   │   W   │   E   │   R   │   T   │   Y   │   U   │   I   │   O   │   P   │   [   │   ]   │    \    │  Del  │
     * │          │       │       │       │       │       │       │       │       │       │       │       │       │         │       │
     * ├──────────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─────────┼───────┤
     * │            │       │       │       │       │       │       │       │       │       │       │       │               │       │
     * │  Caps      │   A   │   S   │   D   │   F   │   G   │   H   │   J   │   K   │   L   │   ;   │   '   │    Return     │ PgUp  │
     * │            │       │       │       │       │       │       │       │       │       │       │       │               │       │
     * ├────────────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴───────┬───────┼───────┤
     * │               │       │       │       │       │       │       │       │       │       │       │            │       │       │
     * │     Shift     │   Z   │   X   │   C   │   V   │   B   │   N   │   M   │   ,   │   .   │   /   │   Shift    │  Up   │ PgDn  │
     * │               │       │       │       │       │       │       │       │       │       │       │            │       │       │
     * ├─────────┬─────┴───┬───┴─────┬─┴───────┴───────┴───────┴───────┴───────┴─────┬─┴───────┼───────┴─┬──┬───────┼───────┼───────┤
     * │         │         │         │                                               │         │         │▒▒│       │       │       │
     * │  Ctrl   │   Alt   │   GUI   │                     Space                     │   Alt   │  Func   │▒▒│ Left  │ Down  │ Right │
     * │         │         │         │                                               │         │         │▒▒│       │       │       │
     * └─────────┴─────────┴─────────┴───────────────────────────────────────────────┴─────────┴─────────┴──┴───────┴───────┴───────┘
     */
    [_MAC] = LAYOUT_65_ansi_blocker(
        TD(TD_GRAVE),    TD_F1,   TD_F2,    TD_F3,   TD_F4,   TD_F5,   TD_F6,   TD_F7,   TD_F8,   TD_F9,   TD_F10,          TD_F11,           TD_F12,  KC_BSPC, KC_DEL,  \
        MEH_T(KC_TAB),   KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,            KC_LBRC,          KC_RBRC, KC_BSLS, KC_HOME, \
        KC_CAPS,         KC_A,    KC_S,     KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,         KC_QUOT,                   KC_ENT,  KC_PGUP, \
        LSFT_T(KC_LCBR), KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,         RSFT_T(KC_RCBR),           KC_UP,   KC_PGDN, \
        KC_LCTL,         KC_LALT, KC_LGUI,                    KC_SPC,                             KC_RALT, TD_LAYER,                          KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
   //Replaces Windows key with NOOP for gaming
    [_GAMING] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, XXXXXXX, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    [_LIGHTS_MEDIA] = LAYOUT_65_ansi_blocker(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE, \
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS, _______, KC_END,  \
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU, \
        _______, RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG, _______, _______, _______, _______,          KC_PGUP, KC_VOLD, \
        _______, _______, _______,                            _______,                            _______, _______, KC_MPRV, KC_MPLY, KC_MNXT  \
    ),
    /*
    [TEMPLATE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

#ifdef _______
#undef _______
#define _______ {0, 0, 0}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [_WINDOWS] = {
        CYAN,    AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   CYAN,    CYAN,
        CYAN,    AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   CYAN,
        CYAN,    AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,            CYAN,    CYAN,
        CYAN,    AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   CYAN,             AZURE,   CYAN,
        CYAN,    CYAN,    CYAN,                               AZURE,                              CYAN,    CYAN,    AZURE,   AZURE,   AZURE,
        //UnderGlow
        CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,
        CYAN,                                                                                                                         CYAN,
        CYAN,                                                                                                                         CYAN,
        CYAN,                                                                                                                         CYAN,
        CYAN,                                                                                                                         CYAN,
        CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN
        },
    [_MAC] = {
        CHART,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   CHART,   CHART,
        CHART,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   CHART,
        CHART,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE ,           CHART,   CHART,
        CHART,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   AZURE,   CHART ,           AZURE,   CHART,
        CHART,   CHART,   CHART ,                             AZURE ,                             CHART,   CHART,   AZURE,   AZURE,   AZURE,
        //UnderGlow
        CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART
       },
    [_GAMING] = {
        RED,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RED,     RED,
        RED,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RED,     RED,
        RED,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RED,     RED,
        RED,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RED,
        RED,     RED,     RED,                                _______,                            RED,     RED,     _______, _______, _______,
        //UnderGlow
        RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED,
        RED,                                                                                                                          RED,
        RED,                                                                                                                          RED,
        RED,                                                                                                                          RED,
        RED,                                                                                                                          RED,
        RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED,     RED
         },
    [_LIGHTS_MEDIA] = {
        _______, PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    _______, _______,
        _______, PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    _______,
        _______, PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK  ,           _______, _______,
        _______, PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    PINK,    _______,          PINK,    _______,
        _______, _______, _______,                            PINK,                               _______, _______, PINK,    PINK,    PINK,
        //UnderGlow
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,                                                                                                                      _______,
        _______,                                                                                                                      _______,
        _______,                                                                                                                      _______,
        _______,                                                                                                                      _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
     },
     /*
    [TEMPLATE] = {
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______,
        //UnderGlow
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,                                                                                                                      _______,
        _______,                                                                                                                      _______,
        _______,                                                                                                                      _______,
        _______,                                                                                                                      _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
     },
     */
};

#undef _______
#define _______ KC_TRNS

#endif

uint16_t th_wm_timer;

static uint32_t idle_timer;
static bool is_idle;

void matrix_scan_user() {
    // Check the timer only if the keyboard is not idle
    if (!is_idle) {
        if (timer_elapsed32(idle_timer) >= (uint32_t) BACKLIGHT_IDLE_TIMEOUT * 1000) {
            is_idle = true;

            // Both backlight_level and backlight_level_noeeprom modify the global backlight config (not useful)
            // Instead, use backlight_set in order to restore the current backlight level later on
            rgb_matrix_set_color_all(0, 0, 0);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {    // Reset timer on each keypress
    idle_timer = timer_read32();

    // Enable backlight back only when keyboard is idling (which implies the backlight was turned off previously)
    if (is_idle) {
        is_idle = false;
        disable_layer_color = false;
    }

    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        case TH_WM:
            if(record->event.pressed) {
                th_wm_timer = timer_read();
                layer_on(_LIGHTS_MEDIA);
            } else {
                layer_off(_LIGHTS_MEDIA);
                if (timer_elapsed(th_wm_timer) < TAPPING_TERM) {
                    if (layer_state_is(_MAC)) {
                        layer_move(_WINDOWS);
                    } else {
                        layer_move(_MAC);
                    }
                }
            }
            return true;
        default:
            return true; //Process all other keycodes normally
    }
}

uint32_t set_layer_color(int layer) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };

        // if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
        //     // Use this to set a secondary colour for special keys?
        //     rgb_matrix_set_color(i, 0, 0, 0);
        // } else
        if (i == 30 && host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(30, 255, 0, 0); // Todo make brightness variable, use theme colour?
        } else if (hsv.h || hsv.s || hsv.v) {
            RGB rgb = hsv_to_rgb(hsv);
            float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        }
    }
    return 0;
}

void rgb_matrix_indicators_user(void) {
    if (g_suspend_state || disable_layer_color ||
        rgb_matrix_get_flags() == LED_FLAG_NONE ||
        rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
            return;
        }
    set_layer_color(get_highest_layer(layer_state));
}

uint32_t layer_state_set_user(uint32_t state) {
    set_layer_color(get_highest_layer(layer_state));
    return state;
}
