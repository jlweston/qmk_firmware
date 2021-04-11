#include "quantum.h"
#include "td_setup.h"

enum tap_dancers {
    TD_GRAVE,
    _TD_F1,
    _TD_F2,
    _TD_F3,
    _TD_F4,
    _TD_F5,
    _TD_F6,
    _TD_F7,
    _TD_F8,
    _TD_F9,
    _TD_F10,
    _TD_F11,
    _TD_F12,
    _TD_LAYER,
};

#define TD_F1    TD(_TD_F1)
#define TD_F2    TD(_TD_F2)
#define TD_F3    TD(_TD_F3)
#define TD_F4    TD(_TD_F4)
#define TD_F5    TD(_TD_F5)
#define TD_F6    TD(_TD_F6)
#define TD_F7    TD(_TD_F7)
#define TD_F8    TD(_TD_F8)
#define TD_F9    TD(_TD_F9)
#define TD_F10   TD(_TD_F10)
#define TD_F11   TD(_TD_F11)
#define TD_F12   TD(_TD_F12)
#define TD_LAYER TD(_TD_LAYER)

td_state_t cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted) {
      return SINGLE_TAP;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if ((state->count == 3) && ((state->interrupted) || (!state->pressed))) return TRIPLE_TAP;
  else if (state->count == 3) return TRIPLE_HOLD;
  else return SPECIAL;
}

td_state_t hold_cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted) {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (!state->pressed) return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return SPECIAL;
}

static td_tap_t tap_state = {
    .is_press_action = true,
    .state = 0
};

void tap_dance_grave_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  switch (tap_state.state) {
    case SINGLE_TAP:
      register_code(KC_ESC);
      break;
    case SINGLE_HOLD:
      SEND_STRING("`");
      break;
    case DOUBLE_TAP:
      SEND_STRING("~");
      break;
    case DOUBLE_HOLD ... SPECIAL:
      break;
  }
}

void tap_dance_grave_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    SEND_STRING("```");
  } else if (state->count > 3) {
    SEND_STRING("`");
  }
}

void tap_dance_grave_reset(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  switch (tap_state.state) {
    case SINGLE_TAP:
      unregister_code(KC_ESC);
    case SINGLE_HOLD ... SPECIAL:
      break;
  }
}

void tap_dance_f1_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == SINGLE_TAP) {
      SEND_STRING("1");
  }
  if (tap_state.state == SINGLE_HOLD) {
      SEND_STRING("!");
  }
}

void tap_dance_f1_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    register_code(KC_F1);
  }
}

void tap_dance_f1_reset(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == DOUBLE_TAP) {
      unregister_code(KC_F1);
  }
}

void tap_dance_f2_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == SINGLE_TAP) {
      SEND_STRING("2");
  }
  if (tap_state.state == SINGLE_HOLD) {
      SEND_STRING("@");
  }
}

void tap_dance_f2_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    register_code(KC_F2);
  }
}

void tap_dance_f2_reset(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == DOUBLE_TAP) {
      unregister_code(KC_F2);
  }
}

void tap_dance_f3_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == SINGLE_TAP) {
      SEND_STRING("3");
  }
  if (tap_state.state == SINGLE_HOLD) {
      SEND_STRING("#");
  }
}

void tap_dance_f3_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    register_code(KC_F3);
  }
}

void tap_dance_f3_reset(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == DOUBLE_TAP) {
      unregister_code(KC_F3);
  }
}

void tap_dance_f4_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == SINGLE_TAP) {
      SEND_STRING("4");
  }
  if (tap_state.state == SINGLE_HOLD) {
      SEND_STRING("$");
  }
}

void tap_dance_f4_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    register_code(KC_F4);
  }
}

void tap_dance_f4_reset(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == DOUBLE_TAP) {
      unregister_code(KC_F4);
  }
}

void tap_dance_f5_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == SINGLE_TAP) {
      SEND_STRING("5");
  }
  if (tap_state.state == SINGLE_HOLD) {
      SEND_STRING("%");
  }
}

void tap_dance_f5_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    register_code(KC_F5);
  }
}

void tap_dance_f5_reset(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == DOUBLE_TAP) {
      unregister_code(KC_F5);
  }
}

void tap_dance_f6_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == SINGLE_TAP) {
      SEND_STRING("6");
  }
  if (tap_state.state == SINGLE_HOLD) {
      SEND_STRING("^");
  }
}

void tap_dance_f6_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    register_code(KC_F6);
  }
}

void tap_dance_f6_reset(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == DOUBLE_TAP) {
      unregister_code(KC_F6);
  }
}

void tap_dance_f7_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == SINGLE_TAP) {
      SEND_STRING("7");
  }
  if (tap_state.state == SINGLE_HOLD) {
      SEND_STRING("&");
  }
}

void tap_dance_f7_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    register_code(KC_F7);
  }
}

