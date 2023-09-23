#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <Qstring>
#include <QList>
#include <QStringList>

#define ID_DB_ITEM 0
#define ID_DB_CHEST 1
#define ID_DB_ARM 2
#define ID_DB_WAIST 3
#define ID_DB_LEG 4
#define ID_DB_HELM 5
#define ID_DB_CHARM 6
#define ID_DB_GS 7
#define ID_DB_SNS 8
#define ID_DB_H 9
#define ID_DB_L 10
#define ID_DB_HBG 11
#define ID_DB_SKILL 12
#define ID_DB_LBG 13
#define ID_DB_LS 14
#define ID_DB_SA 15
#define ID_DB_GL 16
#define ID_DB_BOW 17
#define ID_DB_DB 18
#define ID_DB_HH 19
#define ID_DB_JWL 20
#define ID_DB_EQTYPE 21
#define ID_DB_SEX 22

class Database
{
public:
    Database(QString langue);
    ~Database();
    QString getElement(int id_database, int element);
    QStringList getDatabase(int id_database);

private:
    QList<QStringList> m_listOfQStringList;
    QStringList lireDonnees(std::string file_path);
};

#endif // DATABASE_HPP
