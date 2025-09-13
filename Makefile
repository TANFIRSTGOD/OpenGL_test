# Compiler
CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra

# Source files
SRC = src/main.cpp src/glad.c

# Output binary
TARGET = main.exe

# Libraries (OpenGL + GLFW + GDI)
LIBS = -Llib -lopengl32 -lglfw3dll -lgdi32

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	del $(TARGET) *.o 2>nul || true
