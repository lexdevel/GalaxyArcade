#include "SpriteRenderer.h"
#include <OpenGL/gl.h>

SpriteRenderer *SpriteRenderer::create()
{
    const char *vertSource = ""
            "#ifdef GL_ES\n"
            "precision mediump float;\n"
            "#endif // GL_ES\n\n"
            "attribute vec2 a_position;\n"
            "attribute vec2 a_texcoord;\n"
            "varying   vec2 v_texcoord;\n"
            "uniform   mat4 u_pvmatrix;\n"
            "uniform   mat4 u_mvmatrix;\n"
            "void main() {\n"
            "    v_texcoord  = a_texcoord;\n"
            "    gl_Position = u_pvmatrix * u_mvmatrix * vec4(a_position, 0.0, 1.0);\n"
            "}";
    const char *fragSource = ""
            "#ifdef GL_ES\n"
            "precision mediump float;\n"
            "#endif // GL_ES\n\n"
            "varying vec2       v_texcoord;\n"
            "uniform sampler2D  u_teximage;\n"
            "void main() {\n"
            "    gl_FragColor = texture2D(u_teximage, v_texcoord);\n"
            "}";
    const SpriteVertex vertexBufferData[] = {
            { Vector2f(-1.0f,  1.0f), Vector2f(0.0f, 0.0f) },
            { Vector2f( 1.0f,  1.0f), Vector2f(1.0f, 0.0f) },
            { Vector2f( 1.0f, -1.0f), Vector2f(1.0f, 1.0f) },
            { Vector2f(-1.0f, -1.0f), Vector2f(0.0f, 1.0f) }
    };
    const GLuint elementArrayData[] = {
            0, 1, 2, 2, 3, 0
    };

    SpriteRenderer *spriteRenderer = new SpriteRenderer();

    spriteRenderer->m_renderShader.reset(GraphicsFactory::createShaderProgram(vertSource, fragSource));
    spriteRenderer->m_vertexBuffer.reset(GraphicsFactory::createBuffer(GL_ARRAY_BUFFER));
    spriteRenderer->m_elementArray.reset(GraphicsFactory::createBuffer(GL_ELEMENT_ARRAY_BUFFER));

    spriteRenderer->m_vertexBuffer->attach();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
    spriteRenderer->m_vertexBuffer->detach();

    spriteRenderer->m_elementArray->attach();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementArrayData), elementArrayData, GL_STATIC_DRAW);
    spriteRenderer->m_elementArray->detach();

    return spriteRenderer;
}

void SpriteRenderer::render(const Transformation &transformation, Texture2D *texture)
{
    this->m_renderShader->attach();

    Matrix projection = Matrix::orthographic(0.0f, 0.0f, 480.0f, 800.0f);
    Matrix transformationMatrix = transformation.createTransformationMatrix();

    GLint a_position = glGetAttribLocation(this->m_renderShader->identifier(), "a_position");
    GLint a_texcoord = glGetAttribLocation(this->m_renderShader->identifier(), "a_texcoord");
    GLint u_pvmatrix = glGetUniformLocation(this->m_renderShader->identifier(), "u_pvmatrix");
    GLint u_mvmatrix = glGetUniformLocation(this->m_renderShader->identifier(), "u_mvmatrix");
    GLint u_teximage = glGetUniformLocation(this->m_renderShader->identifier(), "u_teximage");

    glEnableVertexAttribArray(a_position);
    glEnableVertexAttribArray(a_texcoord);

    glUniformMatrix4fv(u_pvmatrix, 1, GL_FALSE, projection.data());
    glUniformMatrix4fv(u_mvmatrix, 1, GL_FALSE, transformationMatrix.data());

    this->m_vertexBuffer->attach();
    glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (void *)offsetof(SpriteVertex, position));
    glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (void *)offsetof(SpriteVertex, texcoord));
    this->m_vertexBuffer->detach();

    texture->attach();
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(u_teximage, 0);

    this->m_elementArray->attach();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    this->m_elementArray->detach();

    texture->detach();

    glDisableVertexAttribArray(a_texcoord);
    glDisableVertexAttribArray(a_position);
    glUseProgram(0);
}
