#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::create()
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
    const Vector2f vertexBufferData[] = {
            Vector2f(-1.0f,  1.0f),
            Vector2f( 1.0f,  1.0f),
            Vector2f( 1.0f, -1.0f),
            Vector2f(-1.0f, -1.0f)
    };
    const GLuint elementArrayData[] = {
            0, 1, 2, 2, 3, 0
    };

    this->m_renderShader.reset(GraphicsFactory::createShaderProgram(vertSource, fragSource));
    this->m_vertexBuffer.reset(GraphicsFactory::createBuffer(GL_ARRAY_BUFFER, 4 * sizeof(Vector2f), vertexBufferData));
    this->m_coordsBuffer.reset(GraphicsFactory::createBuffer(GL_ARRAY_BUFFER, 0, nullptr));
    this->m_elementArray.reset(GraphicsFactory::createBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementArrayData), elementArrayData));

    this->m_shaderParams.a_position = glGetAttribLocation(this->m_renderShader->identifier(), "a_position");
    this->m_shaderParams.a_texcoord = glGetAttribLocation(this->m_renderShader->identifier(), "a_texcoord");
    this->m_shaderParams.u_pvmatrix = glGetUniformLocation(this->m_renderShader->identifier(), "u_pvmatrix");
    this->m_shaderParams.u_mvmatrix = glGetUniformLocation(this->m_renderShader->identifier(), "u_mvmatrix");
    this->m_shaderParams.u_teximage = glGetUniformLocation(this->m_renderShader->identifier(), "u_teximage");
}

void SpriteRenderer::initiate()
{
    GLCALL(glUseProgram(this->m_renderShader->identifier()));
    GLCALL(glEnableVertexAttribArray(this->m_shaderParams.a_position));
    GLCALL(glEnableVertexAttribArray(this->m_shaderParams.a_texcoord));
}

void SpriteRenderer::render(Renderable *renderable)
{
    SpriteRegion *spriteRegion = dynamic_cast<SpriteRegion *>(renderable);
    Sprite *sprite = dynamic_cast<Sprite *>(renderable);

    Vector2f coordsBufferData[] = {
            Vector2f(0.0f, 0.0f),
            Vector2f(1.0f, 0.0f),
            Vector2f(1.0f, 1.0f),
            Vector2f(0.0f, 1.0f)
    };

    if (spriteRegion)
    {
        // ToDo: Implement
    }

    this->m_vertexBuffer->attach();
    GLCALL(glVertexAttribPointer(this->m_shaderParams.a_position, 2, GL_FLOAT, GL_FALSE, 0, nullptr));
    this->m_vertexBuffer->detach();

    this->m_coordsBuffer->attach();
    GLCALL(glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector2f), coordsBufferData, GL_STATIC_DRAW));
    GLCALL(glVertexAttribPointer(this->m_shaderParams.a_texcoord, 2, GL_FLOAT, GL_FALSE, 0, nullptr));
    this->m_coordsBuffer->detach();

    // Matrix projection = Matrix::orthographic(0.0f, 0.0f, 480.0f, 800.0f);
    Matrix projection = Matrix::orthographic(-240.0f, 400.0f, 240.0f, -400.0f);
    Matrix transformation = sprite->transformation().createTransformationMatrix();

    GLCALL(glUniformMatrix4fv(this->m_shaderParams.u_pvmatrix, 1, GL_FALSE, projection.data()));
    GLCALL(glUniformMatrix4fv(this->m_shaderParams.u_mvmatrix, 1, GL_FALSE, transformation.data()));

    this->m_elementArray->attach();
    sprite->texture()->attach();
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(this->m_shaderParams.u_teximage, 0);

    GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

    sprite->texture()->detach();
    this->m_elementArray->detach();
}

void SpriteRenderer::submit()
{
    GLCALL(glDisableVertexAttribArray(this->m_shaderParams.a_texcoord));
    GLCALL(glDisableVertexAttribArray(this->m_shaderParams.a_position));
    GLCALL(glUseProgram(0));
}
