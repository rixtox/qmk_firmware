#include "planck.h"
#include "backlight.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _CM 1
#define OSU 2
#define _NB 3
#define _LW 4
#define _RS 5

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QW] = { /* Qwerty */
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {KC_LCTL, KC_LCTL, KC_LALT, KC_LGUI, MO(_LW), KC_SPC,  KC_SPC,  MO(_RS), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},
[_CM] = { /* Colemak */
  {KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC},
  {KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {KC_LCTL, KC_LCTL, KC_LALT, KC_LGUI, MO(_LW), KC_SPC,  KC_SPC,  MO(_RS), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},
[OSU] = { /* osu! */
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {M(2),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {M(0),    M(1),    M(1),    M(1),    KC_C,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP  , KC_ENT },
  {KC_NO,   KC_NO,   KC_NO,   KC_SPC , KC_SPC , KC_SPC,  KC_SPC,  MO(_RS), KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT}
},
[_NB] = { /* NUMBERS */
  {KC_BSPC, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PLUS, KC_7,    KC_8,    KC_9   },
  {KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MINS, KC_4,    KC_5,    KC_6   },
  {KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_ASTR, KC_1,    KC_2,    KC_3   },
  {KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   MO(_RS), KC_BSLS, KC_DOT,  KC_0,    KC_ENT }
},
[_RS] = { /* RAISE */
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL },
  {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  DF(_QW), DF(_CM), DF(OSU), RESET,   KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DF(_NB), DF(_NB), KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},
[_LW] = { /* LOWER */
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL },
  {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
  {KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  DF(_QW), DF(_CM), DF(OSU), RESET,   KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
}
};

const uint16_t PROGMEM fn_actions[] = {

};

int trigger_keys_enabled = 0;
int trigger_once_enabled = 0;

const int key_count = 2;
const int key_codes[] = {KC_Z, KC_X};
int current_key = -1;

void trigger_key() {
  int previous_key = current_key;
  if (++current_key >= key_count)
    current_key = 0;
  register_code(key_codes[current_key]);
  if (previous_key >= 0) {
    unregister_code(key_codes[previous_key]);
  }
}

void clear_trigger_keys() {
  if (current_key >= 0) {
    unregister_code(key_codes[current_key]);
    current_key = -1;
  }
}

void trigger_loop() {
  if (trigger_keys_enabled) {
    if (!trigger_once_enabled)
      trigger_key();
  } else if (!trigger_once_enabled)
    clear_trigger_keys();
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        trigger_keys_enabled = 1;
      } else {
        trigger_keys_enabled = 0;
      }
      break;
    case 1:
      if (record->event.pressed) {
        trigger_once_enabled++;
        trigger_key();
      } else {
        trigger_once_enabled--;
        if (!trigger_once_enabled)
          clear_trigger_keys();
      }
      break;
    case 2:
      if (record->event.pressed) {
        register_code(KC_SLSH);
        unregister_code(KC_SLSH);
        register_code(KC_N);
        unregister_code(KC_N);
        register_code(KC_P);
        unregister_code(KC_P);
        register_code(KC_ENT);
        unregister_code(KC_ENT);
      }
      break;
  }
  return MACRO_NONE;
};
