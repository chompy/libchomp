AUTOMAKE_OPTIONS = foreign
if MINGW
AM_LDFLAGS = -lmingw32 -lSDL2main
endif
noinst_PROGRAMS = example_chompy
example_chompy_SOURCES = src/main.cpp src/state_chompy.cpp src/state_chompy.h
example_chompy_CPPFLAGS="-I../../src"
example_chompy_LDADD = ../../libchomp.a