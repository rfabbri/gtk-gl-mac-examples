all: version simple gl gl-cxx#  gl-apple gt gl-apple-cxx


# GCC Toolchain - works out of the box -----------------------------

version:version.c
	 gcc -o version version.c `pkg-config --libs --cflags gtk+-2.0`

simple:simple.c
	 gcc -o simple simple.c `pkg-config --libs --cflags gtk+-2.0`

gl:gl.c
	 gcc -o gl gl.c `pkg-config --libs --cflags gtk+-2.0 gtkglext-1.0`

# G++ requires tweaks
gl-cxx:gl.cxx
	 gcc -o gl-cxx gl.cxx `pkg-config --libs --cflags gtk+-2.0 gtkglext-1.0`

# Apple toolchain -------------------------------------------------

# Works fine - just change GL/gl.h to gl.h and add the -I flag
gl-apple:gl-apple.c
	 cc -o gl-apple gl-apple.c `pkg-config --libs --cflags gtk+-2.0 gtkglext-1.0` -I /System/Library/Frameworks/OpenGL.framework/Headers

# Spews error
gl-apple-cxx:gl-apple.cxx
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ -o gl-apple-cxx gl-apple.cxx `pkg-config --libs --cflags gtk+-2.0 gtkglext-1.0` -I /System/Library/Frameworks/OpenGL.framework/Headers

# Test - this may not compile.
gt:gt.cxx
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ -o gt gt.cxx `pkg-config --libs --cflags gtk+-2.0 gtkglext-1.0` -I /System/Library/Frameworks/OpenGL.framework/Headers
