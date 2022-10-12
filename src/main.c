#include <menu.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>	//termios, TCSANOW, ECHO, ICANON
#include <unistd.h>		//STDIN_FILENO
#include <stdbool.h>
void handler0();
void handler1();
void handler2();
int main() {
	// Set terminal output to default
	printf("\x1b[0m");
	static struct termios oldt, newt;
	// Get attributes of current term
	tcgetattr(STDIN_FILENO, &oldt);

	newt = oldt;
	// Disable ICANON
	newt.c_lflag &= ~(ICANON);
	// Apply
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	menu_t *menu = makeMenu();
	strcpy(menu->title, "Title");
	menu->numChoices = 3;
	strcpy(menu->options[0].name, "This is an example menu option");
	menu->options[0].handler = handler0;
	strcpy(menu->options[1].name, "This is an example menu option 2");
	menu->options[1].handler = handler1;
	strcpy(menu->options[2].name, "This is an example menu option 3");
	menu->options[2].handler = handler2;
	drawMenu(menu);
	handleMenu(menu);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}