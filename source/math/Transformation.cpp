#include "Transformation.h"

Transformation::Transformation()
    : position(), rotation(), size(glm::vec3(1.0f, 1.0f, 1.0f))
{
}

Transformation::Transformation(const glm::vec3 &position, const glm::vec3 &rotaion, const glm::vec3 &size)
    : position(position), rotation(rotation), size(size)
{
}

glm::mat4 Transformation::calculateTransformationMatrix() const
{
    static const glm::vec3 axis_x = glm::vec3(1.0f, 0.0f, 0.0f);
    static const glm::vec3 axis_y = glm::vec3(0.0f, 1.0f, 0.0f);
    static const glm::vec3 axis_z = glm::vec3(0.0f, 0.0f, 1.0f);

    glm::mat4 result = glm::mat4(1.0f);

    result *= glm::translate(result, this->position);
    result *= glm::rotate(result, this->rotation.x, axis_x);
    result *= glm::rotate(result, this->rotation.y, axis_y);
    result *= glm::rotate(result, this->rotation.z, axis_z);
    result *= glm::scale(result, this->size);

    return result;
}
