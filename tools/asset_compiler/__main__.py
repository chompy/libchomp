import sys
import loader

# list of compilers and their configurations
COMPILERS = {
    "sprites" : {
        "filepath" : "assets/gfx",
        "prefix" : "spr_",
        "method" : "compile_sprite"
    },
    "languages" : {
        "filepath" : "assets/lang",
        "prefix" : "lang_",
        "method" : "compile_language"
    },
    "fonts" : {
        "filepath" : "assets/font",
        "prefix" : "font_",
        "method" : "compile_font"
    },
    "config" : {
        "filepath" : "assets/config.json",
        "filename" : "_config",
        "method" : "compile_config"
    }
}

# default platform
platform = "sdl2"

# set arguements
for arg in sys.argv:

    # set compiler platform
    if arg[:11] == "--platform=":
        platform = arg[11:].strip()
    elif arg == "--sdl2":
        platform = "sdl2" 

loader.run(COMPILERS, __import__(platform))