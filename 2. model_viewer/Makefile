# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW -lassimp

# Directories
IMGUI_DIRS = vendor/imgui
SRC_DIR = src
VENDOR_DIR = vendor

# Source files
SOURCES = \
    main.cpp \
    $(SRC_DIR)/glad/glad.c \
    $(SRC_DIR)/shaders/shader.cpp \
    $(SRC_DIR)/utils/shapes/shape_vertices.cpp \
    $(VENDOR_DIR)/stb/stb_image.cpp \
    $(SRC_DIR)/textures/texture_loader.cpp \
    $(SRC_DIR)/camera/fps_camera_control.cpp \
    $(VENDOR_DIR)/imgui/backends/imgui_impl_glfw.cpp \
    $(VENDOR_DIR)/imgui/backends/imgui_impl_opengl3.cpp \
    $(wildcard $(IMGUI_DIRS)/*.cpp) \
    $(SRC_DIR)/imgui_debug_menu/imgui_debug.cpp \
    $(SRC_DIR)/input/user_input.cpp \
    $(SRC_DIR)/utils/logs/performance_log.cpp \
    $(SRC_DIR)/assimp_model_loader/mesh.cpp \
    $(SRC_DIR)/assimp_model_loader/model.cpp \
    $(SRC_DIR)/scene_framebuffer/scene_framebuffer.cpp \
    $(VENDOR_DIR)/im3d/im3d.cpp \
    $(SRC_DIR)/im3d/im3d_handler.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS := $(OBJECTS:.c=.o)

# Executable name
EXECUTABLE = model_viewer

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up build files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Run the executable
run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean run
