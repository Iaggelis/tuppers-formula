PKGS=sdl2 SDL2_gfx mpfr
CFLAGS=-Wall -Wold-style-definition -ggdb -std=c11 -pedantic `pkg-config --cflags $(PKGS)`
LIBS=`pkg-config --libs $(PKGS)`

tupper: $(wildcard src/*)
	$(CC) $(CFLAGS) -o tupper src/tupper.c $(LIBS)
