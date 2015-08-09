#include "Texture.h"

#include <cassert>

Texture::Texture() :
    width_(0),
    height_(0),
    data_(nullptr)
{

}

Texture::Texture(unsigned width, unsigned height, data_t data) :
    width_(width),
    height_(height),
    data_(data)
{

}


unsigned Texture::width() const
{
    return width_;
}

unsigned Texture::height() const
{
    return height_;
}


Texture::data_t Texture::data() const
{
    return data_;
}
