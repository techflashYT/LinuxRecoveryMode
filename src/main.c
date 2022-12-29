#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>	//termios, TCSANOW, ECHO, ICANON
#include <unistd.h>		//STDIN_FILENO
#include <stdbool.h>

#include <menu.h>
void automaticRepairHandler();
void memtest86plusHandler();
void dropToShellHandler();
struct termios oldt, newt;
// make this a function since we need to use it elsewhere
void terminalRawMode() {
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}
int main() {
	// Set terminal output to default
	printf("\x1b[0m");
	// Get attributes of current term
	tcgetattr(STDIN_FILENO, &oldt);

	newt = oldt;
	// Disable ICANON
	newt.c_lflag &= ~(ICANON);
	// Apply
	terminalRawMode();
	// main menu
	while (true) {
		menu_t *menu = makeMenu();
		initMenu(menu);
		strcpy(menu->title, "Linux Recovery Mode");
		strcpy(menu->options[0].name, "Automatic Repair");
		menu->options[0].handler = automaticRepairHandler;
		strcpy(menu->options[1].name, "Memory Diagnostic");
		menu->options[1].handler = memtest86plusHandler;
		strcpy(menu->options[2].name, "Shell for manual recovery");
		menu->options[2].handler = dropToShellHandler;
		drawMenu(menu);
		void *addr = handleMenu(menu);
		if (addr != NULL) {
			// tear down the menu, we're gonna call a handler.
			free(menu);
			// goofy casting shenanigans to call to address.
			((void (*)())addr)();
		}
		else {
			// address is NULL, user pressed q to quit.
			break;
		}
	}
	// quit
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return 0;
}