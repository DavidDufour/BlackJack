TARGETS=blackjack
SRC=$(wildcard *.cxx)

CXXFLAGS+=-std=gnu++0x -g -Wall

all: $(TARGETS)

clean:
	rm -rf *.o $(TARGETS)

$(TARGETS): $(SRC:.cxx=.o)
	$(CXX) $^ $(CXXFLAGS) -o $@

%.o: %.cxx
	$(CXX) $^ $(CXXFLAGS) -c -o $@
