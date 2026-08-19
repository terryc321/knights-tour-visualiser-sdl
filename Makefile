
CC=gcc

# removed  sdl12_compat from both CFLAGS and CLIBS
CFLAGS=`pkg-config --cflags sdl2 SDL2_image SDL2_mixer SDL2_ttf`
CLIBS=`pkg-config --libs sdl2 SDL2_image SDL2_mixer SDL2_ttf`

#-Werror -Wfatal-errors ?
hello: tour.c
	$(CC) -Wall -O3 -o tour tour.c $(CFLAGS) $(CLIBS)

