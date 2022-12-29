#include <stdint.h>
typedef struct {
	uint8_t id;
	uint8_t numChoices;
	char title[32];
	struct {
		char name[32];
		void (*handler)();
	} options[10];
	uint8_t selected;
} menu_t;
menu_t *makeMenu();
void drawMenu(const menu_t *menu);
void *handleMenu(menu_t *menu);
void initMenu(menu_t *menu);