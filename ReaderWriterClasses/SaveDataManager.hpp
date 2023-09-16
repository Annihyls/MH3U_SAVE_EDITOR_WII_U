#ifndef SAVEDATAMANAGER_HPP
#define SAVEDATAMANAGER_HPP

#include <string>


#define SIZE_USER_FILE 35364

#define POSITION_BYTE_SEX 40
#define SIZE_SEX 1  //octets

#define POSITION_BYTE_NAME 43
#define SIZE_NAME 10 //octets

#define POSITION_BYTE_HR 0x5a48
#define SIZE_HR 2 //octets

#define POSITION_BYTE_ARGENT 0x48
#define SIZE_ARGENT 4 //octets

#define POSITION_BYTE_RESSOURCE 0x5b50
#define SIZE_RESSOURCE 4 //octets

#define POSITION_BYTE_TIME 0x4c
#define SIZE_TIME 4 //octets

#define POSITION_BYTE_ITEM_BOX 0x1b0
#define SIZE_ITEM_BOX 1000 //nb_objets stockable (1000)

class SaveDataManager
{
public:
    //constructeurs
    SaveDataManager() = default;

    //methods
    void lire_donnees(std::string file_path);
    void ecrire_donnees(std::string file_path);

    uint8_t getSex();
    uint8_t* getName();
    uint16_t getHR();
    uint32_t getArgent();
    uint32_t getRessource();
    uint32_t getTime();
    uint16_t* getItem(int emplacement);


    void setSex(bool new_sex);
    void setName(std::string new_name);
    void setHR(unsigned short new_hr);
    void setArgent(unsigned long argent);
    void setRessource(unsigned long ressource);
    void setTime(unsigned long new_time);
    void setItem(int emplacement, unsigned short id_item, unsigned short quantity);


private:
    //attributs
    uint8_t savefile[SIZE_USER_FILE];
    uint8_t sex;                        //1 octet
    uint8_t name[SIZE_NAME];            //10 octets
    uint16_t hr;                        //2 octets
    uint32_t argent;                    //4 octets
    uint32_t ressource;                 //4 octets
    uint32_t time;                      //4 octets
    uint32_t item_box[SIZE_ITEM_BOX];   //4 octets * 1000


};

#endif // SAVEDATAMANAGER_HPP
