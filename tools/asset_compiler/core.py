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
import os
import json
import struct
from PIL import Image, ImageFont
from pydub import AudioSegment
try:
    from StringIO import StringIO as BytesIO
except ImportError:
    from io import BytesIO

# parse json array
def parse_json(fullpath):
    with open(fullpath, "r") as fp:
        return json.loads( fp.read() )

class AssetCompiler:

    DEFAULT_ANIMATION_FPS = 24
    OUTPUT_PATH = "assets.dat"
    RAND_MAX = 32767

    CONFIG_TYPE_STRING = 0
    CONFIG_TYPE_INT = 1
    CONFIG_TYPE_FLOAT = 2

    def __init__(self, config = {}):
        if "output" in config and config["output"]:
            self.OUTPUT_PATH = config["output"]

    def compile_game_controller_db(self, filePath):

        # open controller db and dump to output
        outputBuffer = b""
        with open(filePath, "rb") as f:
            outputBuffer += f.read()

        print("done")
        return outputBuffer

    def compile_sprite_frames(self, imagePath, frameSize):

        # image does not exist
        if not os.path.exists( imagePath ):
            print("error")
            print("\t----> sprite '%s' not found" % spriteFilename)
            return None

        # attempt to open sprite
        try:
            sprite = Image.open( imagePath )
        except IOError as detail:
            print("error")
            print("  - ----> %s" % detail)
            return None

        # invalid mode
        if sprite.mode not in ["LA", "RGBA", "RGB"]:
            print("error")
            print("\t----> sprite uses incompatible color mode")
            return None

        # output buffer
        outputBuffer = b""

        # get size of frames
        frameSize = list(map(int, frameSize))
        for i in frameSize:
            outputBuffer += struct.pack("<H", int(i))

        # write frame count
        outputBuffer += struct.pack("<H", int((sprite.size[1] / frameSize[1]) * (sprite.size[0] / frameSize[0])))

        # compile tile data
        for y in range( int(sprite.size[1] / frameSize[1]) ):
            if sprite.size[1] - (y * frameSize[1]) < frameSize[1]: break
            for x in range( int(sprite.size[0] / frameSize[0]) ):
                if sprite.size[0] - (x * frameSize[0]) < frameSize[0]: continue

                tile = sprite.copy().crop(( x * frameSize[0], y * frameSize[1], (x + 1) * frameSize[0], (y + 1) * frameSize[1] ))

                tileData = BytesIO()
                tile.convert("RGBA").save(tileData, "PNG")
                outputBuffer += struct.pack("<L", len(tileData.getvalue()) )
                outputBuffer += tileData.getvalue()
                tileData.close()

        return outputBuffer

    # compile sprite
    def compile_sprite(self, filePath):

        # must be JSON file
        if os.path.splitext(filePath)[1] != ".json":
            return None

        # debug
        print("  - Processing '%s'..." % os.path.splitext(os.path.basename(filePath))[0], end="")

        # convert json to array
        config = parse_json(filePath)

        # determine filename of sprite
        if not "source" in config or not config["source"] or type(config["source"]) is not str:
            print("skipped")
            print("\t----> sprite '%s' not provided" % os.path.splitext(filePath)[0])
            return None
        spriteFilename = config["source"]

        # name of sprite
        spriteName = os.path.splitext(os.path.basename(filePath))[0].strip().replace(" ", "_").lower()[:255]

        # get size of frames
        frameSize = map(int, config["frame_size"])

        # compile frames
        outputBuffer = self.compile_sprite_frames(os.path.join(os.path.dirname(filePath), spriteFilename), frameSize)
        if not outputBuffer:
            return None

        # compile animation data
        count = 0
        animationDataStr = b""

        if "animation" in config:
            for animationName in config["animation"]:
                count += 1
                animationFrames = []
                for animationFrame in config["animation"][animationName]:
                    if type(animationFrame) == int:
                        animationFrames.append(animationFrame)
                    elif type(animationFrame) == str:
                        animationFrame = str(animationFrame).split("-")
                        if len(animationFrame) != 2:
                            continue
                        for i in range(int(animationFrame[0]), int(animationFrame[1]) + 1):
                            animationFrames.append(i)
                            
                animationDataStr += struct.pack("<B", len(animationName))
                animationDataStr += bytes(animationName, "ascii")
                animationDataStr += struct.pack("<H", len(animationFrames))
                for animationFrame in animationFrames:
                    animationDataStr += struct.pack("<H", int(animationFrame))            

        outputBuffer += struct.pack("<B", count)

        animationFps = self.DEFAULT_ANIMATION_FPS
        if "animation_fps" in config and type(config["animation_fps"]) == int:
            animationFps = int(config["animation_fps"])
        outputBuffer += struct.pack("<B", animationFps)

        outputBuffer += animationDataStr

        # done
        print("done")
        return outputBuffer

    # compile font
    def compile_font(self, filepath):

        # must be JSON file
        if os.path.splitext(filepath)[1] != ".json":
            return None

        # debug
        print("  - Processing '%s'..." % os.path.splitext(os.path.basename(filepath))[0], end="")

        # parse json
        config = parse_json(filepath)

        # get font file
        fontFilename = ""
        if "font_file" in config and config["font_file"]:
            fontFilename = config["font_file"]
        else:
            print("error")
            print("\t----> font filename was not provided")
            return

        # check if font exists
        fontFullPath = os.path.join(os.path.dirname(filepath), fontFilename)
        if not os.path.exists(fontFullPath):
            print("error")
            print("\t----> font '%s' was not found" % fontFilename)

        # open font and dump to output
        outputBuffer = b""
        with open(fontFullPath, "rb") as f:
            outputBuffer += f.read()

        print("done")
        return outputBuffer

    # compile config
    def compile_config(self, filepath):

        # must be JSON file
        if os.path.splitext(filepath)[1] != ".json":
            return None

        # debug
        print("  - Processing '%s'..." % os.path.splitext(os.path.basename(filepath))[0], end="")

        # config file not found
        if not os.path.exists(filepath):
            print("error")
            print("\t----> config file (%s) does not exist." % os.path.basename(filepath))
            return None

        # parse json
        config = parse_json(filepath)

        # function to recursively iterate over config
        def iterateConfig(value, keys = []):
            
            outputBuffer = b""
            configKey = ""
            if (keys):
                configKey = '.'.join(keys)

            # dict, recursive
            if type(value) is dict:
                for key in value:
                    newKeys = list(keys)
                    newKeys.append(key)
                    outputBuffer += iterateConfig(
                        value[key],
                        newKeys
                    )
                return outputBuffer
            
            # list 
            elif type(value) is list:
                count = 0
                for subValue in value:
                    newKeys = list(keys)
                    newKeys.append(str(count))
                    outputBuffer += iterateConfig(
                        subValue,
                        newKeys
                    )
                    count += 1
                return outputBuffer

            # key
            outputBuffer += struct.pack("<H", len(configKey))
            outputBuffer += bytes(configKey, "ascii")

            # integer
            if type(value) is int:
                outputBuffer += struct.pack("<B", self.CONFIG_TYPE_INT)
                outputBuffer += struct.pack("<l", value)

            # float
            elif type(value) is float:
                outputBuffer += struct.pack("<B", self.CONFIG_TYPE_FLOAT)
                outputBuffer += struct.pack("<f", value)

            # string (treat everything else as a string)
            else:
                outputBuffer += struct.pack("<B", self.CONFIG_TYPE_STRING)
                outputBuffer += struct.pack("<H", len(value))
                outputBuffer += bytes(value, "ascii")

            return outputBuffer

        # config must be a dict
        if type(config) is not dict:
            print("error")
            print("\t----> config should be in dict format ({ 'key' : 'value' }).")

        # recursively process
        outputBuffer = iterateConfig(config)

        # done
        print("done")
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
        print("  - Processing '%s'..." % os.path.splitext(os.path.basename(filepath))[0], end="")

        # convert json to array
        config = parse_json(filepath)

        # determine filename of audio clip
        if not "source" in config or not config["source"] or type(config["source"]) is not str:
            print("skipped")
            print("\t----> audio '%s' not provided" % os.path.splitext(filepath)[0])
            return None
        audioFilename = config["source"]
        audioExt = os.path.splitext(audioFilename)[1].replace(".", "")

        # name of audio clip
        audioName = os.path.splitext(os.path.basename(filepath))[0].strip().replace(" ", "_").lower()[:255]

        # prepare output
        outputBuffer = b""

        # open with pydub
        outputBitrate = "192k"
        if "bitrate" in config and config["bitrate"]:
            outputBitrate = config["bitrate"]

        pyDubAudio = AudioSegment.from_file( os.path.join( os.path.dirname(filepath), audioFilename ) )
        audioData = BytesIO()
        pyDubAudio.export(audioData, format=output, bitrate=outputBitrate)

        # add to output
        audioData.seek(0)
        outputBuffer = audioData.read()
        audioData.close()

        # done
        print("done")
        return outputBuffer

    # modify final output
    def output(self, outputBuffer):
        return outputBuffer