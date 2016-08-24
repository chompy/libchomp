import sys
import os
import struct
from tiledtmxloader import tmxreader
sys.path.append("lib/chompy_engine/tools/asset_compiler")
from core import AssetCompilerCore, parse_json

class AssetCompiler(AssetCompilerCore):
    PLATFORM_NAME = "sdl2"

    MAX_TILE_DIMENSION = 65535

    # compile map
    def compile_map(self, filepath):

        # must be TMX file
        if os.path.splitext(filepath)[1] != ".tmx":
            return None

        # debug
        print "  - Processing '%s'..." % os.path.splitext(os.path.basename(filepath))[0],

        # open TMX
        tiledMap = tmxreader.TileMapParser().parse_decode(filepath)

        # failed to open tmx
        if not tiledMap or len(tiledMap.layers) == 0:
            print "error"
            print "\t----> Unable to load TMX."
            return None

        # should only contain 1 tile set
        if len(tiledMap.tile_sets) != 1:
            print "error"
            print "\t----> Should only contain one tile set."
            return None

        # tile set should contain one image
        if len(tiledMap.tile_sets[0].images) != 1:
            print "error"
            print "\t----> Tile set should contain only one image."
            return None

        # map width/height should be under 65535 (2 bytes)
        if tiledMap.width > self.MAX_TILE_DIMENSION or tiledMap.height > self.MAX_TILE_DIMENSION:
            print "error"
            print "\t----> Map too large (%dx%d tile max)." % (self.MAX_TILE_DIMENSION, self.MAX_TILE_DIMENSION)

        # output buffer
        outputBuffer = ""

        # write tile sprite name
        outputBuffer += struct.pack("<B", len( tiledMap.tile_sets[0].name ))
        outputBuffer += str(tiledMap.tile_sets[0].name)

        # TODO
        # tileset offset (4 bytes x + y)
        # layer size (4 bytes)
        # tile data

        # write background name
        backgroundName = ""
        if "background" in tiledMap.properties:
            backgroundName = tiledMap.properties["background"]
        outputBuffer += struct.pack("<B", len(backgroundName))
        outputBuffer += str(backgroundName)

        # write map tile data
        binaryData = ""
        for i in range(16):
            tile = None
            for _tile in tiledMap.tile_sets[0].tiles:
                if int(_tile.id) == i - 1:
                    tile = _tile
                    break
            tileTypeValue = 0
            if tile and "type" in tile.properties and tile.properties["type"] in self.MAP_TILE_TYPES:
                tileTypeValue = int(self.MAP_TILE_TYPES[tile.properties["type"]])

            binaryData += "{0:b}".format(tileTypeValue).zfill(2)

            if len(binaryData) == 8:
                outputBuffer += struct.pack("<B", int(binaryData, 2))
                binaryData = ""

        if len(binaryData) > 0:
            outputBuffer += struct.pack("<B", int(binaryData.zfill(8), 2))

        # write map size
        outputBuffer += struct.pack("<B", tiledMap.width)
        outputBuffer += struct.pack("<B", tiledMap.height)

        # write map data
        previousValue = None
        for tile in tiledMap.layers[0].decoded_content:
            # 4 bit uint
            tile = tile % 16;

            if previousValue is None:
                previousValue = tile
                continue
            else:
                outputBuffer += struct.pack("<B", int( "0x%s%s" % (hex(previousValue)[2], hex(tile)[2]), 16))
                previousValue = None

        if previousValue:
            outputBuffer += struct.pack("<B", int( "0x%s0" % hex(previousValue)[2], 16 ))

        # spawn point data
        if len(tiledMap.layers) > 1 and tiledMap.layers[1].is_object_group:

            outputBuffer += struct.pack("<B", len(tiledMap.layers[1].objects))

            for mapObject in tiledMap.layers[1].objects:

                outputBuffer += struct.pack("<B", len(mapObject.properties["entity"]))
                outputBuffer += str(mapObject.properties["entity"])

                outputBuffer += struct.pack("<B", mapObject.x / tiledMap.tilewidth )
                outputBuffer += struct.pack("<B", mapObject.y / tiledMap.tileheight )
                outputBuffer += struct.pack("<B", mapObject.width / tiledMap.tilewidth )
                outputBuffer += struct.pack("<B", mapObject.height / tiledMap.tileheight )

                count = 1
                if "count" in mapObject.properties:
                    count = int(mapObject.properties["count"])
                outputBuffer += struct.pack("<B", count)

                respawn = 30
                if "respawn" in mapObject.properties:
                    respawn = int(mapObject.properties["respawn"])
                outputBuffer += struct.pack("<H", respawn)

                chance = self.RAND_MAX
                if "chance" in mapObject.properties:
                    chance = ((( float(mapObject.properties["chance"]) ) * (self.RAND_MAX)) / (100.0))
                    outputBuffer += struct.pack("<H", int(chance))

        else:
            outputBuffer += struct.pack("<B", 0)

        # done
        print "done"
        return outputBuffer
