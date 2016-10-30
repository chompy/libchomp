import sys
import loader

# list of compilers and their configurations
COMPILERS = {
    "sprites" : {
        "filepath" : "assets/gfx",
        "prefix" : "spr_",
        "method" : "compile_sprite"
    },
    "fonts" : {
        "filepath" : "assets/font",
        "prefix" : "font_",
        "method" : "compile_font"
    },
    "config" : {
        "filepath" : "assets/config",
        "prefix" : "conf_",
        "method" : "compile_config"
    },
    "sound effects" : {
        "filepath" : "assets/sfx",
        "prefix" : "sfx_",
        "method" : "compile_audio"
    },
    "music" : {
        "filepath" : "assets/music",
        "prefix" : "mus_",
        "method" : "compile_music"
    },
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