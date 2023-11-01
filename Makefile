CXX = g++
CXXFLAGS = -Wall -std=c++17

PROJECT = test

DEPS = fips140.h
OBJ = fips140.o test.o

all: $(PROJECT)

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

$(PROJECT): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) $(PROJECT)
