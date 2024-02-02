CXX = g++
CXXFLAGS = -std=c++11 -Wall
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = OlympiFitChallenge


SFML_INCLUDE = /usr/include
SFML_LIB = /usr/lib

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -I$(SFML_INCLUDE) -L$(SFML_LIB) $(SFMLFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(SFML_INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
