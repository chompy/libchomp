AC_INIT([libchomp], [0.0.1], [nathanogden@chompy.me])
AM_INIT_AUTOMAKE([subdir-objects])
LT_INIT
AC_PROG_CXX

AC_CHECK_LIB([SDL2], [SDL_Init])
AC_CHECK_LIB([SDL2_image], [IMG_LoadPNG_RW])
AC_CHECK_LIB([SDL2_ttf], [TTF_OpenFontRW])
AC_CHECK_LIB([SDL2_mixer], [Mix_OpenAudio])
AC_CHECK_HEADERS([SDL2/SDL.h SDL2/SDL_image.h SDL2/SDL_ttf.h SDL2/SDL_mixer.h])

AC_CONFIG_SRCDIR([src])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT