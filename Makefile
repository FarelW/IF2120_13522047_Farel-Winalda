# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -I/path/to/jsoncpp/include

# Linker flags
LDFLAGS = -L/path/to/jsoncpp/lib -ljsoncpp

# Source files
SOURCES = main.cpp src/graph.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable
EXECUTABLE = tes

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
