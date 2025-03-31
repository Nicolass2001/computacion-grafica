CXX = clang++
CXXFLAGS = -std=c++11 -Wall -DGL_SILENCE_DEPRECATION -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -framework GLUT -framework OpenGL
SRC = main.cpp
TARGET = myApp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)
