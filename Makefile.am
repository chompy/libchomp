AUTOMAKE_OPTIONS = foreign
noinst_LIBRARIES = libchomp.a
libchomp_a_SOURCES = src/chomp.cpp src/chomp.h src/state.cpp src/state.h src/asset/asset.cpp src/asset/asset.h src/asset/bitmap.cpp src/asset/bitmap.h src/asset/config.cpp src/asset/config.h src/exception/exception.cpp src/exception/exception.h src/exception/sdl_exception.h src/exception/sdl_mixer_exception.h src/exception/sdl_ttf_exception.h src/exception/asset_exception.h src/gfx/gfx.cpp src/gfx/gfx.h src/gfx/layer.cpp src/gfx/layer.h src/gfx/sprite.cpp src/gfx/sprite.h src/gfx/text.cpp src/gfx/text.cpp src/gfx/structs.h src/input/input.cpp src/input/input.h src/input/gamepad.cpp src/input/gamepad.h src/input/mouse.cpp src/input/mouse.h src/input/keyboard.cpp src/input/keyboard.h src/sfx/sfx.cpp src/sfx/sfx.h src/sdl_includes.h src/core.h
libchomp_a_LIBADD = $(LIBOBJS) $(ALLOCA)

noinst_PROGRAMS = example_chompy example_config example_text example_mouse example_gamepad example_triangle_runner

example_chompy_SOURCES = examples/chompy/src/main.cpp examples/chompy/src/state_chompy.cpp examples/gamepad/src/state_chompy.h
example_chompy_LDFLAGS = -static
example_chompy_LDADD = libchomp.a

example_config_SOURCES = examples/config/src/main.cpp
example_config_LDFLAGS = -static
example_config_LDADD = libchomp.a

example_text_SOURCES = examples/text/src/main.cpp examples/text/src/state_main.cpp examples/text/src/state_main.h
example_text_LDFLAGS = -static
example_text_LDADD = libchomp.a

example_mouse_SOURCES = examples/mouse/src/main.cpp examples/mouse/src/state_main.cpp examples/mouse/src/state_main.h
example_mouse_LDFLAGS = -static
example_mouse_LDADD = libchomp.a

example_gamepad_SOURCES = examples/gamepad/src/main.cpp examples/gamepad/src/state_main.cpp examples/gamepad/src/state_main.h
example_gamepad_LDFLAGS = -static
example_gamepad_LDADD = libchomp.a

example_triangle_runner_SOURCES = examples/triangle_runner/src/main.cpp examples/triangle_runner/src/state_main.cpp examples/triangle_runner/src/state_main.h examples/triangle_runner/src/state_play.cpp examples/triangle_runner/src/state_play.h
example_triangle_runner_LDFLAGS = -static
example_triangle_runner_LDADD = libchomp.a