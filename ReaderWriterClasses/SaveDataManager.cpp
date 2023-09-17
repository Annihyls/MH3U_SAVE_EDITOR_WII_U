#include "SaveDataManager.hpp"

#include <iostream>
#include <intrin.h>
#include <cstdint>
#include <fstream>
#include <sstream>


SaveDataManager::~SaveDataManager()
{

}

void SaveDataManager::lire_donnees(std::string file_path)
{
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
        std::cerr << "Le fichier n'a pas pu s'ouvrir en mode lecture !" << std::endl;
        exit(EXIT_FAILURE);
    }
    lecture.close();

    //Je met les données dans les attributs
    ss.seekg(POSITION_BYTE_SEX, ss.beg);
    ss.read((char*)&this->sex, SIZE_SEX);

    ss.seekg(POSITION_BYTE_NAME, ss.beg);
    ss.read((char*)&this->name, SIZE_NAME);

    ss.seekg(POSITION_BYTE_HR, ss.beg);
    ss.read((char*)&this->hr, SIZE_HR);

    ss.seekg(POSITION_BYTE_ARGENT, ss.beg);
    ss.read((char*)&this->argent, SIZE_ARGENT);

    ss.seekg(POSITION_BYTE_TIME, ss.beg);
    ss.read((char*)&this->time, SIZE_TIME);

    //quand il y a trop de données, on les lis petit-à-petit
    ss.seekg(POSITION_BYTE_INVENTORY, ss.beg);
    for (int i = 0; i < SIZE_INVENTORY; i++)
    {
        ss.read((char*)&this->inventory[i], sizeof(uint32_t));
    }

    //quand il y a trop de données, on les lis petit-à-petit
    ss.seekg(POSITION_BYTE_POUCH, ss.beg);
    for (int i = 0; i < SIZE_POUCH; i++)
    {
        ss.read((char*)&this->pouch[i], sizeof(uint32_t));
    }

    //quand il y a trop de données, on les lis petit-à-petit
    ss.seekg(POSITION_BYTE_ITEM_BOX, ss.beg);
    for (int i = 0; i < SIZE_ITEM_BOX; i++)
    {
        ss.read((char*)&this->item_box[i], sizeof(uint32_t));
    }

    ss.seekg(POSITION_BYTE_EQ_BOX, ss.beg);
    for (int i = 0; i < SIZE_EQ_BOX; i++)
    {
        ss.read((char*)&this->eq_box[i], sizeof(uint64_t));
    }

    ss.seekg(POSITION_BYTE_RESSOURCE, ss.beg);
    ss.read((char*)&this->ressource, SIZE_RESSOURCE);

    //j'écris tout le fichier dans un tableau d'octets
    ss.seekg(0x00, ss.beg);
    for (int i = 0; i < SIZE_USER_FILE; i++)
    {
        ss.read((char*)&this->savefile[i], sizeof(uint8_t));
    }
}

void SaveDataManager::ecrire_donnees(std::string file_path)
{
    /*
       Cette fonction écrit les données passées en paramètre
       dans le fichier en les convertissant en binaire
    */
    std::stringstream ss;

    for (int i = 0; i < POSITION_BYTE_SEX; i++)
    {
        ss.write((char*)&this->savefile[i], sizeof(uint8_t));
    }

    //pour changer l'octet du sexe
    ss.write((char*)&this->sex, SIZE_SEX);

    //on skip jusqu'au prochaines choses à modifier.
    for (int i = POSITION_BYTE_SEX + SIZE_SEX; i < POSITION_BYTE_NAME; i++)
    {
        ss.write((char*)&this->savefile[i], sizeof(uint8_t));
    }

    //pour changer les 10 octets du nom.
    ss.write((char*)&this->name, SIZE_NAME);

    for (int i = POSITION_BYTE_NAME + SIZE_NAME; i < POSITION_BYTE_ARGENT; i++)
    {
        ss.write((char*)&this->savefile[i], sizeof(uint8_t));
    }

    //j'écris argent
    ss.write((char*)&this->argent, SIZE_ARGENT);

    for (int i = POSITION_BYTE_ARGENT + SIZE_ARGENT; i < POSITION_BYTE_TIME; i++)
    {
        ss.write((char*)&this->savefile[i], sizeof(uint8_t));
    }

    //j'écris le temps
    ss.write((char*)&this->time, SIZE_TIME);

    for (int i = POSITION_BYTE_TIME + SIZE_TIME; i < POSITION_BYTE_INVENTORY; i++)
    {
        ss.write((char*)&this->savefile[i], sizeof(uint8_t));
    }

    //j'écris l'inventaire petit a petit (pour eviter la surcharge du buffer)
    //INVENTORY WRITE
    for (int i = 0; i < SIZE_INVENTORY; i++)
    {
        ss.write((char*)&this->inventory[i], sizeof(uint32_t));
    }
    for (int i = POSITION_BYTE_INVENTORY + (SIZE_INVENTORY * 4); i < POSITION_BYTE_POUCH; i++)
    {
        ss.write((char*)&this->savefile[i], sizeof(uint8_t));
    }

    //POUCH WRITE
    for (int i = 0; i < SIZE_POUCH; i++)
    {
        ss.write((char*)&this->pouch[i], sizeof(uint32_t));
    }
    for (int i = POSITION_BYTE_POUCH + (SIZE_POUCH * 4); i < POSITION_BYTE_ITEM_BOX; i++)
    {
        ss.write((char*)&this->savefile[i], sizeof(uint8_t));
    }

    //ITEM BOX WRITING
    for (int i = 0; i < SIZE_ITEM_BOX; i++)
    {
        ss.write((char*)&this->item_box[i], sizeof(uint32_t));
    }
                                        //SIZE_ITEM_BOX * 4 car 1000 * 4 octets
    for (int i = POSITION_BYTE_ITEM_BOX + (SIZE_ITEM_BOX * 4); i < POSITION_BYTE_EQ_BOX; i++)
    {
        ss.write((char*)&this->savefile[i], sizeof(uint8_t));
    }

    //EQUIPMENT BOX WRITING
    for (int i = 0; i < SIZE_EQ_BOX; i++)
    {
        ss.write((char*)&this->eq_box[i], sizeof(uint64_t));
    }
    for (int i = POSITION_BYTE_EQ_BOX + (SIZE_EQ_BOX * 8); i < POSITION_BYTE_HR; i++)
    {
        ss.write((char*)&this->savefile[i], sizeof(uint8_t));
    }

    //j'écris le HR
    ss.write((char*)&this->hr, SIZE_HR);

    for (int i = POSITION_BYTE_HR + SIZE_HR; i < POSITION_BYTE_RESSOURCE; i++)
    {
        ss.write((char*)&this->savefile[i], sizeof(uint8_t));
    }

    //j'écris points moga
    ss.write((char*)&this->ressource, SIZE_RESSOURCE);

    for (int i = POSITION_BYTE_RESSOURCE + SIZE_RESSOURCE; i < SIZE_USER_FILE; i++)
    {
        ss.write((char*)&this->savefile[i], sizeof(uint8_t));
    }

    //j'ouvre un nouveau fichier en mode écriture binaire
    std::ofstream ecriture{ file_path, std::ios::binary };
    if (ecriture.is_open())
    {
        ecriture << ss.str();
    }
    else
    {
        std::cerr << "Le fichier n'a pas pu s'ouvrir en mode écriture !" << std::endl;
        exit(EXIT_FAILURE);
    }
    ecriture.close();
}

