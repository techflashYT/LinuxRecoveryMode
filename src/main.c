#include <menu.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>	//termios, TCSANOW, ECHO, ICANON
#include <unistd.h>		//STDIN_FILENO
#include <stdbool.h>
uint8_t input = 0;
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
	while ((input = getchar()) != 'q') {
		// Arrow key
		if (input == 27) {
			input = getchar();
			if (input == 91) {
				input = getchar();
				if (input == 65) {
					if (menu->selected != 0) {
						menu->selected--;
					}
				}
				else if (input == 66) {
					if (menu->selected != menu->numChoices - 1) {
						menu->selected++;
					}
				}
			}
		}
		// Enter
		else if (input == '\n') {
			menu->options[menu->selected].handler();
		}
		drawMenu(menu);
		printf("character: %d", input);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}