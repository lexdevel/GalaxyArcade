#ifndef GRAPHICSFACTORY_H
#define GRAPHICSFACTORY_H

#include "../util/Image.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Buffer.h"

class GraphicsFactory
{
public:

    /**
     * Create the shader program with attached vert and frag shaders.
     * @param vertSource The source code of the vert shader
     * @param fragSource The source code of the frag shader
     */
    static ShaderProgram *createShaderProgram(const char *vertSource, const char *fragSource);

    /**
     *
     */
    static Texture2D *createTexture2D(const Image *image);

    /**
     * Create the OpenGL buffer instance.
     * @param target The buffer target (GL_ARRAY_BUFFER / GL_ELEMENT_ARRAY_BUFFER)
     */
    static Buffer *createBuffer(GLenum target);
};

#endif // GRAPHICSFACTORY_H