void tap_dance_f7_reset(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == DOUBLE_TAP) {
      unregister_code(KC_F7);
  }
}

void tap_dance_f8_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == SINGLE_TAP) {
      SEND_STRING("8");
  }
  if (tap_state.state == SINGLE_HOLD) {
      SEND_STRING("*");
  }
}

void tap_dance_f8_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    register_code(KC_F8);
  }
}

void tap_dance_f8_reset(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == DOUBLE_TAP) {
      unregister_code(KC_F8);
  }
}

void tap_dance_f9_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == SINGLE_TAP) {
      SEND_STRING("9");
  }
  if (tap_state.state == SINGLE_HOLD) {
      SEND_STRING("(");
  }
}

void tap_dance_f9_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    register_code(KC_F9);
  }
}

void tap_dance_f9_reset(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == DOUBLE_TAP) {
      unregister_code(KC_F9);
  }
}

void tap_dance_f10_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == SINGLE_TAP) {
      SEND_STRING("0");
  }
  if (tap_state.state == SINGLE_HOLD) {
      SEND_STRING(")");
  }
}

void tap_dance_f10_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    register_code(KC_F10);
  }
}

void tap_dance_f10_reset(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == DOUBLE_TAP) {
      unregister_code(KC_F10);
  }
}

void tap_dance_f11_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == SINGLE_TAP) {
      SEND_STRING("-");
  }
  if (tap_state.state == SINGLE_HOLD) {
      SEND_STRING("_");
  }
}

void tap_dance_f11_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    register_code(KC_F11);
  }
}

void tap_dance_f11_reset(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == DOUBLE_TAP) {
      unregister_code(KC_F11);
  }
}

void tap_dance_f12_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == SINGLE_TAP) {
      SEND_STRING("=");
  }
  if (tap_state.state == SINGLE_HOLD) {
      SEND_STRING("+");
  }
}

void tap_dance_f12_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    register_code(KC_F12);
  }
}

void tap_dance_f12_reset(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  if (tap_state.state == DOUBLE_TAP) {
      unregister_code(KC_F12);
  }
}

void tap_dance_layer_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = hold_cur_dance(state);
    if (tap_state.state == SINGLE_TAP) {
        if (layer_state_is(_GAMING)) {
            layer_off(_GAMING);
        } else if (layer_state_is(_LIGHTS_MEDIA)) {
            layer_off(_LIGHTS_MEDIA);
        } else if (layer_state_is(_WINDOWS)) {
            layer_move(_MAC);
        } else {
            layer_move(_WINDOWS);
        }
        autoshift_enable();
    }
    if (tap_state.state == SINGLE_HOLD) {
        autoshift_disable();
        layer_on(_LIGHTS_MEDIA);
    }
    if (tap_state.state == DOUBLE_TAP) {
        autoshift_toggle(); // Disable autoshift while gaming
        layer_invert(_GAMING);
    }
}

void tap_dance_layer_each(qk_tap_dance_state_t *state, void *user_data) {
}

void tap_dance_layer_reset(qk_tap_dance_state_t *state, void *user_data) {
    // tap_state.state = hold_cur_dance(state);
    if (tap_state.state == SINGLE_HOLD) {
        layer_off(_LIGHTS_MEDIA);
        autoshift_enable();
    }
    tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_GRAVE]  = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_grave_each, tap_dance_grave_finished, tap_dance_grave_reset),
    [_TD_F1]    = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_f1_each,    tap_dance_f1_finished,    tap_dance_f1_reset),
    [_TD_F2]    = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_f2_each,    tap_dance_f2_finished,    tap_dance_f2_reset),
    [_TD_F3]    = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_f3_each,    tap_dance_f3_finished,    tap_dance_f3_reset),
    [_TD_F4]    = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_f4_each,    tap_dance_f4_finished,    tap_dance_f4_reset),
    [_TD_F5]    = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_f5_each,    tap_dance_f5_finished,    tap_dance_f5_reset),
    [_TD_F6]    = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_f6_each,    tap_dance_f6_finished,    tap_dance_f6_reset),
    [_TD_F7]    = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_f7_each,    tap_dance_f7_finished,    tap_dance_f7_reset),
    [_TD_F8]    = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_f8_each,    tap_dance_f8_finished,    tap_dance_f8_reset),
    [_TD_F9]    = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_f9_each,    tap_dance_f9_finished,    tap_dance_f9_reset),
    [_TD_F10]   = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_f10_each,   tap_dance_f10_finished,   tap_dance_f10_reset),
    [_TD_F11]   = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_f11_each,   tap_dance_f11_finished,   tap_dance_f11_reset),
    [_TD_F12]   = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_f12_each,   tap_dance_f12_finished,   tap_dance_f12_reset),
    [_TD_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,                 tap_dance_layer_finished, tap_dance_layer_reset),
};
