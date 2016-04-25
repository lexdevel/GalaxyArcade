#include "Texture2D.h"

Texture2D::Texture2D(const GLuint &identifier)
    : GraphicsObject(identifier)
{
}

Texture2D::~Texture2D()
{
}

void Texture2D::attach() { glBindTexture(GL_TEXTURE_2D, this->identifier()); }
void Texture2D::detach() { glBindTexture(GL_TEXTURE_2D, 0); }
