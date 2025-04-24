
# FOR MAC
#--------------------------------------------------------------------
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall                             \
		   -I/opt/homebrew/opt/ncurses/include          \
		   -I./Source                                   \
		   -I./Source/Audio								\
		   -I./Source/Keyboard                          \
		   -I./Source/Menu                              \
           -I./Resources    							\
		   -I./Resources/SampleLibrary    				\

LDFLAGS = -L/opt/homebrew/opt/ncurses/lib -lncurses

# Find all .cpp files
SRCS := $(shell find . -name "*.cpp")
OBJS := $(SRCS:.cpp=.o)

# Output executable name
TARGET = main

# Default build rule
all: $(TARGET)

# Link all object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile individual .cpp files into .o object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET) audioPlayerDEBUG.txt  # Delete the .txt file here
#--------------------------------------------------------------------
