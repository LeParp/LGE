#include "Loader.h"

#include <string>
#include <stdexcept>

#include <glm/gtx/vector_angle.hpp>

#include "Model.h"

Model Loader::load_model(std::string const& filename)
{
    Model model;

    if(filename == "player.mdl")
    {
        Node vertical_rotor;
        Mesh mesh(vertical_rotor);

        // Vertices d'un cube, sans texcoords
        mesh.vertices() = {
                              {{-1.0, -1.0, -1.0}, {0.0, -1.0, 0.0}}, {{1.0, -1.0, -1.0}, {0.0, -1.0, 0.0}}, {{-1.0, -1.0, 1.0}, {0.0, -1.0, 0.0}},
                              {{-1.0, -1.0, 1.0}, {0.0, -1.0, 0.0}}, {{1.0, -1.0, -1.0}, {0.0, -1.0, 0.0}}, {{1.0, -1.0, 1.0}, {0.0, -1.0, 0.0}},

                              {{-1.0, 1.0, -1.0}, {0.0, 0.0, -1.0}}, {{1.0, 1.0, -1.0}, {0.0, 0.0, -1.0}}, {{-1.0, -1.0, -1.0}, {0.0, 0.0, -1.0}},
                              {{-1.0, -1.0, -1.0}, {0.0, 0.0, -1.0}}, {{1.0, 1.0, -1.0}, {0.0, 0.0, -1.0}}, {{1.0, -1.0, -1.0}, {0.0, 0.0, -1.0}},

                              {{-1.0, 1.0, -1.0}, {0.0, 1.0, 0.0}}, {{1.0, 1.0, -1.0}, {0.0, 1.0, 0.0}}, {{-1.0, 1.0, 1.0}, {0.0, 1.0, 0.0}},
                              {{-1.0, 1.0, 1.0}, {0.0, 1.0, 0.0}}, {{1.0, 1.0, -1.0}, {0.0, 1.0, 0.0}}, {{1.0, 1.0, 1.0}, {0.0, 1.0, 0.0}},

                              {{-1.0, 1.0, 1.0}, {0.0, 0.0, 1.0}}, {{1.0, 1.0, 1.0}, {0.0, 0.0, 1.0}}, {{-1.0, -1.0, 1.0}, {0.0, 0.0, 1.0}},
                              {{-1.0, -1.0, 1.0}, {0.0, 0.0, 1.0}}, {{1.0, 1.0, 1.0}, {0.0, 0.0, 1.0}}, {{1.0, -1.0, 1.0}, {0.0, 0.0, 1.0}},

                              {{-1.0, 1.0, -1.0}, {-1.0, 0.0, 0.0}}, {{-1.0, 1.0, 1.0}, {-1.0, 0.0, 0.0}}, {{-1.0, -1.0, -1.0}, {-1.0, 0.0, 0.0}},
                              {{-1.0, -1.0, -1.0}, {-1.0, 0.0, 0.0}}, {{-1.0, 1.0, 1.0}, {-1.0, 0.0, 0.0}}, {{-1.0, -1.0, 1.0}, {-1.0, 0.0, 0.0}},

                              {{1.0, 1.0, -1.0}, {1.0, 0.0, 0.0}}, {{1.0, 1.0, 1.0}, {1.0, 0.0, 0.0}}, {{1.0, -1.0, -1.0}, {1.0, 0.0, 0.0}},
                              {{1.0, -1.0, -1.0}, {1.0, 0.0, 0.0}}, {{1.0, 1.0, 1.0}, {1.0, 0.0, 0.0}}, {{1.0, -1.0, 1.0}, {1.0, 0.0, 0.0}}
                          };

        // Couleur turquoise
        mesh.material().diffuse_color() = {0.1, 0.4, 0.2};
        mesh.material().specular_color() = {0.1, 0.4, 0.2};

        mesh.material().shininess() = 32.0; // Reflets diffus
        mesh.material().textured() = false; // Pas de texture

        Node horizontal_rotor(vertical_rotor);
        Camera camera(horizontal_rotor);

        vertical_rotor.translate({0.0, -1.0, 0.0});
        horizontal_rotor.translate({0.0, 0.0, -2.0});
        camera.translate({0.0, 0.0, 6.0});

        model.add_mesh("Body", std::move(mesh));
        model.add_camera("Camera", std::move(camera));
        model.add_node("Vertical_rotor", std::move(vertical_rotor));
        model.add_node("Horizontal_rotor", std::move(horizontal_rotor));
    }

    else if(filename == "terrain.mdl")
    {
        Mesh mesh;

        // Vertices d'un plan horizontal, avec texcoords
        mesh.vertices() = {
                              {{-10.0, 0.0, -10.0}, {0.0, 1.0, 0.0}, {0.0, 0.0}},
                              {{10.0, 0.0, -10.0}, {0.0, 1.0, 0.0}, {1.0, 0.0}},
                              {{10.0, 0.0, 10.0}, {0.0, 1.0, 0.0}, {1.0, 1.0}},

                              {{-10.0, 0.0, -10.0}, {0.0, 1.0, 0.0}, {0.0, 0.0}},
                              {{10.0, 0.0, 10.0}, {0.0, 1.0, 0.0}, {1.0, 1.0}},
                              {{-10.0, 0.0, 10.0}, {0.0, 1.0, 0.0}, {0.0, 1.0}}
                          };

        mesh.material().diffuse_color() = {1.0, 0.6, 0.0};
        mesh.material().specular_color() = {1.0, 1.0, 1.0};
        mesh.material().shininess() = 128.0;
        mesh.material().textured() = true;
        mesh.material().diffuse_texture() = load_texture("Texture.png");
        mesh.material().specular_texture() = load_texture("Texture.png");
        mesh.translate({0.0, -2.0, 0.0});

        Light light;
        light.color() = {1.0, 1.0, 1.0};
        light.attenuations() = {1.0, 0.045, 0.0075};
        light.translate({0.0, -1.0, -1.0});

        Light light2;
        light2.color() = {1.0, 0.0, 1.0};
        light2.attenuations() = {1.0, 0.045, 0.0075};
        light2.translate({0.0, 1.0, 1.0});

        Light light3;
        light3.color() = {1.0, 0.0, 0.0};
        light3.attenuations() = {1.0, 0.045, 0.0075};
        light3.translate({4.0, 0.0, -4.0});

        model.add_mesh("Terrain", std::move(mesh));
        model.add_light("Light", std::move(light));
        model.add_light("Light2", std::move(light2));
        model.add_light("Light3", std::move(light3));
    }

    return model;
}

Texture Loader::load_texture(std::string const& filename)
{
    // Chargement de la texture si elle n'existe pas
    if(images_.find(filename) == images_.end())
    {
        sf::Image& image = images_[filename];

        if(!image.loadFromFile(filename))
            throw std::runtime_error("Unable to load image file " + filename);
        image.flipVertically(); // OpenGL utilise des textures inversées
    }

    sf::Image& image = images_[filename];
    return Texture(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}
