CXX = g++
CXXFLAGS = -std=c++17 -Wall
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW -lassimp

SRC_DIR = src
LIB_DIR = lib

SOURCES = \
	$(LIB_DIR)/glad/glad.c \
	$(LIB_DIR)/stb/stb_image.cpp \
	$(SRC_DIR)/assimp/mesh.cpp \
	$(SRC_DIR)/assimp/model.cpp \
	$(SRC_DIR)/opengl/loop.cpp \
	$(SRC_DIR)/opengl/config.cpp \
	$(SRC_DIR)/scene/camera.cpp \
	$(SRC_DIR)/scene/object.cpp \
	$(SRC_DIR)/scene/scene.cpp \
	$(SRC_DIR)/input/input.cpp \
	$(SRC_DIR)/utils/shapes/shapes.cpp \
	$(SRC_DIR)/utils/glm_utils/utils.cpp \
	$(SRC_DIR)/utils/textures/textures.cpp \
	$(SRC_DIR)/main.cpp \

OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS := $(OBJECTS:.c=.o)

EXECUTABLE = model

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJECTS)

run:
	./$(EXECUTABLE)
