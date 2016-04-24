#include "TileRenderer.h"

TileRenderer::TileRenderer(unsigned int tileXCount, unsigned int tileYCount, Texture2D *textureAtlas)
    : m_tileXCount(tileXCount), m_tileYCount(tileYCount), m_textureAtlas(textureAtlas)
{
}

bool TileRenderer::create()
{
    const char *vertSource = ""
            "#ifdef GL_ES\n"
            "precision mediump float;\n"
            "#endif // GL_ES\n\n"
            ""
            "attribute vec2 a_position;\n"
            "attribute vec2 a_texcoord;\n"
            "varying   vec2 v_texcoord;\n"
            ""
            "uniform   mat4 u_pvmatrix;\n"
            "uniform   mat4 u_mvmatrix;\n"
            ""
            "void main() {"
            "    v_texcoord   = a_texcoord;\n"
            "    gl_Position  = u_pvmatrix * u_mvmatrix * vec4(a_position, 0.0, 1.0);\n"
            "}";
    const char *fragSource = ""
            "#ifdef GL_ES\n"
            "precision mediump float;\n"
            "#endif // GL_ES\n\n"
            ""
            "varying vec2       v_texcoord;\n"
            "uniform sampler2D  u_teximage;\n"
            ""
            "void main() {"
            "    gl_FragColor  = texture2D(u_teximage, v_texcoord);\n"
            "}";

    const Vector2f vertexBufferData[] = {
            Vector2f(-1.0f, 1.0f), Vector2f(1.0f, 1.0f),
            Vector2f(1.0f, -1.0f), Vector2f(-1.0f, -1.0f)
    };
    const GLuint elementArrayData[] = { 0, 1, 2, 2, 3, 0 };

    this->m_renderShader.reset(GraphicsFactory::createShaderProgram(vertSource, fragSource));
    this->m_vertexBuffer.reset(GraphicsFactory::createBuffer(GL_ARRAY_BUFFER));
    this->m_coordsBuffer.reset(GraphicsFactory::createBuffer(GL_ARRAY_BUFFER));
    this->m_elementArray.reset(GraphicsFactory::createBuffer(GL_ELEMENT_ARRAY_BUFFER));

    this->m_vertexBuffer->attach();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
    this->m_vertexBuffer->detach();

    this->m_elementArray->attach();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementArrayData), elementArrayData, GL_STATIC_DRAW);
    this->m_elementArray->detach();

    return true;
}

void TileRenderer::render(const Transformation &transformation, Tile *tile)
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

    glUniform1f(glGetUniformLocation(this->m_renderShader->identifier(), "u_rows"), static_cast<float>(this->m_tileXCount));
    glUniform1f(glGetUniformLocation(this->m_renderShader->identifier(), "u_cols"), static_cast<float>(this->m_tileYCount));

    this->m_vertexBuffer->attach();
    glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2f), 0);
    this->m_vertexBuffer->detach();

    // For every position attribute
    Vector2f texindex = tile->texindex();
    float w = 1.0f / (float)this->m_tileXCount;
    float h = 1.0f / (float)this->m_tileYCount;

    Vector2f coordsBufferData[] = {
            Vector2f( texindex.x == 0.0f ? 0.0f : 1.0f / (float)this->m_tileXCount * texindex.x,
                      texindex.y == 0.0f ? 0.0f : 1.0f / (float)this->m_tileYCount * texindex.y),

            Vector2f( texindex.x == 0.0f ? 0.0f + w : 1.0f / (float)this->m_tileXCount * texindex.x + w,
                      texindex.y == 0.0f ? 0.0f : 1.0f / (float)this->m_tileYCount * texindex.y),

            Vector2f( texindex.x == 0.0f ? 0.0f + w : 1.0f / (float)this->m_tileXCount * texindex.x + w,
                      texindex.y == 0.0f ? 0.0f + h : 1.0f / (float)this->m_tileYCount * texindex.y + h),

            Vector2f( texindex.x == 0.0f ? 0.0f : 1.0f / (float)this->m_tileXCount * texindex.x,
                      texindex.y == 0.0f ? 0.0f + h : 1.0f / (float)this->m_tileYCount * texindex.y + h)
    };

    this->m_coordsBuffer->attach();
    glBufferData(GL_ARRAY_BUFFER, sizeof(coordsBufferData), coordsBufferData, GL_STATIC_DRAW);
    glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2f), 0);
    this->m_coordsBuffer->detach();

    this->m_textureAtlas->attach();
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(u_teximage, 0);

    this->m_elementArray->attach();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    this->m_elementArray->detach();

    this->m_textureAtlas->detach();

    glDisableVertexAttribArray(a_texcoord);
    glDisableVertexAttribArray(a_position);
    glUseProgram(0);
}
