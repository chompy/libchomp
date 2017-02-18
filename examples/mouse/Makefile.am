AUTOMAKE_OPTIONS = foreign
if MINGW
AM_LDFLAGS = -lmingw32 -lSDL2main
endif
noinst_PROGRAMS = example_mouse
example_mouse_SOURCES = src/main.cpp src/state_main.cpp src/state_main.h
example_mouse_CPPFLAGS="-I../../src"
example_mouse_LDADD = ../../libchomp.a