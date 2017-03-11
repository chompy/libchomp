import sys
import os
import struct
from tiledtmxloader import tmxreader
sys.path.append("lib/chompy_engine/tools/asset_compiler")
from core import AssetCompilerCore, parse_json

class AssetCompiler(AssetCompilerCore):
    PLATFORM_NAME = "sdl2"

    MAX_TILE_DIMENSION = 65535
    MAP_TILE_TYPES = {
        "none"  : 0,
        "solid" : 1,
        "slope" : 2,
        "hazard": 3
    }

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
            return None

        # should contain at least one layer
        if len(tiledMap.layers) == 0:
            print "error"
            print "\t----> Map must contain at least one layer."
            return None

        # all layers must be same size as map
        for layer in tiledMap.layers:
            if layer.width != tiledMap.width or layer.height != tiledMap.height:
                print "error"
                print "\t----> All layers must have same tile width/height as map"
                return None

        # output buffer
        outputBuffer = ""

        # write tile sprite name
        outputBuffer += struct.pack("<B", len( tiledMap.tile_sets[0].name ))
        outputBuffer += str(tiledMap.tile_sets[0].name)

        # write tile sprite frame size
        outputBuffer += struct.pack("<H", int(tiledMap.tile_sets[0].tilewidth))
        outputBuffer += struct.pack("<H", int(tiledMap.tile_sets[0].tileheight))

        # write map width/height
        outputBuffer += struct.pack("<H", int(tiledMap.width))
        outputBuffer += struct.pack("<H", int(tiledMap.height))

        # write map tile width/height
        outputBuffer += struct.pack("<H", int(tiledMap.tilewidth))
        outputBuffer += struct.pack("<H", int(tiledMap.tileheight))

        # write layer count
        outputBuffer += struct.pack("<B", len(tiledMap.layers))

        # write tile date
        tileTypeCount = 0
        for layer in tiledMap.layers:
            for tile in layer.decoded_content:
                if int(tile) > tileTypeCount: tileTypeCount = int(tile)
                outputBuffer += struct.pack("<B", int(tile))

        # write tile type data
        for i in range(tileTypeCount):
            tile = None
            for _tile in tiledMap.tile_sets[0].tiles:
                if int(tiledMap.tile_sets[0].firstgid) + int(_tile.id) == i + 1:
                    tile = _tile
                    break
            tileTypeValue = 0
            if tile and "type" in tile.properties and tile.properties["type"] in self.MAP_TILE_TYPES:
                tileTypeValue = int(self.MAP_TILE_TYPES[tile.properties["type"]])
            outputBuffer += struct.pack("<B", tileTypeValue)

        # done
        print "done"
        return outputBuffer
