#ifndef LOADER_H
#define LOADER_H

#include <unordered_map>
#include <string>

#include <SFML/Graphics/Image.hpp>

#include "Model.h"

class Loader
{
    public:
        Model load_model(std::string const& filename);
        //Material load_material(std::string const& filename);

    private:
        Texture load_texture(std::string const& filename);

        std::unordered_map<std::string, sf::Image> images_;
};

#endif // LOADER_H
