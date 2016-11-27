TGT=build
INCLUDES = -Isrc -I../../src
CXXFLAGS = -Wall -std=c++11  $(INCLUDES)
LDFLAGS = -Wall -std=c++11 -g
OBJS = $(addprefix $(TGT)/, $(notdir $(SOURCES:.cpp=.o)))
OS=$(shell ../../tools/get_os.sh)

all:
	make $(OS)

linux:
	mkdir -p $(TGT)/linux
	cd src; make COMPILETO="linux"
	$(CXX) $(LDFLAGS) $(TGT)/linux/*.o -DSDL2 -o $(TGT)/linux/output.bin -L../../lib/linux -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer ../../build/linux/libchomp.so

win32:
	mkdir -p $(TGT)/win32
	cp ../../build/win32/*.dll .
	cd src; make COMPILETO="win32"
	$(CXX) $(LDFLAGS) $(TGT)/win32/*.o -DSDL2 -o $(TGT)/win32/output.exe libchomp.dll -static-libgcc -static-libstdc++ -mconsole -mwindows -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

emscripten:
	mkdir -p $(TGT)/emscripten
	cd src; make COMPILETO="emscripten"
	$(CXX) $(LDFLAGS) $(TGT)/emscripten/*.o \
		-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s SDL2_IMAGE_FORMATS='["png"]' \
		-DSDL2=1 ../../build/emscripten/chomp_engine.bc \
		--preload-file assets.dat \
		-O2 -o $(TGT)/emscripten/output.html

cleanup:
	rm -f *.dll
	rm -rf $(TGT)/*
