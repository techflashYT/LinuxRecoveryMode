#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <menu.h>
uint8_t input = 0;
void *handleMenu(menu_t *menu) {
	// get input, and check if it's q, if it is, exit
	while ((input = getchar()) != 'q') {
		// user *probably* pressed an arrow key
		if (input == 27) {
			input = getchar();
			// user definitely pressed an arrow key
			if (input == 91) {
				// which arrow key?
				input = getchar();
				// up arrow
				if (input == 65) {
					// are we already on the top most item?  if so, don't try to set the selected item higher up.
					if (menu->selected != 0) {
						// nope, set it to the next highest
						menu->selected--;
					}
				}
				// down arrow
				else if (input == 66) {
					// are we already on the bottom most item?  if so, don't try to set the selected item lower down.
					if (menu->selected != menu->numChoices - 1) {
						// nope, set it to the next lowest
						menu->selected++;
					}
				}
			}
		}
		// Enter
		else if (input == '\n') {
			// user pressed enter, return the handler of the selected item.
			return menu->options[menu->selected].handler;
		}
		drawMenu(menu);
		// printf("character: %d", input);
	}
	return NULL; // null indicates that we should go back
}