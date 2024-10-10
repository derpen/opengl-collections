CXX = g++
CXXFLAGS = -std=c++17 -Wall
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW

SOURCES = main.cpp glad.c libs/shaders/shader.cpp utils/shapes/shape_vertices.cpp include/stb/stb_image.cpp libs/textures/texture_loader.cpp

OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS := $(OBJECTS:.c=.o)

EXECUTABLE = cube

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJECTS)

run:
	./$(EXECUTABLE)
