TGT=build
INCLUDES = -Isrc
CXXFLAGS = -Wall -std=c++11  $(INCLUDES)
LDFLAGS = -Wall -std=c++11 -g
OBJS = $(addprefix $(TGT)/, $(notdir $(SOURCES:.cpp=.o)))

linux:
	mkdir -p $(TGT)/linux
	cd src; make COMPILETO="linux"
	$(CXX) $(LDFLAGS) $(TGT)/linux/*.o -DSDL2=1 -shared \
	-o $(TGT)/linux/libchomp.so -lsdl2 -lsdl2_image -lsdl2_ttf -lSDL2main -lSDL2main

emscripten:
	mkdir -p $(TGT)/emscripten
	cd src; make COMPILETO="emscripten"
	$(CXX) $(LDFLAGS) $(TGT)/emscripten/*.o \
		-DSDL2=1 -shared -Ilib/include \
		-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s SDL2_IMAGE_FORMATS='["png"]' \
		-O2 -o $(TGT)/emscripten/libchomp.bc

win32:
	mkdir -p $(TGT)/win32
	cd src; make COMPILETO="win32"
	$(CXX) $(LDFLAGS) $(TGT)/win32/*.o -DSDL2=1 -shared -o \
	$(TGT)/win32/libchomp.dll -static-libgcc -static-libstdc++ \
	-Llib/win32 -lsdl2 -lsdl2_image -lsdl2_ttf -lSDL2main

win32_x64:
	mkdir -p $(TGT)/win32_x64
	cd src; make COMPILETO="win32_x64"
	$(CXX) $(LDFLAGS) $(TGT)/win32_x64/*.o -DSDL2=1 -shared -o \
	$(TGT)/win32_x64/libchomp.dll -static-libgcc -static-libstdc++ \
	-Llib/win32_x64 -lsdl2 -lsdl2_image -lsdl2_ttf -lSDL2main

cleanup:
	rm -rf $(TGT)/*
