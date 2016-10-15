import sys
import os
import json
import struct
from PIL import Image, ImageFont
from pydub import AudioSegment
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

    CONFIG_TYPE_STRING = 0
    CONFIG_TYPE_INT = 1
    CONFIG_TYPE_FLOAT = 2

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
        if not "source" in config or not self.PLATFORM_NAME in config["source"]:
            print "skipped"
            print "\t----> sprite '%s' not provided" % os.path.splitext(filename)[0]
            return None
        spriteFilename = config["source"][self.PLATFORM_NAME]

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

    # compile config
    def compile_config(self, filepath):

        # must be JSON file
        if os.path.splitext(filepath)[1] != ".json":
            return None

        # debug
        print "  - Processing '%s'..." % os.path.splitext(os.path.basename(filepath))[0], 

        # config file not found
        if not os.path.exists(filepath):
            print "error"
            print "\t----> config file (%s) does not exist." % os.path.basename(filepath)
            return None

        # parse json
        config = parse_json(filepath)

        # prepare output
        outputBuffer = ""

        # function to recursively iterate over config
        def iterateConfig(value, keys = [], outputBuffer = ""):
            
            configKey = ""
            if (keys):
                configKey = '.'.join(keys)

            # dict, recursive
            if type(value) is dict:
                for key in value:
                    newKeys = list(keys)
                    newKeys.append(key)
                    iterateConfig(
                        value[key],
                        newKeys,
                        outputBuffer
                    )
            
            # list 
            elif type(value) is list:
                count = 0
                for subValue in value:
                    iterateConfig(
                        subValue,
                        keys.append(str(count)),
                        outputBuffer
                    )
                    count += 1

            # integer
            elif type(value) is int:
                outputBuffer += struct.pack("<B", self.CONFIG_TYPE_INT)
                outputBuffer += struct.pack("<l", value)

            # float
            elif type(value) is float:
                outputBuffer += struct.pack("<B", self.CONFIG_TYPE_FLOAT)
                outputBuffer += struct.pack("<f", value)

            # string (treat everything else as a string)
            else:
                outputBuffer += struct.pack("<B", self.CONFIG_TYPE_STRING)
                outputBuffer += struct.pack("<H", len(configKey))
                outputBuffer += str(value)

        # config must be a dict
        if type(config) is not dict:
            print "error"
            print "\t----> config should be in dict format ({ 'key' : 'value' })."

        # recursively process
        iterateConfig(config, [], outputBuffer)

        # done
        print "done"
        return outputBuffer

    # compile music
    def compile_music(self, filepath):
        return self.compile_audio(filepath, "ogg")

    # compile all types of audio
    def compile_audio(self, filepath, output = "wav"):

        # must be JSON file
        if os.path.splitext(filepath)[1] != ".json":
            return None

        # debug
        print "  - Processing '%s'..." % os.path.splitext(os.path.basename(filepath))[0],

        # convert json to array
        config = parse_json(filepath)

        # determine filename of audio clip
        if not "source" in config or not self.PLATFORM_NAME in config["source"]:
            print "skipped"
            print "\t----> audio '%s' not provided" % os.path.splitext(filename)[0]
            return None
        audioFilename = config["source"][self.PLATFORM_NAME]
        audioExt = os.path.splitext(audioFilename)[1].replace(".", "")

        # name of audio clip
        audioName = os.path.splitext(os.path.basename(filepath))[0].strip().replace(" ", "_").lower()[:255]

        # prepare output
        outputBuffer = ""

        # open with pydub
        outputBitrate = "192k"
        if "bitrate" in config and config["bitrate"]:
            outputBitrate = config["bitrate"]
        pyDubAudio = AudioSegment.from_file( os.path.join( os.path.dirname(filepath), audioFilename ) )
        audioData = StringIO.StringIO()
        pyDubAudio.export(audioData, format=output, bitrate=outputBitrate)

        # add to output
        outputBuffer = str( audioData.read() )
        audioData.close()

        # done
        print "done"
        return outputBuffer

    # modify final output
    def output(self, outputBuffer):
        return outputBuffer