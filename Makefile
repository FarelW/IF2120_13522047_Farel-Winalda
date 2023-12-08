# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -I/path/to/jsoncpp/include

# Linker flags
LDFLAGS = -L/path/to/jsoncpp/lib -ljsoncpp

# Source files
SOURCES = main.cpp src/graph.cpp

# Object files directory
OBJDIR = bin

# Object files
OBJECTS = $(OBJDIR)/main.o $(OBJDIR)/graph.o

# Executable
EXECUTABLE = main

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJDIR)/main.o: main.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/graph.o: src/graph.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)
