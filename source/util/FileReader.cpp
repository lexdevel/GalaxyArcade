#include "FileReader.h"

bool FileReader::read(const char *path, std::vector<unsigned char> *resultBuffer)
{
    FILE *file = fopen(path, "rb");
    if (!file) { return false; }

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    resultBuffer->clear();
    resultBuffer->reserve(length);

    fread(resultBuffer->data(), 1, length, file);
    fclose(file);

    return true;
}
