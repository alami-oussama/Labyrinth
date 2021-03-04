all: app

app:
	gcc src/*.c -o application `sdl2-config --cflags --libs`