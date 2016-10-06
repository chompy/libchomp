SRC=$(wildcard ./*.cpp)
TGT=../build/${COMPILETO}
INCLUDES=
CXXFLAGS=-Wall -std=c++11  $(INCLUDES)
LDFLAGS = -Wall -std=c++11 -g
OBJS = $(addprefix $(TGT)/, $(notdir $(SRC:.cpp=.o)))

$(TGT)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

all: $(OBJS)
	cd asset; make
	cd gfx; make
	cd sfx; make
	cd input; make
	echo "$^"