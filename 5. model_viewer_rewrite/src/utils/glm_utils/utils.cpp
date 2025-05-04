#include "utils.hpp"
#include <iostream>

namespace GLM_Utils {

void printvec3(glm::vec3 vector){
  std::cout << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")\n";
}

}
