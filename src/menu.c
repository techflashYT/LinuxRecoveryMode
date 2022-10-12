#include <stdio.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>
void menuDraw();
menu_t *makeMenu() {
	menu_t *retVal = malloc(sizeof(menu_t));
	memset(retVal, 0, sizeof(menu_t));
	retVal->title   = malloc(32);
	for (uint8_t i = 0; i != 10; i++) {
		retVal->options[i].name = malloc(32);
	}
	return retVal;
}
void drawMenu(const menu_t *menu) {
	printf("\e[1;1H\e[2J");
	printf("%s\r\n", menu->title);
	
	for (uint8_t i = 0; i != menu->numChoices; i++) {
		if (i == menu->selected) {
			printf("\x1b[2;4;30m");
		}
		printf("%d: %s\x1b[0m\r\n", i + 1, menu->options[i].name);
	}
}