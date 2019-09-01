#pragma once

enum emacs_keycodes {
    //----------------------------------EMACS-DEFAULTS------------------------------------
    //KC--|--------Action----------|-----Macro-----|------------Emacs Function------------
    JUMP, // Jump to line          | M-J           | goto-line
    DLIN, // Delete line           | C-backspace   | kill-whole-line
    SAVE, // Save file             | C-x C-s       | save-buffer
    EWTF, // Save as new file      | C-x C-w       | write-file
    EVF,  // Visit file            | C-x C-f       | find-file
    EHPW, // Split window vert.    | C-x 2         | split-window-below
    EVPW, // Split window horiz.   | C-x 3         | split-window-right
    CBUF, // Close buffer          | C-x 0         | delete-window
    KBUF, // Close file            | C-x k         | kill-buffer
    ERRX, // Replace w/ Regex      | C-M-%         | query-replace-regexp
    EBTF, // Pop buffer to Frame   | C-x 5 2       | make-frame-command
    HELP, // Describe Key          | C-h k         | describe-key
    NRTR, // Narrow to Region      | C-x n n       | narrow-to-region
    WIDN, // Widen                 | C-x n w       | widen
    //-------------------------PACKAGE-SPECIFIC-MACROS-(BUILT-IN)-------------------------
    // These are for libraries that are technically packages, but which nevertheless do
    // ship with emacs (e.g Org mode)
    //KC--|------Action----------------Macro--------Package------------Function-----------
    LTEX, // Export Org to LaTeX   | C-c C-e l p   | org-export-dispatch w/ args
    //-------------------------PACKAGE-SPECIFIC-MACROS-(EXTERNAL)-------------------------
    // These either depend on a package from MELPA that isn't distributed with Emacs (e.g.
    // you'll have to get it from MELPA or install it manually) or they call functions
    // that I wrote or bootlegged from other peoples' configs. You can find my dotfiles at
    // http://github.com/zjp
    //KC--|------Action----------------Macro----------------Package----------Function-----
    EMBL, // Move Buffer Left      | C-<shift>-left  | buffer-move      | buf-move-left
    EMBU, // Move Buffer Up        | C-<shift>-up    | buffer-move      | buf-move-up
    EMBD, // Move Buffer Down      | C-<shift>-up    | buffer-move      | buf-move-down
    EMBR, // Move Buffer Right     | C-<shift>-right | buffer-move      | buf-move-right
    EMCM, // Multiple Cursors Mode | C-C C-C         | multiple-cursors | mc/edit-lines
    EMCN, // MC Add @ Next Match   | C->             | multiple-cursors | mc/mark-next-like-this
    EMCP, // MC Add @ Prev Match   | C-<             | multiple-cursors | mc/mark-previous-like-this
    EMAC, // MC Mark on Click      |                 | multiple-cursors | mc/add-cursor-on-click
    EMS,  // Magit Status          | C-x g           | magit            | magit-status
};

/* Defines for keymap macros that include KC_ implicitly like the Iris */
#ifdef KC_ABBREVS_MODE
#define KC_JUMP LALT(LSFT(KC_J))
#define KC_DLIN LCTL(LSFT(KC_BSPC))
#define KC_SAVE SAVE
#define KC_EWTF WTF
#define KC_EVF  EVF
#define KC_EVPW EVPW
#define KC_EHPW EHPW
#define KC_CBUF CBUF
#define KC_KBUF KBUF
#define KC_ERRX ERRX
#define KC_LTEX LTEX
#define KC_EBTF EBTF
#define KC_EMBL EMBL
#define KC_EMBR EMBR
#define KC_EMBU EMBU
#define KC_EMBD EMBD
#define KC_EMCM EMCM
#define KC_EMS  EMS
#endif // KC_ABBREVS_MODE

void emacs_goto_line() {
    SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_G) SS_TAP(X_G) SS_UP(X_LALT));
}

void emacs_delete_line() {
    SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_BSPC) SS_UP(X_LCTRL));
}

void emacs_save_file() {
    SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_X) SS_TAP(X_S) SS_UP(X_LCTRL));
}

void emacs_find_file() {
    SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_X) SS_TAP(X_F) SS_UP(X_LCTRL));
}

void emacs_partition_vertical() {
    SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_X) SS_UP(X_LCTRL) SS_TAP(X_3));
}

void emacs_partition_horizontal() {
    SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_X) SS_UP(X_LCTRL) SS_TAP(X_2));
}

void emacs_close_buffer() {
    SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_X) SS_UP(X_LCTRL) SS_TAP(X_0));
}

void emacs_kill_buffer() {
    SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_X) SS_UP(X_LCTRL) SS_TAP(X_K));
}

void emacs_replace_regex() {
    SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT) SS_TAP(X_5)
                SS_UP(X_LSHIFT) SS_UP(X_LCTRL) SS_UP(X_LALT));
}

void emacs_org_export_latex() {
    SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_C) SS_TAP(X_E)
                SS_UP(X_LCTRL) SS_TAP(X_L) SS_TAP(X_P));
}

void emacs_describe_key() {
    SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_H) SS_UP(X_LCTRL) SS_TAP(X_K));
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
#ifdef KC_ABBREVS_MODE
        case JUMP:
            if (record->event.pressed) {
                emacs_goto_line();
            }
            break;
#endif //KC_ABBREVS_MODE
#ifndef KC_ABBREVS_MODE
        case KC_JUMP:
            if (record->event.pressed) {
                emacs_goto_line();
            }
            break;
#endif //KC_ABBREVS_MODE
    }
    return true;
}
