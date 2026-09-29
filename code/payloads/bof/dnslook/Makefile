SRC = $(wildcard *.c)
OBJS = $(patsubst %.c, %.x64.o, $(SRC))
CC_x64 := x86_64-w64-mingw32-gcc
STRIP_x64 := x86_64-w64-mingw32-strip
CFLAGS := -I.. -fno-asynchronous-unwind-tables

.DELETE_ON_ERROR:
.PHONY: all clean

all: $(OBJS)

%.x64.o: %.c beacon.h Makefile
	$(CC_x64) $(CFLAGS) -o $@ -c $<
	$(STRIP_x64) --strip-unneeded $@

clean:
	rm -f $(OBJS)
