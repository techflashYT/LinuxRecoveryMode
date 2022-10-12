#include <stdint.h>
typedef struct {
	uint8_t id;
	uint8_t numChoices;
	char *title;
	struct {
		char* name;
		void (*handler)();
	} options[10];
	uint8_t selected;
} menu_t;
menu_t *makeMenu();
void drawMenu(const menu_t *menu);
void handleMenu(menu_t *menu);