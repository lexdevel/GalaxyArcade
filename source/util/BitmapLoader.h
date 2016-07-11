#ifndef BITMAPLOADER_H
#define BITMAPLOADER_H

#include "../core/Bitmap.h"
#include <string>
#include <memory>

/**
 * @brief The bitmap loader class.
 */
class BitmapLoader
{
public:

    /**
     * @brief Load the bitmap from a file.
     * @param path The path to file
     */
    static std::shared_ptr<Bitmap> load(const std::string &path);
};

#endif // BITMAPLOADER_H
