#include "Texture2D.h"

Texture2D::Texture2D(const TextureFilter &filter, const TextureWrap &wrap)
{
    GLCALL(glGenTextures(1, &this->m_identifier));
    // assert(this->m_identifier != 0);

    GLCALL(glBindTexture(GL_TEXTURE_2D, this->m_identifier));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap));
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture2D::Texture2D(const std::shared_ptr<Bitmap> &bitmap, const TextureFilter &filter, const TextureWrap &wrap)
{
    GLCALL(glGenTextures(1, &this->m_identifier));
    // assert(this->m_identifier != 0);

    GLCALL(glBindTexture(GL_TEXTURE_2D, this->m_identifier));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap));
    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap->w(), bitmap->h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap->data().data()));
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture2D::~Texture2D()
{
    if (this->m_identifier != 0)
    {
        GLCALL(glDeleteTextures(1, &this->m_identifier));
        // this->m_identifier = 0;
    }
}

void Texture2D::texImage2D(const std::shared_ptr<Bitmap> &bitmap)
{
    GLCALL(glBindTexture(GL_TEXTURE_2D, this->m_identifier));
    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap->w(), bitmap->h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap->data().data()));
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture2D::attach() { GLCALL(glBindTexture(GL_TEXTURE_2D, this->m_identifier)); }
void Texture2D::detach() { GLCALL(glBindTexture(GL_TEXTURE_2D, 0)); }
