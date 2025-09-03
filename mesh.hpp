/*********************************
 * author     : mostafa khaled
 * date       : 
 * desc       : 
 ********************************/
#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

extern "C" {
  #include <image.h>
}

class mesh {
  public:
    bool create(std::vector<float>& vbo_data, std::vector<unsigned int>& ebo_data, unsigned int usg);
    bool add_texture(Image img, unsigned int min_filter, unsigned int mag_filter);

    virtual void setup(); //setup attributes for vertex

    void draw(unsigned int mode, unsigned int shader_program);

  public:
    unsigned int vbo = 0, ebo = 0, vao = 0;
    long vbo_count, ebo_count = 0;

    //textures[i] have texture unit i
    std::vector<unsigned int> textures = 0;

};


#endif /* !MESH_HPP */
