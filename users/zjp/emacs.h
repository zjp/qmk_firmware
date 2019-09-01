#pragma once

enum emacs_keycodes {
	// All lists of keys in this file follow the same order in enums, defines, etc
	//----------------------------------EMACS-DEFAULTS------------------------------------
	//KC--|--------Action----------|-----Macro-----|------------Emacs Function------------
	JUMP, // Jump to line          | M-g M-g       | goto-line
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
	//-------------------------PACKAGE SPECIFIC MACROS (BUILT-IN)-------------------------
	// These are for libraries that are technically packages, but which nevertheless do
	// ship with emacs (e.g Org mode)
	//KC--|------Action----------------Macro--------Package------------Function-----------
	LTEX, // Export Org to LaTeX   | C-c C-e l p   | org-export-dispatch w/ args
};

/* Defines for keymap macros that include KC_ implicitly */
#ifdef KC_ABBREVS_MODE
#define KC_JUMP JUMP
#define KC_DLIN DLIN
#define KC_SAVE SAVE
#define KC_EWTF WTF
#define KC_EVF  EVF
#define KC_EHPW EHPB
#define KC_EVPW EVPB
#define KC_CBUF CBUF
#define KC_KBUF KBUF
#define KC_ERRX ERRX
#define KC_EBTF EBTF
#define KC_HELP HELP

#define KC_LTEX LTEX
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

void emacs_describe_key() {
	SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_H) SS_UP(X_LCTRL) SS_TAP(X_K));
}

void emacs_org_export_latex() {
	SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_C) SS_TAP(X_E)
				SS_UP(X_LCTRL) SS_TAP(X_L) SS_TAP(X_P));
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
