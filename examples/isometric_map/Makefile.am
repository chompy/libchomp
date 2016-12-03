AUTOMAKE_OPTIONS = foreign
if MINGW
AM_LDFLAGS = -lmingw32 -lSDL2main
endif
noinst_PROGRAMS = example_isometric_map
example_isometric_map_SOURCES = src/main.cpp src/state_main.cpp src/state_main.h
example_isometric_map_CPPFLAGS="-I../../src"
example_isometric_map_LDADD = ../../libchomp.a