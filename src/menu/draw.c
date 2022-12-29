#include <menu.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void initMenuPart2(menu_t *menu);
void __drawOrderedList(const menu_t *menu) {
	char *buffer = malloc(16);
	for (uint8_t i = 0; i != menu->numChoices; i++) {
		buffer[0] = '\0';
		if (i == menu->selected) {
			strcpy(buffer, "\x1b[2;4;30m");
		}
		printf("  %s%d: %s\x1b[0m\r\n", buffer, i + 1, menu->options[i].name);
	}
}
void __drawUnorderedList(const menu_t *menu) {
	char *buffer = malloc(16);
	for (uint8_t i = 0; i != menu->numChoices; i++) {
		buffer[0] = '\0';
		if (i == menu->selected) {
			strcpy(buffer, "\x1b[2;4;30m");
		}
		printf("  %s%c: %s\x1b[0m\r\n", buffer, 0xBA, menu->options[i].name);
	}
	free(buffer);
}
void __drawRadioButtons(const menu_t *menu) {
	char *buffer = malloc(256);
	for (uint8_t i = 0; i != menu->numChoices; i++) {
		buffer[0] = '\0';
		printf("  ");
		if (i == menu->selected) {
			printf("\r\x1b[1;36m>\x1b[0m ");
			strcpy(buffer, "\x1b[2;4;30m");
		}
		strcpy(buffer + strlen(buffer), menu->options[i].name);
		printf("[%s] %s\x1b[0m\r\n", (menu->radioPressed == i) ? "\x1b[1;33m*\x1b[0m" : " ", buffer);
	}
	free(buffer);
}
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
	if (menu->type == 0) {
		// no type, we forgot to set
		fprintf(stderr, "\x1b[1;33mWARNING\x1b[0m: Menu has no type, assuming ordered list.\r\n");
		__drawOrderedList(menu);
	}
	else if (menu->type == 1) {
		// ordered list
		__drawOrderedList(menu);
	}
	else if (menu->type == 2) {
		// unordered list
		__drawUnorderedList(menu);
	}
	else if (menu->type == 3) {
		// radio buttons
		__drawRadioButtons(menu);
	}
}