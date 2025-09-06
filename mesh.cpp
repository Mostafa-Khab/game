#include <filesystem>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <iostream>
#include <vector>

#include "mesh.hpp"
#include "texture.hpp"

bool mesh::create(std::vector<float>& vbo_data, std::vector<unsigned int>& ebo_data, unsigned int usg){
  if(vbo_data.empty()) {
    std::cerr << "MESH ERROR: " << "vbo must have data to create a mesh\n";
    return false;
  }

  glCreateVertexArrays(1, &vao);

  glCreateBuffers(1, &vbo);
  glNamedBufferData(vbo, vbo_data.size() * sizeof(float), vbo_data.data(), usg);

  if(!ebo_data.empty())
  {
    glCreateBuffers(1, &ebo);
    glNamedBufferData(ebo, ebo_data.size() * sizeof(unsigned int), ebo_data.data(), usg);
    glVertexArrayElementBuffer(vao, ebo);
  }

  //glVertexArrayVertexBuffer(vao, 0, vbo, 0, stride) //should be in setup function
  //
  vbo_count = vbo_data.size();
  ebo_count = ebo_data.size();

  return true;
}

bool mesh::add_texture(Image img, unsigned int wrap_filter, unsigned int min, unsigned int mag){
  unsigned int texture;
  glCreateTextures(GL_TEXTURE_2D, 1, &texture);
  glBindTextureUnit(0, texture);

  if(!texture)
  {
    std::cerr << "MESH ERROR: failed to add texture\n"; 
    return false;
  }

  glTextureParameteri(texture, GL_TEXTURE_WRAP_S, wrap_filter );
  glTextureParameteri(texture, GL_TEXTURE_WRAP_T, wrap_filter );
  glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, min);
  glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, mag);

  glTextureStorage2D(texture, 1, GL_RGBA8, img.w, img.h);
  glTextureSubImage2D(texture, 0, 0, 0, img.w, img.h, GL_RGBA, GL_UNSIGNED_BYTE, img.data);

  textures.push_back(texture);
  return true;
}

bool mesh::add_texture(
    std::string_view filepath, unsigned int wrap_filter, unsigned int min, unsigned int mag
) {
  //Image img;
  //Image_load(&img, filepath.data());

  //unsigned int texture;
  //glCreateTextures(GL_TEXTURE_2D, 1, &texture);
  //glBindTextureUnit(0, texture);

  //if(!texture)
  //{
  //  std::cerr << "MESH ERROR: failed to add texture\n"; 
  //  return false;
  //}

  //glTextureParameteri(texture, GL_TEXTURE_WRAP_S, wrap_filter );
  //glTextureParameteri(texture, GL_TEXTURE_WRAP_T, wrap_filter );
  //glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, min);
  //glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, mag);

  //glTextureStorage2D(texture, 1, GL_RGBA8, img.w, img.h);
  //glTextureSubImage2D(texture, 0, 0, 0, img.w, img.h, GL_RGBA, GL_UNSIGNED_BYTE, img.data);

  unsigned int texture = create_texture_from_file(filepath, wrap_filter, min,mag);

  if(texture)
    textures.push_back(texture);
  else
    std::cerr << "MESH ERROR: failed to add texture\n"; 

  return true;
}

bool mesh::add_texture(unsigned int texID)
{
  if(!texID)
    return false;

  textures.push_back(texID);
  return true;
}

void mesh::draw(unsigned int mode, unsigned int shader_program){
  glUseProgram(shader_program);

  if(!textures.empty()) {
    for(int i = 0; i < textures.size(); ++i) {
      glBindTextureUnit(i, textures[i]);
    }

    for(int i = 0; i < textures.size(); ++i) {
      glUniform1i( glGetUniformLocation(shader_program, ("u_tex" + std::to_string(i)).c_str()), i);
    }
    
  }

  glBindVertexArray(vao);

    if(ebo) {
      glDrawElements(mode, ebo_count, GL_UNSIGNED_INT, NULL);
    } else {
      glDrawArrays(mode, 0, vbo_count);
    }

    //if(!textures.empty()) {
    //  for(int i = 0; i < textures.size(); ++i) {
    //    glBindTextureUnit(i, 0);
    //  }
    //}
  
  glBindVertexArray(0);
  
}

void mesh::onClean()
{
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);

  if(ebo)
    glDeleteBuffers(1, &ebo);

  //removed due to adding a resource manager.
  //glDeleteTextures(textures[textures.size() - 1], &textures[textures.size() - 1]);
}

void mesh::nuke()
{
  onClean();
  clean();
}
