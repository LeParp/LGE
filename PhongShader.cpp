#include "PhongShader.h"

#include <regex>

PhongShader::PhongShader(unsigned lights_count)
{
    std::string vertex_source = R"(
        #version 330 core
        #line 9

        layout (location = 0) in vec3 vertex_position_M;
        layout (location = 1) in vec3 vertex_normal_M;
        layout (location = 2) in vec2 vertex_texcoords;

        out vec3 fragment_position_E;
        out vec3 fragment_normal_E;
        out vec2 fragment_texcoords;

        uniform mat4 Projection, View, Model;

        void main()
        {
            fragment_position_E = vec3(View * Model * vec4(vertex_position_M, 1.0));
            fragment_normal_E = vec3(View * Model * vec4(vertex_normal_M, 0.0));
            fragment_texcoords = vertex_texcoords;

            gl_Position = Projection * View * Model * vec4(vertex_position_M, 1.0);
        }
    )";

    std::string fragment_source = R"(
        #version 330 core
        #line 33

        in vec3 fragment_position_E;
        in vec3 fragment_normal_E;
        in vec2 fragment_texcoords;

        out vec4 final_color;

        uniform struct
        {
            vec3 position;
            vec3 color;
            vec3 attenuations;
        } Lights[$lights_count];

        uniform struct
        {
            sampler2D diffuse_texture;
            sampler2D specular_texture;

            vec3 diffuse_color;
            vec3 specular_color;
            float shininess;
            bool textured;
        } Material;

        uniform mat4 View;

        vec3 light_impact(int n, vec3 material_diffuse, vec3 material_specular)
        {
            float ambient_impact = 0.03;
            vec3 ambient_color = material_diffuse * (ambient_impact * Lights[n].color);

            vec3 light_position_W = Lights[n].position;
            vec3 light_position_E = vec3(View * vec4(light_position_W, 1.0));
            vec3 light_direction_E = normalize(light_position_E - fragment_position_E);

            float diffuse_impact = max(dot(fragment_normal_E, light_direction_E), 0.0);
            vec3 diffuse_color = material_diffuse * (diffuse_impact * Lights[n].color);

            //vec3 reflection_direction_E = reflect(-light_direction_E, fragment_normal_E);
            vec3 eye_direction_E = normalize(-fragment_position_E);
            vec3 halfway_direction_E = normalize(light_direction_E + eye_direction_E);

            float specular_impact = pow(max(dot(halfway_direction_E, fragment_normal_E), 0.0), Material.shininess);
            vec3 specular_color = material_specular * (specular_impact * Lights[n].color);

            float d = length(light_position_E - fragment_position_E);
            float attenuation = 1.0 / (Lights[n].attenuations[0] + Lights[n].attenuations[1] * d + Lights[n].attenuations[2] * (d * d));
            //float attenuation = 1.0 / (d * d);

            return ambient_color + attenuation * (diffuse_color + specular_color);
        }

        void main()
        {
            float gamma = 2.2;

            vec3 material_diffuse = Material.diffuse_color;
            vec3 material_specular = Material.specular_color;

            if(Material.textured)
            {
                material_diffuse *= pow(texture(Material.diffuse_texture, fragment_texcoords).rgb, vec3(gamma));
                material_specular *= pow(texture(Material.specular_texture, fragment_texcoords).rgb, vec3(gamma));
            }

            final_color = vec4(0.0, 0.0, 0.0, 1.0);

            for(int i = 0; i < $lights_count; ++i)
            {
                final_color.rgb += light_impact(i, material_diffuse, material_specular);
            }

            /*if(fragment_position_E.x >= 0.0)
                final_color.rgb /= 3.0;*/

            final_color.rgb = pow(final_color.rgb, vec3(1.0 / gamma));
        }
    )";

    fragment_source = std::regex_replace(fragment_source, std::regex("\\$lights_count"), std::to_string(lights_count));

    compile(vertex_source, fragment_source);

    locations_[PROJECTION] = glGetUniformLocation(program(), "Projection");
    locations_[VIEW] = glGetUniformLocation(program(), "View");
    locations_[MODEL] = glGetUniformLocation(program(), "Model");

    locations_[MATERIAL_DIFFUSE_COLOR] = glGetUniformLocation(program(), "Material.diffuse_color");
    locations_[MATERIAL_SPECULAR_COLOR] = glGetUniformLocation(program(), "Material.specular_color");
    locations_[MATERIAL_SHININESS] = glGetUniformLocation(program(), "Material.shininess");
    locations_[MATERIAL_TEXTURED] = glGetUniformLocation(program(), "Material.textured");

    glUniform1i(glGetUniformLocation(program(), "Material.diffuse_texture"), MATERIAL_DIFFUSE);
    glUniform1i(glGetUniformLocation(program(), "Material.specular_texture"), MATERIAL_SPECULAR);

    for(GLuint i = 0; i < lights_count; ++i)
    {
        array_locations_[LIGHT_POSITION].push_back(glGetUniformLocation(program(), ("Lights[" + std::to_string(i) + "].position").c_str()));
        array_locations_[LIGHT_COLOR].push_back(glGetUniformLocation(program(), ("Lights[" + std::to_string(i) + "].color").c_str()));
        array_locations_[LIGHT_ATTENUATIONS].push_back(glGetUniformLocation(program(), ("Lights[" + std::to_string(i) + "].attenuations").c_str()));
    }
}

PhongShader::PhongShader(PhongShader&& other)
{
    *this = std::move(other);
}


PhongShader& PhongShader::operator=(PhongShader&& other)
{
    Shader::operator=(std::move(other));
    locations_ = std::move(other.locations_);
    array_locations_ = std::move(other.array_locations_);

    return *this;
}


void PhongShader::projection(glm::mat4 value)
{
    glUniformMatrix4fv(locations_[PROJECTION], 1, GL_FALSE, glm::value_ptr(value));
}

void PhongShader::view(glm::mat4 value)
{
    glUniformMatrix4fv(locations_[VIEW], 1, GL_FALSE, glm::value_ptr(value));
}

void PhongShader::model(glm::mat4 value)
{
    glUniformMatrix4fv(locations_[MODEL], 1, GL_FALSE, glm::value_ptr(value));
}
