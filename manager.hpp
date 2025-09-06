/*********************************
 * author     : mostafa khaled
 * date       : 
 * desc       : 
 ********************************/
#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <unordered_map>
#include <glm/glm.hpp>

class manager
{
  public:
    void add_model(std::string modelName, glm::mat4 model);
    void add_shader(std::string shaderName, unsigned int shaderID);
    void add_shader(std::string shaderName, std::string vshader_path, std::string fshader_path);

    void add_texture(std::string texName, unsigned int texID);
    void add_texture(
        std::string texName, std::string filepath, unsigned int wrap, unsigned int min, unsigned int mag
    );

    unsigned int get_texture(std::string texName);
    unsigned int get_shader(std::string shaderName);
    glm::mat4&   get_model_ref(std::string modelName);
    glm::mat4    get_model_value(std::string modelName);

  private:
    std::unordered_map<std::string, unsigned int> textures;
    std::unordered_map<std::string, unsigned int> shaders; //shader programs
    std::unordered_map<std::string, glm::mat4>    models;  //model matrix
};

#endif /* !MANANGER_HPP */
