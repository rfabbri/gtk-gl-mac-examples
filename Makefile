all: version simple gl gt

version:version.c
	 gcc -o version version.c `pkg-config --libs --cflags gtk+-2.0`

simple:simple.c
	 gcc -o simple simple.c `pkg-config --libs --cflags gtk+-2.0`

gl:gl.c
	 gcc -o gl gl.c `pkg-config --libs --cflags gtk+-2.0 gtkglext-1.0`
	 
# Test - this may not compile.
gt:gt.c
	gcc -o gt gt.c `pkg-config --libs --cflags gtk+-2.0 gtkglext-1.0`
