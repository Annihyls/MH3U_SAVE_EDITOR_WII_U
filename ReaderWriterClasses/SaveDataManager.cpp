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

    ss.seekg(POSITION_BYTE_FACE, ss.beg);
    ss.read((char*)&this->face, SIZE_FACE);

    ss.seekg(POSITION_BYTE_HAIR, ss.beg);
    ss.read((char*)&this->hair, SIZE_HAIR);

    ss.seekg(POSITION_BYTE_NAME, ss.beg);
    ss.read((char*)&this->name, SIZE_NAME);

    ss.seekg(POSITION_BYTE_HR, ss.beg);
    ss.read((char*)&this->hr, SIZE_HR);

    ss.seekg(POSITION_BYTE_ARGENT, ss.beg);
    ss.read((char*)&this->argent, SIZE_ARGENT);

    ss.seekg(POSITION_BYTE_TIME, ss.beg);
    ss.read((char*)&this->time, SIZE_TIME);

    ss.seekg(POSITION_BYTE_VOICE, ss.beg);
    ss.read((char*)&this->voice, SIZE_VOICE);

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
    for (int i = POSITION_BYTE_SEX + SIZE_SEX; i < POSITION_BYTE_FACE; i++)
    {
        ss.write((char*)&this->savefile[i], sizeof(uint8_t));
    }

    //pour changer l'octet du visage
    ss.write((char*)&this->face, SIZE_FACE);

    //on skip jusqu'au prochaines choses à modifier.
    for (int i = POSITION_BYTE_FACE + SIZE_FACE; i < POSITION_BYTE_HAIR; i++)
    {
        ss.write((char*)&this->savefile[i], sizeof(uint8_t));
    }

    //pour changer l'octet du visage
    ss.write((char*)&this->hair, SIZE_HAIR);

    //on skip jusqu'au prochaines choses à modifier.
    for (int i = POSITION_BYTE_HAIR + SIZE_HAIR; i < POSITION_BYTE_NAME; i++)
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

    for (int i = POSITION_BYTE_TIME + SIZE_TIME; i < POSITION_BYTE_VOICE; i++)
    {
        ss.write((char*)&this->savefile[i], sizeof(uint8_t));
    }

    //pour changer l'octet du visage
    ss.write((char*)&this->voice, SIZE_VOICE);

    //on skip jusqu'au prochaines choses à modifier.
    for (int i = POSITION_BYTE_VOICE + SIZE_VOICE; i < POSITION_BYTE_INVENTORY; i++)
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

uint8_t SaveDataManager::getFace()
{
    return this->face;
}

uint8_t SaveDataManager::getHair()
{
    return this->hair;
}

