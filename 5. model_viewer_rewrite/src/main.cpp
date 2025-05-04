#include "iostream"
#include "opengl/loop.hpp"

int main(){
  int success = gl_loop::init_gl(800.0f, 600.0f, "dEngine");
  if(success != 0){
    std::cout << "An Error Occured\n";
    return -1;
  }

  return 0;
}
