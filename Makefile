CC       = core2-gcc # yes I actually need a custom gcc for this because  all of my static libs are from gentoo, so they won't run on anything but my CPU
WARN     = -Wall -Wextra -Wstack-protector -Wformat=2 -Wformat-security
FEATURE  = -fdiagnostics-color=always -fstack-protector-all -march=core2
INCLUDES = -Isrc/include
GLIBCDIR = /opt/TechflashSoftware/crossCompiler/x86_64-linux/lib
CFLAGS   = $(WARN) $(FEATURE) $(INCLUDES) -Ofast -g -std=gnu2x -nostdlib -nostartfiles -static -L$(GLIBCDIR)
CRTFILES1= $(GLIBCDIR)/crt1.o $(GLIBCDIR)/crti.o `gcc --print-file-name=crtbegin.o`
CRTFILES2= `gcc --print-file-name=crtend.o` $(GLIBCDIR)/crtn.o
JUNKFLAG = -Wl,--start-group $(GLIBCDIR)/libc.a -lgcc -lgcc_eh -Wl,--end-group
# CRTFILES = /opt/TechflashSoftware/crossCompiler/x86_64-linux/lib/crt1.o /opt/TechflashSoftware/crossCompiler/x86_64-linux/lib/crti.o /opt/TechflashSoftware/crossCompiler/x86_64-linux/lib/crtn.o -l:libc.a -lgcc -lasan -lm
vpath %.c src
vpath %.c src/menu
vpath %.h src/include
SHELL=/bin/bash
compile := $(patsubst src/%.c,build/%.o,$(shell find src -name '*.c'))


outFileName=recovery

.SUFFIXES: .c .o
all: dirs bin/$(outFileName) iso
	@echo "Built!"

bin/$(outFileName): $(compile)
	$(CC) $(CFLAGS) $(CRTFILES1) $^ $(JUNKFLAG) $(CRTFILES2) -o $@


dirs:
	@$(shell mkdir -p bin build/menu)

build/%.o: %.c $(shell find src/include -type f)
	@echo "CC    $< => $@"
	@$(CC) $(CFLAGS) -c $< -o $@

iso: bin/$(outFileName)


clean:
	@rm -rf build bin
