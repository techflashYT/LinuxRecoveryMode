WARN   = -Wall -Wextra -Wstack-protector -Wformat=2 -Wformat-security
FEATURE= -fdiagnostics-color=always -fstack-protector-all
CFLAGS = $(WARN) $(FEATURE) -Isrc/include -Ofast -g -s -std=gnu2x

compile=\
src/main.o \
src/handler.o \
src/menu.o

link=\
build/main.o \
build/handler.o \
build/menu.o

outFileName=recovery

.SUFFIXES: .o .c

all: dirs $(compile)
	@gcc $(link) $(CFLAGS) -o bin/$(outFileName)
	@echo "Built!"


dirs:
	@$(shell mkdir -p bin build)

.c.o:
	@echo "CC    $(subst .o,.c,$@) => $(subst src,build,$@)"
	@gcc $(CFLAGS) -c $(subst .o,.c,$@) -o $(subst src,build,$@)

clean:
	@rm -f $(link)