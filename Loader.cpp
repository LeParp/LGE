#include "Loader.h"

#include <string>
#include <stdexcept>
#include <iostream>

#include "Model.h"

Model Loader::load_model(std::string const& filename)
{
    Model model;

    if(filename == "player.mdl")
    {
        Mesh mesh;
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
        mesh.material().diffuse_color() = {0.1, 0.4, 0.2};
        mesh.material().specular_color() = {0.1, 0.4, 0.2};
        mesh.material().shininess() = 32.0;
        mesh.material().textured() = false;
        mesh.translate({0.0, 0.0, 3.0});
        model.add_mesh("Body", std::move(mesh));

        Camera camera;
        Node camera_parent;

        camera.look_at({0.0, 0.0, 0.0}, {0.0, 0.0, -1.0}, {0.0, 1.0, 0.0});
        camera.attach(camera_parent);

        model.add_camera("Camera", std::move(camera));
        model.add_node("Camera_parent", std::move(camera_parent));
    }

    else if(filename == "terrain.mdl")
    {
        Mesh mesh;
        /*mesh.vertices() = {
                              {{-1.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0}},
                              {{1.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0}},
                              {{1.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0}},

                              {{-1.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0}},
                              {{1.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0}},
                              {{-1.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0}}
                          };*/

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
        model.add_mesh("Ground", std::move(mesh));

        Light light;
        light.color() = {1.0, 1.0, 1.0};
        light.attenuations() = {1.0, 0.045, 0.0075};
        light.translate({0.0, -1.0, -1.0});
        model.add_light("Light", std::move(light));

        Light light2;
        light2.color() = {1.0, 0.0, 1.0};
        light2.attenuations() = {1.0, 0.045, 0.0075};
        light2.translate({0.0, 1.0, 1.0});
        model.add_light("Light2", std::move(light2));

        Light light3;
        light3.color() = {1.0, 0.0, 0.0};
        light3.attenuations() = {1.0, 0.045, 0.0075};
        light3.translate({4.0, 0.0, -4.0});
        model.add_light("Light3", std::move(light3));
    }

    return model;
}

Texture Loader::load_texture(std::string const& filename)
{
    if(images_.find(filename) == images_.end())
    {
        images_.insert({filename, sf::Image()});
        sf::Image& image = images_[filename];

        if(!image.loadFromFile(filename))
            throw std::runtime_error("Unable to load image file " + filename);
        image.flipVertically();
    }

    sf::Image& image = images_[filename];
    return Texture(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}
