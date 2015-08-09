#include "RenderTexture.h"

#include <cassert>

RenderTexture::RenderTexture(Texture const& texture) :
    id_(0),
    texture_(texture)
{
    if(texture_.data())
    {
        glGenTextures(1, &id_);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, id_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_.width(), texture_.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_.data());
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void RenderTexture::bind()
{
    assert(id_);
    glBindTexture(GL_TEXTURE_2D, id_);
}
