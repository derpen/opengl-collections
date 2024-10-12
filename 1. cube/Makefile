CXX = g++
CXXFLAGS = -std=c++17 -Wall
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW

IMGUI_DIRS = include/imgui

SOURCES = main.cpp glad.c libs/shaders/shader.cpp utils/shapes/shape_vertices.cpp include/stb/stb_image.cpp libs/textures/texture_loader.cpp libs/camera/fps_camera_control.cpp include/imgui/backends/imgui_impl_glfw.cpp include/imgui/backends/imgui_impl_opengl3.cpp $(wildcard $(IMGUI_DIRS)/*.cpp) libs/imgui_debug_menu/imgui_debug.cpp libs/input/user_input.cpp

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
