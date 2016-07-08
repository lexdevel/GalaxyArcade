#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "core/PlatformEntity.h"

/**
 * @brief The shader program class.
 */
class ShaderProgram : public PlatformEntity
{
public:
    explicit ShaderProgram(const std::string &vertSource, const std::string &fragSource);
    virtual ~ShaderProgram();

    virtual void attach() override;
    virtual void detach() override;
};

#endif // SHADERPROGRAM_H
