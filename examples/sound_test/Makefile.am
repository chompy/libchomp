AUTOMAKE_OPTIONS = foreign
if MINGW
AM_LDFLAGS = -lmingw32 -lSDL2main
endif
noinst_PROGRAMS = example_sound_test
example_sound_test_SOURCES = src/main.cpp src/state_main.cpp src/state_main.h
example_sound_test_CPPFLAGS="-I../../src"
example_sound_test_LDADD = ../../libchomp.a