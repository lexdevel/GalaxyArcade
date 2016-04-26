#ifndef GRAPHICSFACTORY_H
#define GRAPHICSFACTORY_H

#include "../util/Image.h"
#include "opengl/ShaderProgram.h"
#include "opengl/Texture2D.h"
#include "opengl/Buffer.h"

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
     * @param image
     */
    static Texture2D *createTexture2D(const Image *image);

    /**
     * Create the OpenGL buffer instance.
     * @param target The buffer target (GL_ARRAY_BUFFER / GL_ELEMENT_ARRAY_BUFFER)
     * @param bufferDataLength
     * @param bufferData
     */
    static Buffer *createBuffer(GLenum target, unsigned int bufferDataLength, const void *bufferData);
};

#endif // GRAPHICSFACTORY_H
