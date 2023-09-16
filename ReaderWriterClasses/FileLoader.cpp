#include "FileLoader.hpp"

FileLoader::FileLoader(QString file_path)
{
    m_sdm = new SaveDataManager();
    /*
    Lis les données du fichier et les stocke dans les attributs
    de l'objet
    */
    std::stringstream ss;
    uint8_t tmp;
    std::ifstream lecture{ file_path, std::ios::binary };
    if (lecture.is_open())
    {
        for (int i = 0; i < SIZE_USER_FILE; i++)
        {
            //je stocke les octets dans un tableau de unsigned char
            lecture.read((char*)&tmp, sizeof(uint8_t));
            ss.write((char*)&tmp, sizeof(uint8_t));
        }
    }
    else
    {
        std::cerr << "user_test n'existe pas !" << std::endl;
        exit(EXIT_FAILURE);
    }
    lecture.close();

    //Je met les données dans les attributs
    ss.seekg(POSITION_BYTE_SEX, ss.beg);
    ss.read((char*)&m_sdm->sex, SIZE_SEX);

    ss.seekg(POSITION_BYTE_NAME, ss.beg);
    ss.read((char*)&m_sdm->name, SIZE_NAME);

    ss.seekg(POSITION_BYTE_HR, ss.beg);
    ss.read((char*)&m_sdm->hr, SIZE_HR);

    ss.seekg(POSITION_BYTE_ARGENT, ss.beg);
    ss.read((char*)&m_sdm->argent, SIZE_ARGENT);

    ss.seekg(POSITION_BYTE_RESSOURCE, ss.beg);
    ss.read((char*)&m_sdm->ressource, SIZE_RESSOURCE);

    ss.seekg(POSITION_BYTE_TIME, ss.beg);
    ss.read((char *)&m_sdm->time, SIZE_TIME);

    //j'écris tout le fichier dans un tableau d'octets
    ss.seekg(0x00, ss.beg);
    for (int i = 0; i < SIZE_USER_FILE; i++)
    {
        ss.read((char*)&m_sdm->savefile[i], sizeof(uint8_t));
    }
}
