AUTOMAKE_OPTIONS = foreign
if MINGW
AM_LDFLAGS = -lmingw32 -lSDL2main
endif
noinst_PROGRAMS = example_text
example_text_SOURCES = src/main.cpp src/state_main.cpp src/state_main.h
example_text_CPPFLAGS="-I../../src"
example_text_LDADD = ../../libchomp.a