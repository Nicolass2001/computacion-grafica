# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -DGL_SILENCE_DEPRECATION -I./hs -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_image -framework GLUT -framework OpenGL

# Folder structure
SRC_DIR = ./is
OBJ_DIR = ./os
INC_DIR = ./hs

# Main source file
MAIN_SRC = main.cpp
MAIN_OBJ = $(OBJ_DIR)/main.o

# Sources and objects
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Output binary
TARGET = myApp

# Default rule
all: $(TARGET)

# Linking final binary
$(TARGET): $(OBJECTS) $(MAIN_OBJ)
	$(CXX) $(OBJECTS) $(MAIN_OBJ) -o $@ $(LDFLAGS)

# Compile .cpp from ./is to ./os
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile main.cpp
$(MAIN_OBJ): $(MAIN_SRC)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean
