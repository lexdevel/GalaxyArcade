#ifndef FILEREADER_H
#define FILEREADER_H

#include <cstdio>
#include <vector>

class FileReader
{
public:

    /**
     * Read the binary file.
     */
    static bool read(const char *path, std::vector<unsigned char> *resultBuffer);
};

#endif // FILEREADER_H
