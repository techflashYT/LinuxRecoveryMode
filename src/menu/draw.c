#include <menu.h>
#include <stdint.h>
#include <stdio.h>
void initMenuPart2(menu_t *menu);
void drawMenu(const menu_t *menu) {
	// has this menu been ran before?
	if (menu->numChoices == 0) {
		// no, finish initialization now that we've set the options
		initMenuPart2((menu_t *)menu);
	}
	// clear screen
	printf("\x1b[1;1H\x1b[2J");
	// print title
	printf("%s\r\n", menu->title);
	
	for (uint8_t i = 0; i != menu->numChoices; i++) {
		if (i == menu->selected) {
			printf("\x1b[2;4;30m");
		}
		printf("  %d: %s\x1b[0m\r\n", i + 1, menu->options[i].name);
	}
}