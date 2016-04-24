#ifndef ATTACHABLE_H
#define ATTACHABLE_H

/**
 * The attachable interface.
 */
class Attachable
{
public:
    virtual ~Attachable() = 0;

    /**
     * Attach.
     */
    virtual void attach() = 0;

    /**
     * Detach.
     */
    virtual void detach() = 0;
};

#endif // ATTACHABLE_H
