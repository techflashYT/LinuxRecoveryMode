#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void terminalRawMode();
void automaticRepairHandler() {
	printf("\r\nhandler 0\r\n");
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
