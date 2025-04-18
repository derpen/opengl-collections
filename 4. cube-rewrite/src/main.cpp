#include "iostream"
#include "opengl/loop.hpp"

int main(){
  int success = gl_loop::init_gl(800, 600, "dEngine");
  if(success != 0){
    std::cout << "An Error Occured\n";
    return -1;
  }

  return 0;
}
