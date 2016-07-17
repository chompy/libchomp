SRC=$(wildcard ./*.cpp)
TGT=../build/${COMPILETO}
INCLUDES= -I../../../src
CXXFLAGS=-Wall -std=c++11  $(INCLUDES)
LDFLAGS = -Wall -std=c++11 -g
OBJS = $(addprefix $(TGT)/, $(notdir $(SRC:.cpp=.o)))

$(TGT)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -DSDL2 -c $< -o $@

all: $(OBJS)
	echo "$^"