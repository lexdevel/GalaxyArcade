#ifndef ATTACHABLE_H
#define ATTACHABLE_H

/**
 * @brief The attachable interface.
 */
class Attachable
{
public:
    explicit Attachable();
    virtual ~Attachable() = 0;

    /**
     * @brief Attach.
     */
    virtual void attach() = 0;

    /**
     * @brief Detach.
     */
    virtual void detach() = 0;
};

#endif // ATTACHABLE_H
