#include <iostream>
#include "opengl/loop.hpp"

#ifdef _WIN32
    #include <windows.h>

    #ifdef _DEBUG
        int main(int argc, char* argv[]) {
    #else
        int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    #endif
#else
        int main(int argc, char* argv[]) {
#endif

        int success = gl_loop::init_gl(800.0f, 600.0f, "dEngine");
        if (success != 0) {
            std::cout << "An Error Occurred\n";
            return -1;
        }

        return 0;
    }