#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
    using data_t = unsigned char const*;

    public:
        Texture();
        Texture(unsigned width, unsigned height, data_t data);

        unsigned width() const;
        unsigned height() const;

        data_t data() const;

    private:
        unsigned width_, height_;
        data_t data_;
};

#endif // TEXTURE_H
