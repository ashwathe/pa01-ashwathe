CXX = g++
CXXFLAGS = -Wall -Wno-uninitialized

BINARIES = game

game: main.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

tests: ${BINARIES}
	./test

test: test.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

clean:
	/bin/rm -f main game *.o