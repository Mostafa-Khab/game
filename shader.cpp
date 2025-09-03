#include <glad/gl.h>

#include <string>
#include <fstream>
#include <iostream>

bool loadfile(std::string filepath, std::string& src)
{
  std::ifstream file(filepath, std::fstream::binary);
  std::string line;

  src = "";

  if(!file.is_open())
  {
    std::cerr << ("ERROR:\n\tfailed to load file from specified path\n");
    return false;
  }

  while(std::getline(file, line))
  {
    src += line;
  }

  return true;

}

unsigned int create_shader_program(std::string vshader_path, std::string fshader_path)
{
  std::string vs_src_string, fs_src_string;

  loadfile(vshader_path, vs_src_string);
  loadfile(fshader_path, fs_src_string);

  const char* vshader_src = vs_src_string.data();
  const char* fshader_src = fs_src_string.data();

  unsigned int vshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vshader, 1, &vshader_src, NULL);
  glCompileShader(vshader);

  unsigned int fshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fshader, 1, &fshader_src, NULL);
  glCompileShader(fshader);

  unsigned int shader_prg = glCreateProgram();
  glAttachShader(shader_prg, vshader);
  glAttachShader(shader_prg, fshader);
  glLinkProgram(shader_prg);

  glDeleteShader(vshader);
  glDeleteShader(fshader);

  return shader_prg;
}

