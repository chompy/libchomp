AUTOMAKE_OPTIONS = foreign
if MINGW
AM_LDFLAGS = -lmingw32 -lSDL2main
endif
noinst_PROGRAMS = example_template
example_template_SOURCES = src/main.cpp src/state_main.cpp src/state_main.h
example_template_CPPFLAGS="-I../../src"
example_template_LDADD = ../../libchomp.a