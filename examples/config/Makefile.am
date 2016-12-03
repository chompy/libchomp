AUTOMAKE_OPTIONS = foreign
if MINGW
AM_LDFLAGS = -lmingw32 -lSDL2main
endif
noinst_PROGRAMS = example_config
example_config_SOURCES = src/main.cpp
example_config_CPPFLAGS="-I../../src"
example_config_LDADD = ../../libchomp.a