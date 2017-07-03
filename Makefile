all: version simple gl

version:version.c
	 gcc -o version version.c `pkg-config --libs --cflags gtk+-2.0`

simple:simple.c
	 gcc -o simple simple.c `pkg-config --libs --cflags gtk+-2.0`

gl:gl.c
	 gcc -o gl gl.c `pkg-config --libs --cflags gtk+-2.0 gtkglext-1.0`
