TGT=build
INCLUDES = -Isrc
CXXFLAGS = -Wall -std=c++11  $(INCLUDES)
LDFLAGS = -Wall -std=c++11 -g
OBJS = $(addprefix $(TGT)/, $(notdir $(SOURCES:.cpp=.o)))
OS=$(shell tools/get_os.sh)

OPTS=
LINUX_LIBS = -lSDL2
EMSCRIPTEN_LIBS = -s USE_SDL=2
WIN32_LIBS = -lsdl2

ifeq ($(WITHOUT_SDL_MIXER), 1)
OPTS += -DWITHOUT_SDL_MIXER
else
LINUX_LIBS += -lSDL2_mixer
#EMSCRIPTEN_LIBS += -s USE_SDL_MIXER=2
EMSCRIPTEN_LIBS += -DWITHOUT_SDL_MIXER
WIN32_LIBS += -lsdl2_mixer
endif
ifeq ($(WITHOUT_SDL_IMAGE), 1)
OPTS += -DWITHOUT_SDL_IMAGE
else
LINUX_LIBS += -lSDL2_image
EMSCRIPTEN_LIBS += -s USE_SDL_IMAGE=2
WIN32_LIBS += -lsdl2_image
endif
ifeq ($(WITHOUT_SDL_TTF), 1)
OPTS += -DWITHOUT_SDL_TTF
else
LINUX_LIBS += -lSDL2_ttf
EMSCRIPTEN_LIBS += -s USE_SDL_TTF=2
WIN32_LIBS += -lsdl2_ttf
endif

LINUX_LIBS += -lSDL2main
WIN32_LIBS += -lSDL2main

all:
	make $(OS)

linux:
	mkdir -p $(TGT)/linux
	cd src; make COMPILETO="linux" OPTS="$(OPTS)" LIBS=""
	$(CXX) $(OPTS) $(LDFLAGS) $(TGT)/linux/*.o -DSDL2=1 -shared \
	-o $(TGT)/linux/libchomp.so $(LINUX_LIBS)

emscripten:
	mkdir -p $(TGT)/emscripten
	cd src; make COMPILETO="emscripten" OPTS="$(OPTS)" LIBS="$(EMSCRIPTEN_LIBS)"
	$(CXX) $(OPTS) $(LDFLAGS) $(TGT)/emscripten/*.o \
		-DSDL2=1 -shared -Ilib/include \
		$(EMSCRIPTEN_LIBS) \
		-O2 -o $(TGT)/emscripten/libchomp.bc

win32:
	mkdir -p $(TGT)/win32
	cd src; make COMPILETO="win32" OPTS="$(OPTS)" LIBS=""
	$(CXX) $(OPTS) $(LDFLAGS) $(TGT)/win32/*.o -DSDL2=1 -shared -o \
	$(TGT)/win32/libchomp.dll -static-libgcc -static-libstdc++ \
	-Llib/win32 $(WIN32_LIBS)

cleanup:
	rm -rf $(TGT)/*
