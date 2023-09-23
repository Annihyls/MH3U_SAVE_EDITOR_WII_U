#include "Database.hpp"
#include <iostream>
#include <fstream>
#include <Qstring>


Database::Database(QString langue)
{
    m_listOfQStringList = QList<QStringList>();
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/item.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/chest_armors.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/arms_armors.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/waist_armors.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/legs_armors.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/head_armors.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/charms.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/gs_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/sns_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/h_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/l_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/hbg_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/skills.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/lbg_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/ls_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/sa_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/gl_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/bow_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/db_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/hh_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/jewels.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/equipment_type.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/sex.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/faces.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/hairs.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/%1/voices.txt").arg(langue).toStdString()));
}

Database::~Database()
{
}

QString Database::getElement(int id_database, int element)
{
    return m_listOfQStringList.at(id_database).at(element);
}

QStringList Database::getDatabase(int id_database)
{
    return m_listOfQStringList.at(id_database);
}

QStringList Database::lireDonnees(std::string file_path)
{
    QStringList result;
    QString test_temp;
    std::string str_temp;

    //une première ligne pour signifier les emplacement vide
    result.push_back("");

    std::ifstream lecture{ file_path, std::ios::in };
    if (lecture.is_open())
    {
        //je détermine d'abord le nombre de lignes du fichier
        while (!lecture.eof())
        {
            std::getline(lecture >> std::ws, str_temp);
            test_temp = str_temp.c_str();
            if(test_temp.startsWith("DUMMY"))
            {
                result.push_back("");
            }
            else
            {
                result.push_back(test_temp);
            }

        }
    }
    else
    {
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
        exit(EXIT_FAILURE);
    }
    lecture.close();
    return result;
}

