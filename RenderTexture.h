#ifndef RENDERTEXTURE_H
#define RENDERTEXTURE_H

#include <GL/glew.h>

#include "Texture.h"

class RenderTexture
{
    public:
        RenderTexture(Texture const& texture);
        RenderTexture(Texture&& texture) = delete;

        void bind();

    private:
        GLuint id_;
        Texture const& texture_;
};

#endif // RENDERTEXTURE_H
