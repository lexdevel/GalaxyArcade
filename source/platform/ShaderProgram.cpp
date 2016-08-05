#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string &vertSource, const std::string &fragSource)
{
    GLuint vertShader = 0;
    GLuint fragShader = 0;
    GLint  status     = 0;

    GLCALL(this->m_identifier = glCreateProgram());
    GLCALL(vertShader = glCreateShader(  GL_VERTEX_SHADER));
    GLCALL(fragShader = glCreateShader(GL_FRAGMENT_SHADER));

    GLCALL(glShaderSource(vertShader, 1, (const GLchar * const *)vertSource.data(), nullptr));
    GLCALL(glShaderSource(fragShader, 1, (const GLchar * const *)fragSource.data(), nullptr));

    GLCALL(glCompileShader(vertShader));
    GLCALL(glCompileShader(fragShader));

    GLCALL(glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status));
    if (status == GL_FALSE) { throw std::runtime_error("Cannot compile vert shader!"); }

    GLCALL(glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status));
    if (status == GL_FALSE) { throw std::runtime_error("Cannot compile frag shader!"); }

    GLCALL(glAttachShader(this->m_identifier, vertShader));
    GLCALL(glAttachShader(this->m_identifier, fragShader));

    GLCALL(glLinkProgram(this->m_identifier));

    GLCALL(glGetProgramiv(this->m_identifier, GL_LINK_STATUS, &status));
    if (status == GL_FALSE) { throw std::runtime_error("Cannor link shader program!"); }

    GLCALL(glDeleteShader(fragShader)); // Free the frag shader
    GLCALL(glDeleteShader(vertShader)); // Free the vert shader
}

ShaderProgram::~ShaderProgram()
{
    if (this->m_identifier != 0)
    {
        GLCALL(glDeleteProgram(this->m_identifier));
        // this->m_identifier = 0;
    }
}

void ShaderProgram::attach() { GLCALL(glUseProgram(this->m_identifier)); }
void ShaderProgram::detach() { GLCALL(glUseProgram(0)); }
