SRC=$(wildcard ./*.cpp)
TGT=../build/${COMPILETO}
INCLUDES=
CXXFLAGS=-Wall -std=c++11  $(INCLUDES)
LDFLAGS = -Wall -std=c++11 -g
OBJS = $(addprefix $(TGT)/, $(notdir $(SRC:.cpp=.o)))

$(TGT)/%.o: %.cpp
	$(CXX) $(OPTS) $(CXXFLAGS) $(LIBS) -c -fPIC $< -o $@

all: $(OBJS)
	cd asset; make OPTS="$(OPTS)" LIBS="$(LIBS)"
	cd gfx; make OPTS="$(OPTS)" LIBS="$(LIBS)"
	cd sfx; make OPTS="$(OPTS)" LIBS="$(LIBS)"
	cd input; make OPTS="$(OPTS)" LIBS="$(LIBS)"
	cd exception; make OPTS="$(OPTS)" LIBS="$(LIBS)"
	echo "$^"