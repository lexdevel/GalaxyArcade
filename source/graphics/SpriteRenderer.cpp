#include "SpriteRenderer.h"

std::string SpriteRendererShaderSource::vertSource()
{
    return  ""
            "#ifdef GL_ES\n"
            "precision mediump float;\n"
            "#endif // GL_ES\n\n"
            ""
            "attribute vec2 a_position;\n"
            "attribute vec2 a_texcoord;\n"
            "varying   vec2 v_texcoord;\n"
            "uniform   mat4 u_pvmatrix;\n"
            "uniform   mat4 u_mvmatrix;\n\n"
            ""
            "void main() {\n"
            "    v_texcoord   = a_texcoord;\n"
            "    gl_Position  = u_pvmatrix * u_mvmatrix * vec4(a_position, 0.0, 1.0);\n"
            "}\0";
}

std::string SpriteRendererShaderSource::fragSource()
{
    return  ""
            "#ifdef GL_ES\n"
            "precision mediump float;\n"
            "#endif // GL_ES\n\n"
            ""
            "varying vec2       v_texcoord;\n"
            "uniform sampler2D  u_teximage;\n\n"
            ""
            "void main() {\n"
            "    gl_FragColor = texture2D(u_teximage, v_texcoord);\n"
            "}\0";
}

SpriteRenderer::SpriteRenderer()
    : Renderer(std::shared_ptr<ShaderProgram>(new ShaderProgram(SpriteRendererShaderSource::vertSource(),
                                                                SpriteRendererShaderSource::fragSource())))
{
    this->m_projection = Matrix::identity();
    this->m_transformStack.push(Matrix::identity());

    this->m_shaderProgram->attach();

    GLCALL(this->m_shaderParams.a_position = static_cast<GLuint>(glGetAttribLocation(this->m_shaderProgram->identifier(), "a_position")));
    GLCALL(this->m_shaderParams.a_texcoord = static_cast<GLuint>(glGetAttribLocation(this->m_shaderProgram->identifier(), "a_texcoord")));
    GLCALL(this->m_shaderParams.u_pvmatrix = static_cast<GLuint>(glGetUniformLocation(this->m_shaderProgram->identifier(), "u_pvmatrix")));
    GLCALL(this->m_shaderParams.u_mvmatrix = static_cast<GLuint>(glGetUniformLocation(this->m_shaderProgram->identifier(), "u_mvmatrix")));
    GLCALL(this->m_shaderParams.u_teximage = static_cast<GLuint>(glGetUniformLocation(this->m_shaderProgram->identifier(), "u_teximage")));

    this->m_shaderProgram->detach();
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::resize(uint32_t w, uint32_t h)
{
    const float aspect = static_cast<float>(w) / static_cast<float>(h);
    if (w >= h) {
        this->m_projection = Matrix::orthographic(-1.0f * aspect, 1.0f * aspect, 1.0f, -1.0f);
    } else {
        this->m_projection = Matrix::orthographic(-1.0f, 1.0f, 1.0f / aspect, -1.0f / aspect);
    }
}

void SpriteRenderer::invalidate(float r, float g, float b, float a)
{
    GLCALL(glClearColor(r, g, b, a));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void SpriteRenderer::initiate(const Matrix &initialTransform)
{
    this->m_shaderProgram->attach();

    GLCALL(glEnableVertexAttribArray(this->m_shaderParams.a_position));
    GLCALL(glEnableVertexAttribArray(this->m_shaderParams.a_texcoord));
    GLCALL(glUniformMatrix4fv(this->m_shaderParams.u_pvmatrix, 1, GL_FALSE, this->m_projection.elements));

    this->m_transformStack.push(this->m_transformStack.top() * initialTransform);
}

void SpriteRenderer::render(Renderable *renderable)
{
    Sprite *sprite = dynamic_cast<Sprite *>(renderable);
    if (!sprite) {
        // Render only sprites
        return;
    }

    Matrix transformationMatrix = this->m_transformStack.top() * sprite->transformation().calculateTransformationMatrix();
    GLCALL(glUniformMatrix4fv(this->m_shaderParams.u_mvmatrix, 1, GL_FALSE, transformationMatrix.elements));

    sprite->vertexBuffer()->attach();
    GLCALL(glVertexAttribPointer(this->m_shaderParams.a_position, 2, GL_FLOAT, GL_FALSE, 0, nullptr));
    sprite->vertexBuffer()->detach();

    sprite->texelsBuffer()->attach();
    GLCALL(glVertexAttribPointer(this->m_shaderParams.a_texcoord, 2, GL_FLOAT, GL_FALSE, 0, nullptr));
    sprite->texelsBuffer()->detach();

    GLCALL(glActiveTexture(GL_TEXTURE0));
    sprite->textureImage()->attach();
    GLCALL(glUniform1i(this->m_shaderParams.u_teximage, 0));

    sprite->elementArray()->attach();
    GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
    sprite->elementArray()->detach();

    sprite->textureImage()->detach();
}

void SpriteRenderer::submit()
{
    this->m_transformStack.pop();

    GLCALL(glDisableVertexAttribArray(this->m_shaderParams.a_position));
    GLCALL(glDisableVertexAttribArray(this->m_shaderParams.a_texcoord));

    this->m_shaderProgram->detach();
}
