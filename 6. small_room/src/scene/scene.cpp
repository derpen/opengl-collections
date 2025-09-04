#include "scene.hpp"
#include <glad/glad.h>
#include <string>
#include <map>
#include "../scene/camera.hpp"
#include "../utils/shapes/shapes.hpp"
#include "../utils/textures/textures.hpp"

#ifdef _WIN32
    #include <glfw/glfw3.h>
#elif defined(__linux__)
	#include <GLFW/glfw3.h>
#endif

namespace Scene {

    std::unordered_map<std::string, GameObject> Objects;
	std::unordered_map<std::string, Light> Lights;

	void DrawScene(float deltaTime){

		//// Testing some transform, there's only one object right now (Osaka)
		//glm::mat4 newModelMatrix = glm::rotate(
		//    Objects[0].transform.GetModelMatrix(),
		//    static_cast<float>(glfwGetTime()),
		//    glm::vec3(0.0, 1.0, 0.0)
		//);
		//Objects[0].transform.setModelMatrix(newModelMatrix);

		//// What if I rotate it like so?
		//Objects[0].transform.rotation.y += deltaTime; // Works apparently


		// Testing light around camera
		Lights["PointLight1"].transform.position = Camera::Position;


		//TODO: why did I do this again?
		DrawObjects();

	}

	void AddObjectToScene(){

	}

	void AddCube(
	  std::string name, // TODO: need to automate this
	  const std::string& texturePath,
	  glm::vec3 position,
	  glm::vec3 rotation,
	  glm::vec3 scale
	){
	  bool useTexture = false;
	  if(!texturePath.empty()) {
		useTexture = true;
	  }

	  Shader new_shader(PROJECT_DIR"../assets/shaders/cube.vert", PROJECT_DIR"../assets/shaders/cube.frag");

	  // TODO: need a way to handle textureless object, do it in the shader
	  unsigned int texture1 = 0;
	  if(useTexture){
		texture1 = TextureHandler::read_texture(texturePath.c_str());
	  }

	  Transform transform;
	  transform.position = position;
	  transform.rotation = rotation;
	  transform.scale = scale;

	  GameObject new_object;

	  if(name.empty()){
		new_object.name = "cube";
	  } else {
		new_object.name = name;
	  }

	  // If not initialized
	 
	  if(Shapes::cube_VAO == 0){
		(void)Shapes::init_cube(); // (void) because return value not used
	  }

	  new_object.ObjectVAO = Shapes::cube_VAO;
	  new_object.ObjectShader = new_shader;
	  new_object.transform = transform;

	  ObjectMaterial object_material;

	  object_material.diffuseMap = texture1;
	  object_material.object_shininess = 32.0f;
	  object_material.object_specular = glm::vec3(1.0f);
	  object_material.object_diffuse = glm::vec3(1.0f, 0.0f, 0.0f);

	  new_object.material = object_material;

	  //Objects.push_back(new_object);
	  Objects.emplace(new_object.name, new_object); // @Fix: This will break
	}

	void AddPointLight(std::string lightName, glm::vec3 position){
	  Light new_light;
	  new_light.name = lightName.c_str();

	  Transform transform;
	  transform.position = position;
	  transform.rotation = glm::vec3(0.0f);
	  transform.scale = glm::vec3(1.0f);

	  new_light.transform = transform;


	  // Need a better way to handle directory
	  // Probably in release mode could have the assets directory directly copied inside the final folder
	  Shader point_light(PROJECT_DIR"../assets/shaders/light_cube.vert", PROJECT_DIR"../assets/shaders/light_cube.frag");
	  new_light.ObjectShader = point_light;

	  LightMaterial default_mat;
	  default_mat.light_specular = glm::vec3(1.0f);

	  // For now just white
	  glm::vec3 lightColor = glm::vec3(1.0f);
	  glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // decrease the influence
	  glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
	  default_mat.lightColor = lightColor;
	  default_mat.diffuseColor = diffuseColor;
	  default_mat.ambientColor = ambientColor;

	  default_mat.light_constant = 1.0f;
	  default_mat.light_linear = 0.09f;
	  default_mat.light_quadratic = 0.032f;

	  new_light.material = default_mat;
	  new_light.lightType = Light::LightType::POINT;

	  // If not initialized
	  if(Shapes::cube_VAO == 0){
		(void)Shapes::init_cube(); // (void) because return value not used
	  }

	  new_light.ObjectVAO = Shapes::cube_VAO;

	  Lights.emplace(new_light.name, new_light); // Trying map
	}

	void AddDirLight(
		std::string lightName, 
		glm::vec3 direction,
		glm::vec3 ambient,
		glm::vec3 diffuse,
		glm::vec3 specular
	) {
		Light new_light;
		new_light.name = lightName.c_str();

		Transform transform;
		transform.direction = direction;
		transform.rotation = glm::vec3(0.0f);
		transform.scale = glm::vec3(1.0f);

		new_light.transform = transform;

		// Need a better way to handle directory
		// Probably in release mode could have the assets directory directly copied inside the final folder
		Shader point_light(PROJECT_DIR"../assets/shaders/light_cube.vert", PROJECT_DIR"../assets/shaders/light_cube.frag");
		new_light.ObjectShader = point_light;

		LightMaterial default_mat;
		default_mat.light_specular = specular;

		// For now just white
		glm::vec3 lightColor = glm::vec3(1.0f);
		glm::vec3 diffuseColor = lightColor   * diffuse; // decrease the influence
		glm::vec3 ambientColor = diffuseColor * ambient; // low influence
		default_mat.lightColor = lightColor;
		default_mat.diffuseColor = diffuseColor;
		default_mat.ambientColor = ambientColor;

		new_light.material = default_mat;
		new_light.lightType = Light::LightType::DIRECTIONAL;

		Lights.emplace(new_light.name, new_light);
	}

