#include <stdint.h>
static const uint8_t MENU_TYPE_DEFAULT        = 0; // if no type is specified, give a warning, and be an ordered list
static const uint8_t MENU_TYPE_ORDERED_LIST   = 1;
static const uint8_t MENU_TYPE_UNORDERED_LIST = 2;
static const uint8_t MENU_TYPE_RADIO_BUTTONS  = 3;
typedef struct {
	uint8_t id;
	uint8_t numChoices;
	/*
		Can be any of the types in the menu types enum
	*/
	uint8_t type;
	char title[32];
	struct {
		char name[32];
		void (*handler)();
	} options[10];
	uint8_t selected;
	uint8_t radioPressed;
} menu_t;
menu_t *makeMenu();
void drawMenu(const menu_t *menu);
void *handleMenu(menu_t *menu);
void initMenu(menu_t *menu);