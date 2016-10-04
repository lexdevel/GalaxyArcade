#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// using namespace glm;

/**
 * @brief The transformation structure.
 */
struct Transformation
{
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 size;
public:
    Transformation();
    Transformation(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &size);

    /**
     * @brief Calculate the transformation matrix.
     */
    glm::mat4 calculateTransformationMatrix() const;
};

#endif // TRANSFORMATION_H