	void AddModelToScene(std::string modelName, std::string modelDirectory, std::string VertexShader, std::string FragmentShader, bool flipImage){
	  Model new_model(modelDirectory.c_str());
	  Shader new_shader(VertexShader.c_str(), FragmentShader.c_str());

	  GameObject new_object;
	  new_object.name = modelName.c_str();
	  new_object.ObjectShader = new_shader;
	  new_object.useModel = true;
	  new_object.modelMesh = new_model;

	  Transform transform;
	  transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
	  transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	  transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	  new_object.transform = transform;

	  // TODO:
	  // Need to handle this somewhere else at some point
	  ObjectMaterial object_material;
	  object_material.object_shininess = 32.0f;
	  object_material.object_specular = glm::vec3(1.0f);
	  object_material.object_diffuse = glm::vec3(1.0f, 0.0f, 0.0f);
	  new_object.material = object_material;

	  //Objects.push_back(new_object);
	  Objects.emplace(new_object.name, new_object); // @Fix: This will break
	}

	void DrawObjects(){
	  //for(long unsigned int i=0; i<Objects.size(); i++){
		//for (auto& it: Objects){
		for (auto& [objectName, gameObject] : Objects) {
			//GameObject currentObject = Objects[i];
			GameObject currentObject = gameObject;
			HandleShaderUniforms(currentObject);

			if(currentObject.useModel){
			  currentObject.modelMesh.Draw(currentObject.ObjectShader);
			} else {
			  if(currentObject.material.diffuseMap!= 0){
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, currentObject.material.diffuseMap);
			  } else {
				glBindTexture(GL_TEXTURE_2D, 0);
			  }

			  glBindVertexArray(currentObject.ObjectVAO);
			  glDrawArrays(GL_TRIANGLES, 0, 36); // TODO: handle this shit, for now we just draw cubes
			  /*glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/
			}
	  }

	  //for(long unsigned int i=0; i<Lights.size(); i++){
	  for(auto& [lightName, lightObject]: Lights) {
		  Light currentLight = lightObject;
		  HandleShaderUniforms(currentLight);

		  // Just disable the cube rendering for now
		  // They really should be two different things lol
		  if (currentLight.enabled) {
			  glBindVertexArray(currentLight.ObjectVAO);
			  glDrawArrays(GL_TRIANGLES, 0, 36);
		  }
	  }
	}

	/*void HandleLights(){*/
	/*  for(int i=0; i<Lights.size(); i++){*/
	/**/
	/*  }*/
	/*}*/

	void HandleShaderUniforms(GameObject currentObject){
	  Shader currentShader = currentObject.ObjectShader;
	  currentShader.use();
	  currentShader.setMat4("projection", Camera::GetProjectionMatrix());
	  currentShader.setMat4("view", Camera::GetViewMatrix());
	  currentShader.setInt("material.diffuse", 0);

	  glm::mat4 model = currentObject.transform.GetModelMatrix();
	  currentShader.setMat4("model", model);

	  //for(long unsigned int i=0; i<Lights.size(); i++){
	  for(auto& [lightName, lightObject]: Lights) {
		HandleLightingUniforms(currentShader, lightObject, currentObject);
	  }
	}

	void HandleShaderUniforms(Light currentLight){
	  Shader currentShader = currentLight.ObjectShader;
	  currentShader.use();
	  currentShader.setMat4("projection", Camera::GetProjectionMatrix());
	  currentShader.setMat4("view", Camera::GetViewMatrix());
	  currentShader.setInt("material.diffuse", 0);

	  glm::mat4 model = currentLight.transform.GetModelMatrix();
	  currentShader.setMat4("model", model);
	}

	void HandleLightingUniforms(Shader currentShader, Light currentLight, GameObject currentObject){
	  currentShader.use(); // Is using it again necessary lol
	  if (currentLight.lightType == Light::LightType::POINT) {
		  // Some bullshit with ambient
		  // This codebase has become too unmanageable, rewrite soon once I understand OpenGL more
		  currentShader.setFloat("ambientStrength", 0.5f);
		  currentShader.setVec3("ambientColor", glm::vec3(0.5f, 0.5f, 0.5f));
		  currentShader.setVec3("material.specular", currentObject.material.object_specular);
		  currentShader.setFloat("material.shininess", currentObject.material.object_shininess);
		  glm::mat4 lightModel = currentLight.transform.GetModelMatrix(); // This feels so ugly lol
		  currentShader.setVec3("pointLight.position", glm::vec3(lightModel[3]));
		  currentShader.setVec3("viewPos", Camera::Position); // TODO: can this be cached somehow?
		  currentShader.setVec3("pointLight.lightColor", currentLight.material.lightColor);
		  currentShader.setVec3("pointLight.diffuse", currentLight.material.diffuseColor);
		  currentShader.setVec3("pointLight.ambient", currentLight.material.ambientColor);
		  currentShader.setVec3("pointLight.specular", currentLight.material.light_specular);
		  currentShader.setFloat("pointLight.constant", currentLight.material.light_constant);
		  currentShader.setFloat("pointLight.linear", currentLight.material.light_linear);
		  currentShader.setFloat("pointLight.quadratic", currentLight.material.light_quadratic);
	  }
	  else if (currentLight.lightType == Light::LightType::DIRECTIONAL) {
		  currentShader.setVec3("dirLight.direction", currentLight.transform.direction);
		  currentShader.setVec3("dirLight.ambient", currentLight.material.ambientColor);
          currentShader.setVec3("dirLight.diffuse", currentLight.material.diffuseColor);
          currentShader.setVec3("dirLight.specular", currentLight.material.light_specular);
	  }
	}
}
