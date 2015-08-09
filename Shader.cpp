#include "Shader.h"

#include <string>
#include <array>
#include <cassert>

Shader::Shader() :
    program_(0)
{

}

Shader::Shader(Shader&& other)
{
    *this = std::move(other);
}

Shader::~Shader()
{
    if(program_)
        glDeleteProgram(program_);
}


Shader& Shader::operator=(Shader&& other)
{
    std::swap(program_, other.program_);

    return *this;
}


void Shader::use()
{
    assert(program_);
    glUseProgram(program_);
}

GLuint Shader::program()
{
    return program_;
}

void Shader::compile(std::string vertex_source, std::string fragment_source)
{
    std::array<const char*, 1> vertex_source_array = {vertex_source.c_str()};
    std::array<const char*, 1> fragment_source_array = {fragment_source.c_str()};

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex_shader, 1, vertex_source_array.data(), nullptr);
    glShaderSource(fragment_shader, 1, fragment_source_array.data(), nullptr);

    glCompileShader(vertex_shader);
    glCompileShader(fragment_shader);

    int compile_status = 0;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
    if(compile_status == GL_FALSE)
    {
        int max_length = 0;
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length);

        std::string error_log;
        error_log.resize(max_length);
        glGetShaderInfoLog(vertex_shader, max_length, &max_length, const_cast<char*>(error_log.data()));
        throw std::runtime_error("Failed to compile shader : " + error_log);
    }

    compile_status = 0;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
    if(compile_status == GL_FALSE)
    {
        int max_length = 0;
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length);

        std::string error_log;
        error_log.resize(max_length);
        glGetShaderInfoLog(fragment_shader, max_length, &max_length, const_cast<char*>(error_log.data()));
        throw std::runtime_error("Failed to compile shader : " + error_log);
    }

    program_ = glCreateProgram();

    glAttachShader(program_, vertex_shader);
    glAttachShader(program_, fragment_shader);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glLinkProgram(program_);

    int is_linked = 0;
    glGetProgramiv(program_, GL_LINK_STATUS, &is_linked);
    if(is_linked == GL_FALSE)
    {
        int max_length = 0;
        glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &max_length);

        std::string error_log;
        error_log.resize(max_length);
        glGetProgramInfoLog(program_, max_length, &max_length, const_cast<char*>(error_log.data()));
        throw std::runtime_error("Failed to link program : " + error_log);
    }
}
