CXX = clang++
CXXFLAGS = -std=c++11 -Wall -DGL_SILENCE_DEPRECATION -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_image -framework GLUT -framework OpenGL
SRC = main.cpp
TARGET = myApp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)
