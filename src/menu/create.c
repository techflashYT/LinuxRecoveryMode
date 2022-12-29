#include <menu.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
menu_t *makeMenu() {
	menu_t *retVal = malloc(sizeof(menu_t));
	return retVal;
}
void initMenu(menu_t *menu) {
	// zero out the uninitialized memory that makeMenu gave us.
	memset(menu, 0, sizeof(menu_t));
}
void initMenuPart2(menu_t *menu) {
	// calculate the number of choices selected
	uint8_t choices = 0;
	while (menu->options[choices].name[0] != '\0') {
		choices++;
	}
	menu->numChoices = choices;
}