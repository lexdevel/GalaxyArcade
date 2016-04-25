#include "ShaderProgram.h"
#include <OpenGL/gl.h>
#include <assert.h>

ShaderProgram::ShaderProgram(const GLuint &identifier)
    : GraphicsObject(identifier)
{
}

ShaderProgram::~ShaderProgram()
{
    if (this->identifier()) {
        glDeleteProgram(this->identifier());
    }
}

void ShaderProgram::attach() { GLCALL(glUseProgram(this->identifier())); }
void ShaderProgram::detach() { GLCALL(glUseProgram(this->identifier())); }
