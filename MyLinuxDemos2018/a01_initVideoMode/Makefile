CC=gcc
#AR=$(CC) ar
#CFLAGS= `sdl-config --cflags --libs`
CFLAGS = -I/usr/include/SDL -L/usr/lib/x86_64-linux-gnu -lSDL

a01_initVideoMode: a01_initVideoMode.cpp
	$(CC)  $^ $(CFLAGS)  -o $@

clean:
	-rm -f $(EXEC) *.elf *.gdb *.o
	