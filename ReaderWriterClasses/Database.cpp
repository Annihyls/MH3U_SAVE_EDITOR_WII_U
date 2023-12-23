#include "Database.hpp"
#include <iostream>
#include <Qstring>
#include <QFile>
#include <QTextStream>


Database::Database(QString langue)
{
    m_listOfQStringList = QList<QStringList>();
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/item.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/chest_armors.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/arms_armors.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/waist_armors.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/legs_armors.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/head_armors.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/charms.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/gs_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/sns_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/h_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/l_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/hbg_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/skills.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/lbg_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/ls_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/sa_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/gl_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/bow_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/db_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/hh_weapons.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/jewels.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/equipment_type.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/sex.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/faces.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/hairs.txt").arg(langue).toStdString()));
    m_listOfQStringList.push_back(lireDonnees(QString(":/databases/data/%1/voices.txt").arg(langue).toStdString()));
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

    //une première ligne pour signifier les emplacement vide
    result.push_back("");

    QFile inputFile(file_path.c_str());
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if(line.startsWith("DUMMY"))
            {
                result.push_back("");
            }
            else
            {
                result.push_back(line);
            }
        }
        inputFile.close();
    }
    else
    {
        std::cerr << "Impossible d'ouvrir le fichier database !" << std::endl;
        exit(EXIT_FAILURE);
    }
    return result;
}

