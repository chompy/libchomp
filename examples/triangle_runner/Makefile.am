AUTOMAKE_OPTIONS = foreign
if MINGW
AM_LDFLAGS = -lmingw32 -lSDL2main
endif
noinst_PROGRAMS = example_gamepad
example_gamepad_SOURCES = src/main.cpp src/state_main.cpp src/state_main.h
example_gamepad_CPPFLAGS="-I../../src"
example_gamepad_LDADD = ../../libchomp.a