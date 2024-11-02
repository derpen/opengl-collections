CXX = g++
CXXFLAGS = -std=c++17 -Wall
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW -lassimp

IMGUI_DIRS = vendor/imgui

SOURCES = main.cpp src/glad/glad.c src/shaders/shader.cpp src/utils/shapes/shape_vertices.cpp vendor/stb/stb_image.cpp src/textures/texture_loader.cpp src/camera/fps_camera_control.cpp vendor/imgui/backends/imgui_impl_glfw.cpp vendor/imgui/backends/imgui_impl_opengl3.cpp $(wildcard $(IMGUI_DIRS)/*.cpp) src/imgui_debug_menu/imgui_debug.cpp src/input/user_input.cpp src/utils/logs/performance_log.cpp src/assimp_model_loader/mesh.cpp src/assimp_model_loader/model.cpp src/scene_framebuffer/scene_framebuffer.cpp vendor/im3d/im3d.cpp src/im3d/im3d_handler.cpp

OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS := $(OBJECTS:.c=.o)

EXECUTABLE = model_viewer

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJECTS)

run:
	./$(EXECUTABLE)
