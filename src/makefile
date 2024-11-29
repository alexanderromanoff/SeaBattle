# Compiler and flags
CXX = g++
CXXFLAGS = -c

# Target executable
TARGET = MyProject

# Source files and object files
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Build the final executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^
	rm -f $(OBJS)

# Generic rule to compile .cpp into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean target
clean:
	rm -f $(TARGET) $(OBJS)

