#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

class Shader
{
    public:
        Shader();
        Shader(Shader&& other);
        Shader(Shader const& other) = delete;
        ~Shader();

        Shader& operator=(Shader&& other);
        Shader& operator=(Shader const& other) = delete;

        void use();

    protected:
        GLuint program();
        void compile(std::string vertex_source, std::string fragment_source);

    private:
        GLuint program_;
};

#endif // SHADER_H
