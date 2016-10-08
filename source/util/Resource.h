#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

/**
 * @brief The resource class.
 */
class Resource
{
public:
    explicit Resource();
    virtual ~Resource();

    /**
     * @brief Load the resource.
     * @param location The location of the resource
     */
    virtual bool load(const std::string &location) = 0;
};

#endif // RESOURCE_H