uint8_t SaveDataManager::getVoice()
{
    return this->voice;
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
    uint32_t item = 0;
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

uint8_t SaveDataManager::getSlotOrUpgradeNumber(int emplacement)
{
    uint64_t equip;
    uint8_t slotUpgrade;
    equip = _byteswap_uint64(this->eq_box[emplacement]);
    slotUpgrade = (uint8_t)(equip >> 48);
    return slotUpgrade;
}
uint16_t SaveDataManager::getIdEquipment(int emplacement)
{
    uint64_t equip;
    uint16_t idEq;
    equip = _byteswap_uint64(this->eq_box[emplacement]);
    idEq = (uint16_t)(equip >> 32);
    return idEq;
}
uint8_t SaveDataManager::getFirstSkillCharmID(int emplacement)
{
    uint64_t equip;
    uint8_t skill;
    equip = _byteswap_uint64(this->eq_box[emplacement]);
    skill = (uint8_t)(equip >> 24);
    return skill;
}
uint8_t SaveDataManager::getFirstSkillCharmPoint(int emplacement)
{
    uint64_t equip;
    uint8_t skill;
    equip = _byteswap_uint64(this->eq_box[emplacement]);
    skill = (uint8_t)(equip >> 16);
    return skill;
}
uint8_t SaveDataManager::getSecondSkillCharmID(int emplacement)
{
    uint64_t equip;
    uint8_t skill;
    equip = _byteswap_uint64(this->eq_box[emplacement]);
    skill = (uint8_t)(equip >> 8);
    return skill;
}
uint8_t SaveDataManager::getSecondSkillCharmPoint(int emplacement)
{
    uint64_t equip;
    uint8_t skill;
    equip = _byteswap_uint64(this->eq_box[emplacement]);
    skill = (uint8_t)equip;
    return skill;
}
uint16_t SaveDataManager::getFirstDeco(int emplacement)
{
    uint64_t equip;
    uint16_t deco;
    //emplacement + 1 car (impair = decos, pair = equipement)
    equip = _byteswap_uint64(this->eq_box[emplacement+1]);
    deco = (uint16_t)(equip >> 48);
    return deco;
}
uint16_t SaveDataManager::getSecondDeco(int emplacement)
{
    uint64_t equip;
    uint16_t deco;
    //emplacement + 1 car (impair = decos, pair = equipement)
    equip = _byteswap_uint64(this->eq_box[emplacement+1]);
    deco = (uint16_t)(equip >> 32);
    return deco;
}
uint16_t SaveDataManager::getThirdDeco(int emplacement)
{
    uint64_t equip;
    uint16_t deco;
    //emplacement + 1 car (impair = decos, pair = equipement)
    equip = _byteswap_uint64(this->eq_box[emplacement+1]);
    deco = (uint16_t)(equip >> 16);
    return deco;
}



void SaveDataManager::setSex(bool new_sex)
{
    if (new_sex == false)
        this->sex = 0x00;
    else
        this->sex = 0x01;
}

void SaveDataManager::setFace(uint8_t new_face)
{
    this->face = new_face;
}

void SaveDataManager::setHair(uint8_t new_hair)
{
    this->hair = new_hair;
}

void SaveDataManager::setVoice(uint8_t new_voice)
{
    this->voice = new_voice;
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

void SaveDataManager::setHR(uint16_t new_hr)
{
    //pour changer l'endianness des bits (intrin.h)
    this->hr = _byteswap_ushort(new_hr);
}

void SaveDataManager::setArgent(uint32_t new_money)
{
    //pour changer l'endianness des bits (intrin.h)
    this->argent = _byteswap_ulong(new_money);
}

void SaveDataManager::setRessource(uint32_t new_ressource)
{
    //pour changer l'endianness des bits (intrin.h)
    this->ressource = _byteswap_ulong(new_ressource);
}

void SaveDataManager::setTime(uint32_t new_time)
{
    //pour changer l'endianness des bits (intrin.h)
    this->time = _byteswap_ulong(new_time);
}

void SaveDataManager::setItem(ItemMode mode, int emplacement, uint16_t id, uint16_t quantity)
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

void SaveDataManager::setWeapon(int emplacement,
                                uint8_t typeWeapon,
                                uint16_t idWeapon,
                                uint16_t firstJwl,
                                uint16_t secondJwl,
                                uint16_t thirdJwl)
{
    uint64_t equip = 0;
    uint64_t jwls = 0;

    equip = ((uint64_t)typeWeapon << 56)
            | ((uint64_t)idWeapon << 32);

    jwls = ((uint64_t)firstJwl << 48)
           | ((uint64_t)secondJwl << 32)
           | ((uint64_t)thirdJwl << 16);

    this->eq_box[emplacement] = _byteswap_uint64(equip);
    this->eq_box[emplacement+1] = _byteswap_uint64(jwls);

}

void SaveDataManager::setArmor(int emplacement,
                               uint8_t typeArmor,
                               uint8_t amelioration,
                               uint16_t idArmor,
                               uint16_t firstJwl,
                               uint16_t secondJwl,
                               uint16_t thirdJwl)
{
    uint64_t equip = 0;
    uint64_t jwls = 0;

    equip = ((uint64_t)typeArmor << 56)
            | ((uint64_t)amelioration << 48)
            | ((uint64_t)idArmor << 32);

    jwls = ((uint64_t)firstJwl << 48)
           | ((uint64_t)secondJwl << 32)
           | ((uint64_t)thirdJwl << 16);

    this->eq_box[emplacement] = _byteswap_uint64(equip);
    this->eq_box[emplacement+1] = _byteswap_uint64(jwls);
}

void SaveDataManager::setCharm(int emplacement,
                               uint8_t typeCharm,
                               uint8_t slot,
                               uint16_t idCharm,
                               uint8_t firstSkill,
                               uint8_t firstSkillPoint,
                               uint8_t secondSkill,
                               uint8_t secondSkillPoint,
                               uint16_t firstJwl,
                               uint16_t secondJwl,
                               uint16_t thirdJwl)
{
    uint64_t equip = 0;
    uint64_t jwls = 0;

    equip = ((uint64_t)typeCharm << 56)
            | ((uint64_t)slot << 48)
            | ((uint64_t)idCharm << 32)
            | ((uint64_t)firstSkill << 24)
            | ((uint64_t)firstSkillPoint << 16)
            | ((uint64_t)secondSkill << 8)
            | (uint64_t)secondSkillPoint;

    jwls = ((uint64_t)firstJwl << 48)
           | ((uint64_t)secondJwl << 32)
           | ((uint64_t)thirdJwl << 16);

    this->eq_box[emplacement] = _byteswap_uint64(equip);
    this->eq_box[emplacement+1] = _byteswap_uint64(jwls);
}
