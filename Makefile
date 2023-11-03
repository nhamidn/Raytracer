# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -ggdb3 -O0 -Wall
CPPFLAGS = -I/usr/local/include/SDL2 -D_THREAD_SAFE
LDFLAGS = -L/usr/local/lib
LIBS = -lSDL2 -lSDL2_image -lm

# Target executable
TARGET = raytracer

# Source files
SRCS = main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Link object files to create the target executable
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

