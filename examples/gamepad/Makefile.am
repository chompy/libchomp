AUTOMAKE_OPTIONS = foreign
AM_LDFLAGS = -lmingw32 -lSDL2main
noinst_PROGRAMS = example_gamepad
example_gamepad_SOURCES = src/main.cpp src/state_main.cpp src/state_main.h
example_gamepad_CPPFLAGS="-I../../src"
example_gamepad_LDADD = ../../libchomp.a