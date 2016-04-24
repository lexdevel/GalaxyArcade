#include "GraphicsFactory.h"

ShaderProgram *GraphicsFactory::createShaderProgram(const char *vertSource, const char *fragSource)
{
    GLuint prog = GLCALL(glCreateProgram());

    GLuint vert = GLCALL(glCreateShader(GL_VERTEX_SHADER));
    GLuint frag = GLCALL(glCreateShader(GL_FRAGMENT_SHADER));

    GLCALL(glShaderSource(vert, 1, static_cast<const GLchar * const *>(&vertSource), nullptr));
    GLCALL(glShaderSource(frag, 1, static_cast<const GLchar * const *>(&fragSource), nullptr));

    GLCALL(glCompileShader(vert));
    GLCALL(glCompileShader(frag));

    // ToDo: Check shader compilation status

    GLCALL(glAttachShader(prog, vert));
    GLCALL(glAttachShader(prog, frag));

    GLCALL(glLinkProgram(prog));

    GLCALL(glDeleteShader(frag));
    GLCALL(glDeleteShader(vert));

    return new ShaderProgram(prog);
}

Texture2D *GraphicsFactory::createTexture2D(const Image *image)
{
    GLuint teximage = 0;
    glGenTextures(1, &teximage);

    glBindTexture(GL_TEXTURE_2D, teximage);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->imageW(), image->imageH(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->colorMap());

    glBindTexture(GL_TEXTURE_2D, 0);

    return new Texture2D(teximage);
}

Buffer *GraphicsFactory::createBuffer(GLenum target)
{
    GLuint buffer = 0;
    GLCALL(glGenBuffers(1, &buffer));

    return new Buffer(buffer, target);
}
