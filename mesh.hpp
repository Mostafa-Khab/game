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
    bool add_texture(Image img, unsigned int wrap_filter, unsigned int min, unsigned int mag);
    bool add_texture(std::string_view filepath, unsigned int wrap_filter, unsigned int min, unsigned int mag);
    bool add_texture(unsigned texID);

    void draw(unsigned int mode, unsigned int shader_program);
    void nuke();

    virtual void setup() = 0; //setup attributes for vertex
    virtual void clean(){};

  private:
    void onClean();

  public:
    unsigned int vbo = 0, ebo = 0, vao = 0;
    long vbo_count, ebo_count = 0;

    //textures[i] have texture unit i
    std::vector<unsigned int> textures;

};


#endif /* !MESH_HPP */
