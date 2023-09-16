#ifndef FILELOADER_HPP
#define FILELOADER_HPP

#include "SaveDataManager.hpp"

#include <QString>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <sstream>

class FileLoader
{
public:
    FileLoader(QString path);

private:
    SaveDataManager *m_sdm;
};

#endif // FILELOADER_HPP
