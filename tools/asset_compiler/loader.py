import os
import struct

def run(compilerConfig, compiler):

    # get platform compiler module
    compiler = compiler.AssetCompiler()

    # data to compile
    dataBuffer = []

    # iterate compiler conf
    for compileType in compilerConfig:
        
        print "* Compile %s..." % compileType,

        config = compilerConfig[compileType]

        # must include filepath
        if "filepath" not in config:
            print "error"
            print "---> 'filepath' not configured"
            continue

        # must include method
        if "method" not in config:
            print "error"
            print "---> 'method' not configured"
            continue

        # get asset name prefix
        prefix = ""
        if "prefix" in config:
            prefix = config["prefix"]

        # resolve filepath
        filepath = config["filepath"]
        if not os.path.exists(filepath):
            filepath = os.path.join( os.path.join( os.path.dirname(__file__), "../../" ), filepath )
            if not os.path.exists(filepath):
                print "error"
                print "---> file path '%s' was not found" % config["filepath"]
                continue

        # single file
        if os.path.isfile(filepath):
            data = getattr(compiler, config["method"])(filepath)           
            if data is None: continue
            filename = "%s%s" % (prefix, os.path.splitext(os.path.basename(filepath))[0].strip().replace(" ", "_"))
            if "filename" in config:
                filename = config["filename"]
            dataBuffer.append({
                "name" : filename,
                "data" : data
            })

        # multi file
        elif os.path.isdir(filepath):
            print
            for filename in os.listdir(filepath):
                data = getattr(compiler, config["method"])(os.path.join(filepath, filename))
                if data is None: continue
                dataBuffer.append({
                    "name" : "%s%s" % (prefix, os.path.splitext(filename)[0].strip().replace(" ", "_")),
                    "data" : data
                })

    # open output file
    output = open(compiler.OUTPUT_PATH, "wb")

    # build index
    print "* Build index...",

    # output
    outputBuffer = ""

    # write number of assets
    outputBuffer += struct.pack("<H", len(dataBuffer))

    # iterate assets to determine index size
    indexSize = 2
    for item in dataBuffer:
        indexSize += len(item["name"]) + 9

    # iterate assets to write index
    pos = indexSize
    for item in dataBuffer:
        
        # write asset name
        outputBuffer += struct.pack("<B", len(item["name"]))
        outputBuffer += item["name"]

        # write data pos and size
        outputBuffer += struct.pack("<L", pos)
        outputBuffer += struct.pack("<L", len(item["data"]))

        # next position
        pos += len(item["data"])

    # done index
    print "done"

    # iterate assets to write data
    print "* Write asset data to buffer...",
    for item in dataBuffer:
        outputBuffer += str( item["data"] )
    print "done"

    # compiler output method
    try:
        outputBuffer = compiler.output(outputBuffer)
    except AttributeError:
        pass

    # write to file
    print "* Writing output file...",
    output.write( outputBuffer )
    print "done"

    # close output
    output.close()