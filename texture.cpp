#include <iostream>

#include <glad/gl.h>

#include "texture.hpp"

unsigned int create_texture_from_file(
    std::string_view filepath, unsigned int wrapFilter, unsigned int min, unsigned int mag
) {
  Image img;
  Image_load(&img, filepath.data());

  unsigned int texture;
  glCreateTextures(GL_TEXTURE_2D, 1, &texture);
  glBindTextureUnit(0, texture);

  if(!texture)
  {
    std::cerr << "MESH ERROR: failed to add texture\n"; 
    return false;
  }

  glTextureParameteri(texture, GL_TEXTURE_WRAP_S, wrapFilter );
  glTextureParameteri(texture, GL_TEXTURE_WRAP_T, wrapFilter );
  glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, min);
  glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, mag);

  glTextureStorage2D(texture, 1, GL_RGBA8, img.w, img.h);
  glTextureSubImage2D(texture, 0, 0, 0, img.w, img.h, GL_RGBA, GL_UNSIGNED_BYTE, img.data);

  return texture;
}

unsigned int create_texture_from_img(
    Image img, unsigned int wrapFilter, unsigned int min, unsigned int mag
) {
  unsigned int texture;
  glCreateTextures(GL_TEXTURE_2D, 1, &texture);
  glBindTextureUnit(0, texture);

  if(!texture)
  {
    std::cerr << "MESH ERROR: failed to add texture\n"; 
    return false;
  }

  glTextureParameteri(texture, GL_TEXTURE_WRAP_S, wrapFilter );
  glTextureParameteri(texture, GL_TEXTURE_WRAP_T, wrapFilter );
  glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, min);
  glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, mag);

  glTextureStorage2D(texture, 1, GL_RGBA8, img.w, img.h);
  glTextureSubImage2D(texture, 0, 0, 0, img.w, img.h, GL_RGBA, GL_UNSIGNED_BYTE, img.data);

  return texture;
}
