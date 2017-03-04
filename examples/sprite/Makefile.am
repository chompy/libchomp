AUTOMAKE_OPTIONS = foreign
if MINGW
AM_LDFLAGS = -lmingw32 -lSDL2main
endif
noinst_PROGRAMS = example_sprite
example_sprite_SOURCES = src/main.cpp src/state_main.cpp
example_sprite_CPPFLAGS="-I../../src"
example_sprite_LDADD = ../../libchomp.a