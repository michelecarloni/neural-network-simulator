# Makefile for Neural Net Backpropagation Simulator

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11
DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -O3 -DNDEBUG

# Directories
SRC_DIR = source
HEADER_DIR = header
OBJ_DIR = obj
BIN_DIR = .

# Target executable
TARGET = main

# Source files (add all your .cpp files from the source directory)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Add main.cpp from the root directory
SOURCES += main.cpp

# Object files
OBJECTS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SOURCES)))

# Default target
all: $(BIN_DIR)/$(TARGET)
	@rm -rf $(OBJ_DIR)

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(BIN_DIR)/$(TARGET)
	@rm -rf $(OBJ_DIR)

# Release build
release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(BIN_DIR)/$(TARGET)
	@rm -rf &(OBJ_DIR) 

# Link
$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files in the source directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(HEADER_DIR) -c -o $@ $<

# Compile main.cpp from root directory
$(OBJ_DIR)/main.o: main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(HEADER_DIR) -c -o $@ $<

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(TARGET) *.o

# Phony targets
.PHONY: all debug release clean

# Dependencies
# Add header dependencies here
$(OBJ_DIR)/main.o: $(HEADER_DIR)/shell.h
# Add more dependencies as needed