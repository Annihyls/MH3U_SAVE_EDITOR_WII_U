#include "Database.hpp"
#include <iostream>
#include <fstream>

Database::Database(std::string file_path)
{
    std::string str_temp;
    int count = 0;
    std::ifstream lecture{ file_path, std::ios::in };
    if (lecture.is_open())
    {
        //je détermine d'abord le nombre de lignes du fichier
        while (!lecture.eof())
        {
            std::getline(lecture >> std::ws, str_temp);
            count++;
        }

        //je remet le curseur à la première ligne
        lecture.seekg(0);

        m_strTab = new QString[count];
        m_length = count;

        //je rempli mon tableau avec les données du fichier
        for(int i=0; i<count; i++)
        {
            std::getline(lecture >> std::ws, str_temp);
            m_strTab[i] = QString::fromStdString(str_temp);

        }
    }
    else
    {
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
        exit(EXIT_FAILURE);
    }
    lecture.close();
}

Database::~Database()
{
    delete[] this->m_strTab;
}

QString Database::getElement(int i)
{
    return m_strTab[i];
}

int Database::getSize()
{
    return m_length;
}
