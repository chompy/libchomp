"""
    This file is part of Libchomp.

    Libchomp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Libchomp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Libchomp.  If not, see <http://www.gnu.org/licenses/>.
"""

import sys
import loader
import os

# list of compilers and their configurations
COMPILERS = {
    "game controller database" : {
        "filepath" : "assets/game_controller_db.txt",
        "filename" : "_gcdb",
        "method" : "compile_game_controller_db"
    },
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