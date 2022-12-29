#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <menu.h>
uint8_t input = 0;
bool __handleArrows(uint8_t input, menu_t *menu);
void *handleMenu(menu_t *menu) {
	// get input, and check if it's q.  if it is, exit
	while ((input = getchar()) != 'q') {
		// user *probably* pressed an arrow key
		if (__handleArrows(input, menu)) {
			goto end;
		}
		// space
		if (input == ' ') {
			// is this a radio menu?
			if (menu->type == MENU_TYPE_RADIO_BUTTONS) {
				// yes, activate that button
				menu->radioPressed = menu->selected;
				goto end;
			}
			// no, return the handler (don't bother worrying about the selected option stuff below, since we know it isn't a radio menu)
			return menu->options[menu->selected].handler;
		}
		// Enter
		if (input == '\n') {
			// user pressed enter, return the handler of the selected item.
			if (menu->type == MENU_TYPE_RADIO_BUTTONS) {
				// special case: radio buttons, return the selected option
				return (void *)((uint64_t)(menu->selected));
			}
			return menu->options[menu->selected].handler;
		}
		end:
			drawMenu(menu);
			// printf("character: %d", input);
	}
	return NULL; // null indicates that we should go back
}
bool __handleArrows(uint8_t input, menu_t *menu) {
	if (input != 27) {
		return false;
	}
	input = getchar();
	if (input != 91) {
		return false;
	}
	// user definitely pressed an arrow key
	// which arrow key?
	input = getchar();
	// up arrow
	if (input == 65) {
		// are we already on the top most item?  if so, don't try to set the selected item higher up.
		if (menu->selected != 0) {
			// nope, set it to the next highest
			menu->selected--;
		}
		return true;
	}
	// down arrow
	else if (input == 66) {
		// are we already on the bottom most item?  if so, don't try to set the selected item lower down.
		if (menu->selected != menu->numChoices - 1) {
			// nope, set it to the next lowest
			menu->selected++;
		}
		return true;
	}
	else {
		// wtf?  junk, not an arrow key, return false
		return false;
	}
}