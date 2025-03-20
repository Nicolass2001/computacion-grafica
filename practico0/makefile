# Compiler and flags
CXX = g++
CXXFLAGS = -I./hs -Wall -Wextra -std=c++17

# Folder structure
SRC_DIR = ./is
OBJ_DIR = ./os
INC_DIR = ./hs

# Main source file in the root folder
MAIN_SRC = main.cpp

# Sources and objects
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
MAIN_OBJ = $(OBJ_DIR)/main.o

# Output binary
TARGET = main

# Default rule
all: $(TARGET)

# Linking the binary
$(TARGET): $(OBJECTS) $(MAIN_OBJ)
	$(CXX) $(OBJECTS) $(MAIN_OBJ) -o $@

# Compiling .cpp files into .o files (from ./is folder)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compiling main.cpp into an .o file (from root folder)
$(OBJ_DIR)/main.o: $(MAIN_SRC)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleaning build files
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Phony targets
.PHONY: all clean
