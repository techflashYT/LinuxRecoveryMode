#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <menu.h>
void terminalRawMode();
void __defaultMenuHandler() {
	printf(
		"\x1b[1;1H\x1b[2J\x1b[31m"
		"Uh oh!  It looks like you found a bug in the program!\r\n"
		"\x1b[0mNot to worry though.\r\n"
		"\x1b[1;39mReport the following information to Techflash at \x1b[0m\x1b[4;36mhttps://github.com/techflashYT/LinuxRecoveryMode!\x1b[0m\r\n"
		""
	);
}
void automaticRepairHandler() {
	menu_t *menu = makeMenu();

	initMenu(menu);
	menu->type = MENU_TYPE_RADIO_BUTTONS;
	strcpy(menu->title, "Please select your disk");
	strcpy(menu->options[0].name, "/dev/sda1");
	strcpy(menu->options[1].name, "/dev/sda2");
	strcpy(menu->options[2].name, "/dev/sda3");

	drawMenu(menu);
	uint8_t selectedOpt = (uint8_t)((uint64_t)handleMenu(menu)); // we're using a uint8_t here since for radio button menus, it doesn't return the handler, it just returns the number of the selected option.

	printf("selected option: %u\r\n", selectedOpt);
	sleep(1);
}
void memtest86plusHandler() {
	printf("\x1b[1;1H\x1b[2JPlease reboot and select the `Memtest86+\' option from the GRUB menu to use this!\r\n");
	system("sync");
	printf("\x1b[31mSystem Halted.\x1b[0m\r\n");
	system("echo \"c\" > /proc/sysrq-trigger");
	sleep(1);
}
void dropToShellHandler() {
	// we don't care about the return value, we're just using it to execute a shell.
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
	system("/bin/bash");
	#pragma GCC diagnostic pop
	// now that the shell is done, we need to reset the terminal to the mode we set it to at the start of the app
	terminalRawMode();
}
