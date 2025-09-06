#include "manager.hpp"
#include "shader.hpp"

void manager::add_texture(std::string name, unsigned int texID)
{
  textures[name] = texID;
}

void manager::add_shader(std::string name, unsigned int shaderID){
  shaders[name] = shaderID;
}

void manager::add_shader(std::string name, std::string vshader_path, std::string fshader_path) {
  unsigned int shaderID = create_shader_program(vshader_path, fshader_path);
  shaders[name] = shaderID;
}

void manager::add_model(std::string name, glm::mat4 model) {
  models[name] = model;
}

unsigned int manager::get_texture(std::string texName){
  return textures[texName];
}

unsigned int manager::get_shader(std::string shaderName){
  return shaders[shaderName];
}

glm::mat4& manager::get_model_ref(std::string modelName){
    return models[modelName];
}

glm::mat4    manager::get_model_value(std::string modelName){
    return models[modelName];
}

