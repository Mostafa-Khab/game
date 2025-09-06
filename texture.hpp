/*********************************
 * author     : mostafa khaled
 * date       : 
 * desc       : 
 ********************************/
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

extern "C" {
#include <image.h>
}

unsigned int create_texture_from_img(
    Image img, unsigned int wrapFilter, unsigned int min, unsigned int mag
);

unsigned int create_texture_from_file(
    std::string_view filepath, unsigned int wrapFilter, unsigned int min, unsigned int mag
);

#endif /* !TEXTURES_HPP */
