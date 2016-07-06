import sys
import os
import json
import struct
from PIL import Image, ImageFont
import StringIO

# parse json array
def parse_json(fullpath):
    with open(fullpath, "r") as fp:
        return json.loads( fp.read() )

class AssetCompilerCore:

    PLATFORM_NAME = "core"
    DEFAULT_ANIMATION_FPS = 24
    OUTPUT_PATH = "assets.dat"
    RAND_MAX = 32767

    def compile_sprite_frames(self, imagePath, frameSize):

        # image does not exist
        if not os.path.exists( imagePath ):
            print "error"
            print "\t----> sprite '%s' not found" % spriteFilename
            return None

        # attempt to open sprite
        try:
            sprite = Image.open( imagePath )
        except IOError as detail:
            print "error"
            print "  - ----> %s" % detail
            return None

        # invalid mode
        if sprite.mode not in ["LA", "RGBA", "RGB"]:
            print "error"
            print "\t----> sprite uses incompatible color mode"
            return None

        # output buffer
        outputBuffer = ""

        # get size of frames
        frameSize = map(int, frameSize)
        for i in frameSize:
            outputBuffer += struct.pack("<H", int(i))

        # write frame count
        outputBuffer += struct.pack("<H", (sprite.size[1] / frameSize[1]) * (sprite.size[0] / frameSize[0]) - 1)

        # compile tile data
        for y in range( sprite.size[1] / frameSize[1] ):
            if sprite.size[1] - (y * frameSize[1]) < frameSize[1]: break
            for x in range( sprite.size[0] / frameSize[0] ):
                if sprite.size[0] - (x * frameSize[0]) < frameSize[0]: continue

                tile = sprite.copy().crop(( x * frameSize[0], y * frameSize[1], (x + 1) * frameSize[0], (y + 1) * frameSize[1] ))

                tileData = StringIO.StringIO()
                tile.convert("RGBA").save(tileData, "PNG")
                outputBuffer += struct.pack("<L", len(tileData.getvalue()) )
                outputBuffer += tileData.getvalue()
                tileData.close()

        return outputBuffer

    # compile sprite
    def compile_sprite(self, filepath):

        # must be JSON file
        if os.path.splitext(filepath)[1] != ".json":
            return None

        # debug
        print "  - Processing '%s'..." % os.path.splitext(os.path.basename(filepath))[0],

        # convert json to array
        config = parse_json(filepath)

        # determine filename of sprite
        if not "image" in config or not self.PLATFORM_NAME in config["image"]:
            print "skipped"
            print "\t----> sprite '%s' not provided" % os.path.splitext(filename)[0]
            return None
        spriteFilename = config["image"][self.PLATFORM_NAME]

        # name of sprite
        spriteName = os.path.splitext(os.path.basename(filepath))[0].strip().replace(" ", "_").lower()[:255]

        # get size of frames
        frameSize = map(int, config["frame_size"])

        # compile frames
        outputBuffer = self.compile_sprite_frames(os.path.join(os.path.dirname(filepath), spriteFilename), frameSize)
        if not outputBuffer:
            return None

        # compile animation data
        count = 0
        animationDataStr = ""

        if "animation" in config:
            for animationName in config["animation"]:
                count += 1
                animationFrames = []
                for animationFrame in config["animation"][animationName]:
                    if type(animationFrame) == int:
                        animationFrames.append(animationFrame)
                    elif type(animationFrame) == unicode or type(animationFrame) == str:
                        animationFrame = str(animationFrame).split("-")
                        if len(animationFrame) != 2:
                            continue
                        for i in range(int(animationFrame[0]), int(animationFrame[1]) + 1):
                            animationFrames.append(i)
                            
                animationDataStr += struct.pack("<B", len(animationName))
                animationDataStr += str(animationName)
                animationDataStr += struct.pack("<B", len(animationFrames))
                for animationFrame in animationFrames:
                    animationDataStr += struct.pack("<B", int(animationFrame))            

        outputBuffer += struct.pack("<B", count)

        animationFps = self.DEFAULT_ANIMATION_FPS
        if "animation_fps" in config and type(config["animation_fps"]) == int:
            animationFps = int(config["animation_fps"])
        outputBuffer += struct.pack("<B", animationFps)

        outputBuffer += animationDataStr

        # done
        print "done"
        return outputBuffer

    # compile font
    def compile_font(self, filepath):

        # must be JSON file
        if os.path.splitext(filepath)[1] != ".json":
            return None

        # debug
        print "  - Processing '%s'..." % os.path.splitext(os.path.basename(filepath))[0],

        # parse json
        config = parse_json(filepath)

        # get font file
        fontFilename = ""
        if "font_file" in config and config["font_file"]:
            fontFilename = config["font_file"]
        else:
            print "error"
            print "\t----> font filename was not provided"
            return

        # check if font exists
        fontFullPath = os.path.join(os.path.dirname(filepath), fontFilename)
        if not os.path.exists(fontFullPath):
            print "error"
            print "\t----> font '%s' was not found" % fontFilename

        # open font and dump to output
        outputBuffer = ""
        with open(fontFullPath, "rb") as f:
            outputBuffer += f.read()

        print "done"
        return outputBuffer

    # compile language
    def compile_language(self, filepath):

        # must be JSON file
        if os.path.splitext(filepath)[1] != ".json":
            return None

        # debug
        print filepath
        print "  - Processing '%s'..." % os.path.splitext(os.path.basename(filepath))[0],

        # parse json
        config = parse_json(filepath)

        # prepare output
        outputBuffer = ""

        # compile number of entries
        outputBuffer += struct.pack("<H", len(config))

        # compile key values
        for key in config:
            value = config[key]
            outputBuffer += struct.pack("<B", len(key))
            outputBuffer += key
            outputBuffer += struct.pack("<B", len(value))
            outputBuffer += value

        # done
        print "done"
        return outputBuffer

    # compile config
    def compile_config(self, filepath):

        # config file not found
        if not os.path.exists(filepath):
            print "error"
            print "\t----> config file (%s) does not exist." % os.path.basename(filepath)
            return None

        # parse json
        config = parse_json(filepath)

        # prepare output
        outputBuffer = ""

        # iterate params
        for param in config:
            value = config[param]
            outputBuffer += struct.pack("<B", len(param))
            outputBuffer += str(param)
            if type(value) == int:
                outputBuffer += struct.pack("<B", 4)
                outputBuffer += struct.pack("<l", value)
            elif type(value) == float:
                outputBuffer += struct.pack("<B", 4)
                outputBuffer += struct.pack("<f", value)
            else:
                outputBuffer += struct.pack("<B", len(value))
                outputBuffer += str(value)

        # done
        print "done"
        return outputBuffer

    # modify final output
    def output(self, outputBuffer):
        return outputBuffer