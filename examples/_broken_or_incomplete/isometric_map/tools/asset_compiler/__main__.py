import sys
import os
sys.path.append(os.path.join(os.path.dirname(__file__), "../../../../tools/asset_compiler"))
import loader
import imp

COMPILERS = imp.load_source("", os.path.join(os.path.dirname(__file__), "../../../../tools/asset_compiler/__main__.py")).COMPILERS
COMPILERS["maps"] = {
    "filepath" : "assets/map",
    "prefix" : "imap_",
    "method" : "compile_map"
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