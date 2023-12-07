/* Copyright 2023 jdwx
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

#include QMK_KEYBOARD_H

#include "features/sentence_case.h"


/* KEY LAYOUTS AND LAYERS */
enum layers {
    ALPH,
    FUNC,
};

// Left-hand home row mods
#define GUI_C LGUI_T(KC_C)
#define ALT_R LALT_T(KC_R)
#define SFT_S LSFT_T(KC_S)
#define CTRL_T LCTL_T(KC_T)

// Right-hand home row mods
#define CTL_N RCTL_T(KC_N)
#define SFT_E RSFT_T(KC_E)
#define ALT_I LALT_T(KC_I)
#define GUI_A RGUI_T(KC_A)

enum custom_keycodes {
    KC_TH = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [ALPH] = LAYOUT_60_hhkb(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,   KC_BSLS,
        KC_TAB,  KC_W,    KC_L,    KC_Y,    KC_P,    KC_K,    KC_Z,    KC_X,    KC_O,    KC_U,    KC_SCLN, KC_LBRC, KC_RBRC, KC_DELETE,
        KC_BSPC, GUI_C,   ALT_R,   SFT_S,   CTRL_T,  KC_B,    KC_F,    CTL_N,   SFT_E,   ALT_I,   GUI_A,   KC_QUOT,          KC_ENT,
                 KC_LSFT, KC_J,    KC_V,    KC_D,    KC_G,    KC_Q,    KC_M,    KC_H,    KC_SLSH, KC_COMM, KC_DOT,  KC_RSFT, MO(FUNC),
                          KC_LGUI, SC_LAPO,                                     KC_SPC,                    SC_RCPC, KC_RGUI
    ),
    // TODO: come up with aliases for the long keys to have this lay out better.
    [FUNC] = LAYOUT_60_hhkb(
        QK_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,             KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11, KC_F12,  KC_GRV, KC_DELETE,
        KC_TAB,  KC_PGDN, KC_PGUP, KC_HOME, KC_END,  KC_KB_VOLUME_UP,   KC_Z,    DT_PRNT, DT_UP,   DT_DOWN, KC_SCLN, KC_LBRC, KC_RBRC, KC_HYPR,
        KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_KB_MUTE,        KC_F,    KC_N,    KC_E,    KC_I,    KC_A,    KC_QUOT,          KC_ENT,
                 KC_LSFT, KC_CUT,  KC_COPY, KC_PSTE, KC_KB_VOLUME_DOWN, KC_Q,    KC_M,    KC_H,    KC_SLSH, KC_COMM, KC_DOT,  KC_RSFT, MO(FUNC),
                          KC_LGUI, KC_LALT,                                     KC_SPC,                              KC_RCTL, KC_RGUI
    ),
};


/* COMBOS */
enum combos {
    BACK_WORD,
    CAPS,
    QUESTION,
    TH,
    DOT,
};

const uint16_t PROGMEM back_word_combo[] = {KC_Y, KC_P, COMBO_END};
const uint16_t PROGMEM caps_combo[] = {KC_O, KC_X, COMBO_END};
const uint16_t PROGMEM question_combo[] = {KC_DOT, KC_COMM, COMBO_END};
const uint16_t PROGMEM th_combo[] = {GUI_C, CTRL_T, COMBO_END};
const uint16_t PROGMEM dot_combo[] = {ALT_R, SFT_S, COMBO_END};

combo_t key_combos[] = {
    [BACK_WORD] = COMBO(back_word_combo, C(KC_BSPC)),
    [CAPS] = COMBO(caps_combo, CW_TOGG),
    [QUESTION] = COMBO(question_combo, KC_QUES),
    [TH] = COMBO(th_combo, KC_TH),
    [DOT] = COMBO(dot_combo, KC_DOT),
};


/* CUSTOM HANDLING */
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_sentence_case(keycode, record)) { return false; }

    if (record->event.pressed) {
        switch (keycode) {
            case KC_TH:
                tap_code(KC_T);
                unregister_mods(MOD_MASK_SHIFT);
                tap_code(KC_H);
                return false;
        }
    }

    return true;
}

