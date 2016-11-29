AUTOMAKE_OPTIONS = foreign
noinst_LIBRARIES = libchomp.a
libchomp_a_SOURCES = src/chomp.cpp src/chomp.h src/state.cpp src/state.h src/asset/asset.cpp src/asset/asset.h src/asset/bitmap.cpp src/asset/bitmap.h src/asset/config.cpp src/asset/config.h src/exception/exception.cpp src/exception/exception.h src/exception/sdl_exception.h src/exception/sdl_mixer_exception.h src/exception/sdl_ttf_exception.h src/exception/asset_exception.h src/gfx/gfx.cpp src/gfx/gfx.h src/gfx/layer.cpp src/gfx/layer.h src/gfx/sprite.cpp src/gfx/sprite.h src/gfx/text.cpp src/gfx/text.cpp src/gfx/structs.h src/input/input.cpp src/input/input.h src/input/gamepad.cpp src/input/gamepad.h src/input/mouse.cpp src/input/mouse.h src/input/keyboard.cpp src/input/keyboard.h src/sfx/sfx.cpp src/sfx/sfx.h src/sdl_includes.h src/core.h
libchomp_a_LIBADD = $(LIBOBJS) $(ALLOCA)

noinst_PROGRAMS = example_gamepad
example_gamepad_SOURCES = examples/gamepad/src/main.cpp examples/gamepad/src/state_main.cpp examples/gamepad/src/state_main.h
example_gamepad_LDFLAGS = -static
example_gamepad_LDADD = libchomp.a