uint8_t SaveDataManager::getSex()
{
    return this->sex;
}

uint8_t* SaveDataManager::getName()
{
    return this->name;
}

uint16_t SaveDataManager::getHR()
{
    return _byteswap_ushort(this->hr);
}

uint32_t SaveDataManager::getArgent()
{
    return _byteswap_ulong(this->argent);
}

uint32_t SaveDataManager::getRessource()
{
    return _byteswap_ulong(this->ressource);
}

uint32_t SaveDataManager::getTime()
{
    return _byteswap_ulong(this->time);
}

uint16_t* SaveDataManager::getItem(ItemMode mode, int emplacement)
{
    /*
     * Cette fonction retourne un tableau
     * dont la première case contient l'id
     * de l'objet, et la seconde contient
     * la quantité de cet objet
     */
    uint32_t item;
    switch(mode)
    {
    case INVENTORY:
        item = _byteswap_ulong(this->inventory[emplacement]);
        break;

    case POUCH:
        item = _byteswap_ulong(this->pouch[emplacement]);
        break;

    case ITEM_BOX:
        item = _byteswap_ulong(this->item_box[emplacement]);
        break;
    }
    uint16_t *itemTab = new uint16_t[2];
    itemTab[1] = (uint16_t)item; //je cast en uint16_t (ce qui est au delà est ignoré)
    itemTab[0] = (uint16_t)(item >> 16); //je décale de 16 bits à droite et je l'interprète comme un uint16_t
    return itemTab;
}

uint8_t SaveDataManager::getTypeEquipment(int emplacement)
{
    uint64_t equip;
    uint8_t id;
    equip = _byteswap_uint64(this->eq_box[emplacement]);
    id = (uint8_t)(equip >> 56);
    return id;
}



void SaveDataManager::setSex(bool new_sex)
{
    if (new_sex == false)
        this->sex = 0x00;
    else
        this->sex = 0x01;
}

void SaveDataManager::setName(std::string new_name)
{
    short int i{ 0 };
    for (char c : new_name)
    {
        this->name[i] = c;
        i++;
    }
    while (i <= SIZE_NAME)
    {
        this->name[i] = 0x00;
        i++;
    }
}

void SaveDataManager::setHR(unsigned short new_hr)
{
    //pour changer l'endianness des bits (intrin.h)
    this->hr = _byteswap_ushort(new_hr);
}

void SaveDataManager::setArgent(unsigned long new_money)
{
    //pour changer l'endianness des bits (intrin.h)
    this->argent = _byteswap_ulong(new_money);
}

void SaveDataManager::setRessource(unsigned long new_ressource)
{
    //pour changer l'endianness des bits (intrin.h)
    this->ressource = _byteswap_ulong(new_ressource);
}

void SaveDataManager::setTime(unsigned long new_time)
{
    //pour changer l'endianness des bits (intrin.h)
    this->time = _byteswap_ulong(new_time);
}

void SaveDataManager::setItem(ItemMode mode, int emplacement, unsigned short id, unsigned short quantity)
{
    uint32_t item = 0;
    //pour concaténer id (uint16) et quantity(uint16) en un uint32
    item = ((uint32_t)id << 16) | quantity; //id << 16 = je décale id de 16 bit à gauche et OU logic quantité
    switch(mode)
    {
        case INVENTORY:
            this->inventory[emplacement] = _byteswap_ulong(item);
            break;

        case POUCH:
            this->pouch[emplacement] = _byteswap_ulong(item);
            break;

        case ITEM_BOX:
            this->item_box[emplacement] = _byteswap_ulong(item);
            break;
    }


}
