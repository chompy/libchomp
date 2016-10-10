SRC=$(wildcard ./*.cpp)
TGT=../build/${COMPILETO}
INCLUDES=
CXXFLAGS=-Wall -std=c++11  $(INCLUDES)
LDFLAGS = -Wall -std=c++11 -g
OBJS = $(addprefix $(TGT)/, $(notdir $(SRC:.cpp=.o)))

$(TGT)/%.o: %.cpp
	$(CXX) $(OPTS) $(CXXFLAGS) -c -fPIC $< -o $@

all: $(OBJS)
	cd asset; make OPTS="$(OPTS)"
	cd gfx; make OPTS="$(OPTS)"
	cd sfx; make OPTS="$(OPTS)"
	cd input; make OPTS="$(OPTS)"
	cd exception; make OPTS="$(OPTS)"
	echo "$^"