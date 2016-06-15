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

    this->m_shaderParams.a_position = static_cast<GLuint>(glGetAttribLocation(this->m_renderShader->identifier(), "a_position"));
    this->m_shaderParams.a_texcoord = static_cast<GLuint>(glGetAttribLocation(this->m_renderShader->identifier(), "a_texcoord"));
    this->m_shaderParams.u_pvmatrix = static_cast<GLuint>(glGetUniformLocation(this->m_renderShader->identifier(), "u_pvmatrix"));
    this->m_shaderParams.u_mvmatrix = static_cast<GLuint>(glGetUniformLocation(this->m_renderShader->identifier(), "u_mvmatrix"));
    this->m_shaderParams.u_teximage = static_cast<GLuint>(glGetUniformLocation(this->m_renderShader->identifier(), "u_teximage"));
}

void SpriteRenderer::resize(uint32_t w, uint32_t h)
{
    this->m_viewport.w = w;
    this->m_viewport.h = h;

    float aspect = static_cast<float>(this->m_viewport.w) / static_cast<float>(this->m_viewport.h);

    if (this->m_viewport.w > this->m_viewport.h)
    {
        // this->m_projecton = Matrix::orthographic(-240.0f * aspect, 400.0f / aspect, 240.0f * aspect, -400.0f / aspect);
        this->m_projecton = Matrix::orthographic(-1.0f * aspect, 1.0f, 1.0f * aspect, -1.0f);
        // this->m_projecton = this->m_projecton.multiply(Matrix::scale(1.0f, 1.0f * aspect));
    }
    else
    {
        // this->m_projecton = Matrix::orthographic(-240.0f, 400.0f / aspect, 240.0f, -400.0f / aspect);
        this->m_projecton = Matrix::orthographic(-1.0f, 1.0f / aspect, 1.0f, -1.0f / aspect);
        // this->m_projecton = this->m_projecton.multiply(Matrix::scale(1.0f * aspect, 1.0f));
    }

    glViewport(0, 0, w, h);
}

void SpriteRenderer::initiate()
{
    GLCALL(glUseProgram(this->m_renderShader->identifier()));

    GLCALL(glEnableVertexAttribArray(this->m_shaderParams.a_position));
    GLCALL(glEnableVertexAttribArray(this->m_shaderParams.a_texcoord));

    this->m_vertexBuffer->attach();
    GLCALL(glVertexAttribPointer(this->m_shaderParams.a_position, 2, GL_FLOAT, GL_FALSE, 0, nullptr));
    this->m_vertexBuffer->detach();

    GLCALL(glUniformMatrix4fv(this->m_shaderParams.u_pvmatrix, 1, GL_FALSE, this->m_projecton.data()));
}

void SpriteRenderer::render(Renderable *renderable)
{
    SpriteRegion *spriteRegion = dynamic_cast<SpriteRegion *>(renderable);
    Sprite *sprite = dynamic_cast<Sprite *>(renderable);

    if (!sprite) {
        // Render only sprites or derived from sprite instances...
        return;
    }

    Vector2f coordsBufferData[] = {
            Vector2f(0.0f, 0.0f), Vector2f(1.0f, 0.0f),
            Vector2f(1.0f, 1.0f), Vector2f(0.0f, 1.0f)
    };

    if (spriteRegion)
    {
        float x = spriteRegion->x() == 0 ? 0.0f : 1.0f / static_cast<float>(spriteRegion->rows()) * static_cast<float>(spriteRegion->x());
        float y = spriteRegion->y() == 0 ? 0.0f : 1.0f / static_cast<float>(spriteRegion->cols()) * static_cast<float>(spriteRegion->y());
        float w = 1.0f / static_cast<float>(spriteRegion->rows());
        float h = 1.0f / static_cast<float>(spriteRegion->cols());

        coordsBufferData[0] = Vector2f(x,     y);
        coordsBufferData[1] = Vector2f(x + w, y);
        coordsBufferData[2] = Vector2f(x + w, y + h);
        coordsBufferData[3] = Vector2f(x,     y + h);
    }

    Matrix transformation = sprite->transformation().createTransformationMatrix();
    GLCALL(glUniformMatrix4fv(this->m_shaderParams.u_mvmatrix, 1, GL_FALSE, transformation.data()));

    this->m_coordsBuffer->attach();
    GLCALL(glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector2f), coordsBufferData, GL_STATIC_DRAW));
    GLCALL(glVertexAttribPointer(this->m_shaderParams.a_texcoord, 2, GL_FLOAT, GL_FALSE, 0, nullptr));
    this->m_coordsBuffer->detach();

    this->m_elementArray->attach();
    sprite->texture()->attach();
    GLCALL(glActiveTexture(GL_TEXTURE0));
    GLCALL(glUniform1i(this->m_shaderParams.u_teximage, 0));

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
